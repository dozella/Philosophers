/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dozella <dozella@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 01:06:35 by dozella           #+#    #+#             */
/*   Updated: 2022/07/08 01:52:22 by dozella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor_pid(t_info *info)
{
	int	status;
	int	full;

	full = 0;
	status = 0;
	while (1)
	{
		waitpid(-1, &status, 0);
		status = status >> 8;
		if (status == 4)
			break ;
		if (status == 5)
			full++;
		if (full == info->number_of_philosophers)
		{
			printf("number of meals reached\n");
			break ;
		}
	}
}

void	*check_death(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		if (philo->info->time_to_die <= get_time() - philo->last_eat_time)
		{
			sem_wait(philo->info->death);
			philo->alive = 0;
			message(philo, "died\n");
			sem_wait(philo->info->message);
			exit(4);
		}
	}
	return (NULL);
}

void	make_forks(t_info *info)
{
	pid_t	pid;
	int		i;

	i = 0;
	while (i < info->number_of_philosophers)
	{
		pid = fork();
		if (pid == 0)
			work(&info->philo[i]);
		else
			info->philo[i].pid = pid;
		i++;
	}
}

void	start(t_info *info)
{
	make_forks(info);
	monitor_pid(info);
}
