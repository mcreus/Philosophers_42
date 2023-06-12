/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcreus <mcreus@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:51:29 by mcreus            #+#    #+#             */
/*   Updated: 2023/06/09 17:43:42 by mcreus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parse(char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
			{
				printf("Error\n Invalid arg\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_arg(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (!av[i][0])
		{
			printf("Error, Empty argument\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	arg_to_int(char **av, t_arg *philos)
{
	if (!check_arg(av))
		return (0);
	philos->number_of_philosophers = ft_atoi(av[1]);
	if (!philos->number_of_philosophers)
		return (0);
	philos->time_to_die = ft_atoi(av[2]);
	philos->time_to_eat = ft_atoi(av[3]);
	philos->time_to_sleep = ft_atoi(av[4]);
	philos->number_of_times_each_philosopher_must_eat = 0;
	if (av[5] && av[0])
	{
		philos->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
		if (!philos->number_of_times_each_philosopher_must_eat)
			return (0);
	}
	if (philos->number_of_philosophers < 0 || philos->time_to_die < 0
		|| philos->time_to_eat < 0 || philos->time_to_sleep < 0
		|| philos->number_of_times_each_philosopher_must_eat < 0)
	{
		printf("Error\n Invalid arguments\n");
		return (0);
	}
	return (1);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10 + str[i] - '0');
		i++;
	}
	return (res * sign);
}
