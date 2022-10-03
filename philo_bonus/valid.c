/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dozella <dozella@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 01:06:50 by dozella           #+#    #+#             */
/*   Updated: 2022/07/08 01:29:19 by dozella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_number_arguments(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("valid error\n");
		return (1);
	}	
	return (0);
}

int	check_valid(int argc, char **argv)
{
	int	i;
	int	j;

	if (check_number_arguments(argc) == 1)
		exit (1);
	i = 1;
	while (argv[i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("valid error\n");
				exit (1);
			}
		}
		if (ft_atoi(argv[i]) <= 0)
		{
			printf("valid error\n");
			exit (1);
		}
		i++;
	}
	return (0);
}
