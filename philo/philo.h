/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dozella <dozella@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 01:06:17 by dozella           #+#    #+#             */
/*   Updated: 2022/07/08 01:50:31 by dozella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	struct s_info	*info;
	int				id;
	int				alive;
	int				number_must_eat;
	unsigned int	last_eat_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

typedef struct s_info
{
	unsigned int	time;
	pthread_t		*threads;
	t_philo			*philo;
	pthread_mutex_t	mutex;
	int				eat_limits;
	pthread_mutex_t	*forks;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
}					t_info;

int				check_valid(int argc, char **argv);
int				ft_atoi(const char *str);
int				init(t_info *info, int argc, char **argv);
int				start(t_info *info);
void			*work(void *args);
void			ft_usleep(int ms);
unsigned int	get_time(void);
void			message(t_philo *philo, const char *msg);

#endif