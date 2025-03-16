/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutifra <aoutifra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 23:53:13 by aoutifra          #+#    #+#             */
/*   Updated: 2023/05/22 09:26:35 by aoutifra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*initphilo(int *numphilo, t_philo **philo, t_data *data, int ac)
{
	int	i;

	i = -1;
	while (++i < numphilo[0])
	{
		memset(philo[i], 0, sizeof(t_philo));
		philo[i]->time_to_die = numphilo[1];
		philo[i]->time_to_eat = numphilo[2];
		philo[i]->tsleep = numphilo[3];
		philo[i]->meat = -1;
		if (ac == 6)
			philo[i]->meat = numphilo[4];
		philo[i]->id = i + 1;
		pthread_mutex_init(&philo[i]->fork, NULL);
		pthread_mutex_init(&philo[i]->lock, NULL);
		philo[i]->dat = data;
		if (1 == numphilo[0])
			return ((void *)(0));
		if (i == numphilo[0] - 1)
			philo[i]->right = philo[0];
		else if (i < numphilo[0] - 1)
			philo[i]->right = philo[i + 1];
	}
	return ((void *)(0));
}

void	message(char *str, t_philo *ph)
{
	pthread_mutex_lock(&ph->dat->write);
	printf("time : %lu philo number %d is %s\n", (time_in_ms()
			- ph->dat->time), ph->id, str);
	pthread_mutex_unlock(&ph->dat->write);
}

long	time_in_ms(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
