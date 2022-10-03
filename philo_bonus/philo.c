/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dozella <dozella@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 01:06:41 by dozella           #+#    #+#             */
/*   Updated: 2022/07/08 01:20:08 by dozella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->number_of_philosophers)
	{
		kill(info->philo[i].pid, 9);
		i++;
	}
	if (info->philo)
		free (info->philo);
	sem_close(info->forks);
	sem_unlink("fork");
	sem_close(info->message);
	sem_unlink("message");
	sem_close(info->death);
	sem_unlink("death");
}

int	main(int argc, char **argv)
{
	t_info	info;

	check_valid(argc, argv);
	init(&info, argc, argv);
	start(&info);
	clean(&info);
	return (0);
}
