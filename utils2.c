/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutifra <aoutifra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:29:46 by aoutifra          #+#    #+#             */
/*   Updated: 2023/05/25 22:57:56 by aoutifra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	finish_check(t_data *data)
{
	pthread_mutex_lock(&data->finich);
	if (data->finiched == data->philos)
		return (1);
	pthread_mutex_unlock(&data->finich);
	return (0);
}

int	ft_atoi(const char *str)
{
	long	res;
	int		i;
	int		sign;

	sign = 1;
	res = 0;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		if (res >= (__INT32_MAX__ / 10) && ((sign == 1 && str[i + 1] > '7')
				|| (sign == -1 && str[i + 1] > '8')))
			return (0);
		i++;
	}
	return (res * sign);
}

int	ft_isdigit(char *s)
{
	int	i;

	i = 0;
	while (s[i] >= '0' && s[i] <= '9' && s[i])
		s++;
	if (s[i] && (s[i] < '0' || s[i] > '9'))
		return (0);
	return (1);
}

void	ft_usleep(long delay)
{
	long	time;

	time = time_in_ms();
	while (time_in_ms() < (time + delay))
		usleep(500);
}

void	rotine(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	message(FORK, philo);
	if (!philo->right)
		return ;
	pthread_mutex_lock(&philo->right->fork);
	message(FORK, philo);
	message(EAT, philo);
	pthread_mutex_lock(&philo->lock);
	philo->eat_time = time_in_ms();
	pthread_mutex_unlock(&philo->lock);
	ft_usleep(philo->time_to_eat);
	philo->eat++;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->right->fork);
	message(SLEEP, philo);
	ft_usleep(philo->tsleep);
	message(THINK, philo);
}
