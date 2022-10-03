/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dozella <dozella@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 01:06:08 by dozella           #+#    #+#             */
/*   Updated: 2022/07/08 01:50:31 by dozella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(&philo->info->mutex);
	printf("%u %d %s", get_time() - philo->info->time, philo->id + 1, msg);
	pthread_mutex_unlock(&philo->info->mutex);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	message(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->right_fork);
	message(philo, "has taken a fork\n");
	message(philo, "is eating\n");
	pthread_mutex_lock(&philo->info->mutex);
	philo->last_eat_time = get_time();
	philo->number_must_eat--;
	if (philo->number_must_eat == 0)
		philo->info->eat_limits--;
	pthread_mutex_unlock(&philo->info->mutex);
	ft_usleep(philo->info->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
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

void	*work(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	pthread_mutex_lock(&philo->info->mutex);
	while (philo->alive && philo->number_must_eat)
	{
		pthread_mutex_unlock(&philo->info->mutex);
		eating(philo);
		sleeping(philo);
		thinking(philo);
		pthread_mutex_lock(&philo->info->mutex);
	}
	pthread_mutex_unlock(&philo->info->mutex);
	return (NULL);
}
