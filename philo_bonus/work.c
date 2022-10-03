/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dozella <dozella@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 01:06:38 by dozella           #+#    #+#             */
/*   Updated: 2022/07/08 01:52:22 by dozella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(t_philo *philo, const char *msg)
{
	sem_wait(philo->info->message);
	printf("%ld %d %s", get_time() - philo->info->time, philo->id + 1, msg);
	sem_post(philo->info->message);
}

void	eating(t_philo *philo)
{
	sem_wait(philo->info->forks);
	message(philo, "has taken a fork\n");
	sem_wait(philo->info->forks);
	message(philo, "has taken a fork\n");
	message(philo, "is eating\n");
	sem_wait(philo->info->death);
	philo->last_eat_time = get_time();
	philo->number_must_eat--;
	sem_post(philo->info->death);
	ft_usleep(philo->info->time_to_eat);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
	if (philo->number_must_eat == 0)
		exit (5);
}

void	sleeping(t_philo *philo)
{
	message(philo, "is sleeping\n");
	ft_usleep(philo->info->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	message(philo, "is thinking\n");
}

void	work(t_philo *philo)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, check_death, philo))
		return ;
	if (pthread_detach(thread))
		return ;
	sem_wait(philo->info->death);
	while (philo->alive && philo->number_must_eat)
	{
		sem_post(philo->info->death);
		eating(philo);
		sleeping(philo);
		thinking(philo);
		sem_wait(philo->info->death);
	}
	sem_post(philo->info->death);
	exit (4);
}
