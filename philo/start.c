/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dozella <dozella@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 01:06:04 by dozella           #+#    #+#             */
/*   Updated: 2022/07/08 01:50:30 by dozella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	limits_check(t_info *info)
{
	if (info->eat_limits == 0)
	{
		printf("number of meals reached\n");
		return (0);
	}
	return (1);
}

void	monitor(t_info *info)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < info->number_of_philosophers)
		{
			pthread_mutex_lock(&info->mutex);
			if (!limits_check(info))
				return ;
			if ((unsigned int)info->time_to_die
				<= get_time() - info->philo[i].last_eat_time)
			{
				info->philo->alive = 0;
				pthread_mutex_unlock(&info->mutex);
				message(&info->philo[i], "died\n");
				pthread_mutex_lock(&info->mutex);
				return ;
			}
			pthread_mutex_unlock(&info->mutex);
			i++;
		}
	}
	return ;
}

int	start(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->number_of_philosophers)
	{
		if (pthread_create(&info->threads[i], NULL, \
			work, &info->philo[i]))
			return (0);
		if (pthread_detach(info->threads[i]))
			return (0);
		usleep(100);
		i++;
	}
	monitor(info);
	return (1);
}
