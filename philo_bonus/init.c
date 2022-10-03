/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dozella <dozella@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 01:06:30 by dozella           #+#    #+#             */
/*   Updated: 2022/07/08 01:16:33 by dozella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_init(t_info *info, int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < info->number_of_philosophers)
	{
		info->philo[i].alive = 1;
		info->philo[i].last_eat_time = get_time();
		info->philo[i].id = i;
		info->philo[i].number_must_eat = -1;
		if (argc == 6)
			info->philo[i].number_must_eat = ft_atoi(argv[5]);
		info->philo[i].info = info;
		info->philo[i].pid = 0;
		i++;
	}
}

void	init_sem(t_info *info)
{
	sem_unlink("fork");
	sem_unlink("message");
	sem_unlink("death");
	info->death = sem_open("death", O_CREAT | O_EXCL, 644, 1);
	info->forks = sem_open("fork", O_CREAT | O_EXCL, 644, \
		info->number_of_philosophers);
	info->message = sem_open("message", O_CREAT | O_EXCL, 644, 1);
	if (info->death == SEM_FAILED || info->message == SEM_FAILED \
		|| info->forks == SEM_FAILED)
	{
		printf ("sem error\n");
		exit (1);
	}
}

int	init(t_info *info, int argc, char **argv)
{
	info->number_of_philosophers = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->time = get_time();
	info->philo = malloc (sizeof(t_philo) * info->number_of_philosophers);
	if (!info->philo)
	{
		printf ("malloc error\n");
		exit (1);
	}
	philo_init(info, argc, argv);
	init_sem(info);
	return (0);
}
