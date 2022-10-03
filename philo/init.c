/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dozella <dozella@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 01:05:48 by dozella           #+#    #+#             */
/*   Updated: 2022/07/08 01:06:52 by dozella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_malloc(t_info *info)
{
	info->threads = malloc(sizeof(pthread_t) * info->number_of_philosophers);
	if (!info->threads)
		return (0);
	info->forks = \
		malloc (sizeof(pthread_mutex_t) * info->number_of_philosophers);
	if (!info->forks)
		return (0);
	info->philo = malloc(sizeof(t_philo) * info->number_of_philosophers);
	if (!info->philo)
		return (0);
	return (1);
}

int	philo_init(t_info *info, int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < info->number_of_philosophers)
	{
		info->philo[i].alive = 1;
		info->philo[i].last_eat_time = get_time();
		info->philo[i].id = i;
		info->philo[i].info = info;
		info->philo[i].number_must_eat = -1;
		if (argc == 6)
			info->philo[i].number_must_eat = ft_atoi(argv[5]);
		info->philo[i].left_fork = &info->forks[i];
		info->philo[i].right_fork = \
			&(info)->forks[(i + 1) % info->number_of_philosophers];
		i++;
	}
	return (1);
}

int	init_mutex(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->number_of_philosophers)
	{
		if (pthread_mutex_init(&info->forks[i], NULL))
		{
			printf("mutex ");
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(&info->mutex, NULL))
	{
		printf("mutex ");
		return (0);
	}
	return (1);
}

int	init(t_info *info, int argc, char **argv)
{
	info->number_of_philosophers = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->eat_limits = info->number_of_philosophers;
	info->time = get_time();
	if (!philo_malloc(info) || !philo_init(info, argc, argv) \
		|| !init_mutex(info))
		return (0);
	return (1);
}
