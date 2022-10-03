/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dozella <dozella@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 01:06:11 by dozella           #+#    #+#             */
/*   Updated: 2022/07/08 01:06:52 by dozella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_info *info)
{
	int	i;

	i = 0;
	usleep(100);
	pthread_mutex_destroy(&info->mutex);
	while (i < info->number_of_philosophers)
	{
		if (&info->forks[i])
			pthread_mutex_destroy(&info->forks[i]);
		i++;
	}
	if (info->philo)
		free (info->philo);
	if (info->forks)
		free (info->forks);
	if (info->threads)
		free (info->threads);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (!check_valid(argc, argv))
	{
		printf("error\n");
		return (0);
	}
	if (!init(&info, argc, argv) || !start(&info))
		printf("error\n");
	clean(&info);
	return (1);
}
