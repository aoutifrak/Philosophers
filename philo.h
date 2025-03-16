/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutifra <aoutifra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:00:05 by aoutifra          #+#    #+#             */
/*   Updated: 2023/05/22 09:26:43 by aoutifra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h> 
# include <sys/time.h>
# include <stdbool.h>
# define DEAD "dead"
# define EAT "eating"
# define THINK "think"
# define SLEEP "sleep"
# define FORK "is taking fork"
# define ERROR "Bad Argument !!"

struct	s_data;
typedef struct philo
{
	pthread_t		t;
	long			time_to_eat;
	long			time_to_die;
	long			tsleep;
	long			meat;
	int				id;
	long			eat;
	long			eat_time;
	pthread_mutex_t	lock;
	pthread_mutex_t	fork;
	struct philo	*right;
	struct s_data	*dat;
}t_philo;

typedef struct s_data
{
	int				finiched;
	int				philos;
	long			time;
	int				die_id;
	pthread_mutex_t	write;
	pthread_mutex_t	finich;
	t_philo			**pho;
}t_data;

void	*rot(void *philos);
void	*initphilo(int *numphilo, t_philo **philo, t_data *data, int ac);
void	message(char *str, t_philo *ph);
int		monitor(t_philo *philo);
int		ft_atoi(const char *str);
int		*dataini(t_data *data, int ac, char **av);
void	rotine(t_philo *philo);
int		ft_isdigit(char *s);
void	ft_delay(unsigned long dt);
int		finish_check(t_data *data);
void	*checks(void *data);
long	time_in_ms(void);
void	ft_sleep(t_philo *philo);

#endif // PHILO_H