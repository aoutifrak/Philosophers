/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutifra <aoutifra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:04 by aoutifra          #+#    #+#             */
/*   Updated: 2023/05/25 22:57:44 by aoutifra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*rot(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *) philos;
	if (!(philo->id % 2))
		usleep(100);
	while (1)
	{
		rotine(philo);
		if (!philo->right)
			break ;
		pthread_mutex_lock(&philo->dat->finich);
		if (philo->dat->die_id)
			break ;
		pthread_mutex_unlock(&philo->dat->finich);
		if (philo->eat == philo->meat)
		{
			pthread_mutex_lock(&philo->dat->finich);
			philo->dat->finiched++;
			pthread_mutex_unlock(&philo->dat->finich);
			return (NULL);
		}
	}
	return ((void *)(0));
}

int	*dataini(t_data *data, int ac, char *av[])
{
	int	i;
	int	*j;

	i = 0;
	j = malloc(sizeof(int) * (ac - 1));
	while (i < ac - 1)
	{
		if (!ft_isdigit(av[i + 1]))
			return (free(j), NULL);
		j[i] = ft_atoi(av[i + 1]);
		if (j[i] <= 0)
			return (free(j), NULL);
		i++;
	}
	memset(data, 0, sizeof(t_data));
	data->philos = j[0];
	data->pho = malloc(sizeof(t_philo *) * (j[0]));
	if (!data->pho)
		return (NULL);
	i = -1;
	while (++i < data->philos)
		data->pho[i] = malloc(sizeof(t_philo));
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->finich, NULL);
	return (j);
}

void	ft_free(t_data *data, int *j)
{
	int	i;

	i = -1;
	while (++i < j[0])
	{
		pthread_mutex_destroy(&data->pho[i]->fork);
		pthread_mutex_destroy(&data->pho[i]->lock);
		free(data->pho[i]);
	}
	free(data->pho);
	free(j);
	pthread_mutex_destroy(&data->finich);
	pthread_mutex_destroy(&data->write);
	free(data);
}

void	*checks(void *dat)
{
	int			i;
	t_data		*data;

	data = (t_data *)dat;
	while (1)
	{
		if (finish_check(data))
			return (NULL);
		i = -1;
		while (++i < (data->philos))
		{
			pthread_mutex_lock(&data->pho[i]->lock);
			if (data->pho[i]->time_to_die
				<= time_in_ms() - data->pho[i]->eat_time)
			{
				pthread_mutex_lock(&data->write);
				pthread_mutex_lock(&data->finich);
					data->die_id++;
				return (printf("time : %lu philo number %d is %s\n",
						(time_in_ms() - data->time), (i + 1), DEAD), NULL);
			}
			pthread_mutex_unlock(&data->pho[i]->lock);
		}
	}
}

int	main(int ac, char *argv[])
{
	t_data		*data;
	pthread_t	n;
	int			i;
	int			*j;

	i = 0;
	if (ac != 5 && ac != 6)
		return (printf("%s\n", ERROR), 1);
	data = malloc(sizeof(t_data));
	j = dataini(data, ac, argv);
	if (!j || !data || initphilo(j, data->pho, data, ac))
		return (printf("%s", ERROR), free(data), 1);
	i = -1;
	data->time = time_in_ms();
	while (++i < j[0])
		pthread_create(&data->pho[i]->t, NULL, rot, (void *)data->pho[i]);
	i = -1;
	while (++i < j[0])
		pthread_detach(data->pho[i]->t);
	usleep(data->pho[0]->time_to_die * 1000);
	pthread_create(&n, NULL, checks, (void *)data);
	pthread_join(n, NULL);
	ft_free(data, j);
	return (0);
}
