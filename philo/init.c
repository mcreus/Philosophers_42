/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcreus <mcreus@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:07:07 by mcreus            #+#    #+#             */
/*   Updated: 2023/06/22 13:49:16 by mcreus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_error(int ac, char **av)
{
	int		i;
	int		j;
	long	n;

	i = 0;
	while (++i < ac)
	{
		n = long_atoi(av[i]);
		if (n > 2147483647 || n == 0)
			return (-1);
		j = -1;
		while (av[i][++j])
		{
			if (!ft_isdigit(av[i][j]))
				return (-1);
		}
	}
	return (0);
}

int	init_info(int ac, char **av, t_arg *args)
{
	if (check_error(ac, av) == -1)
		return (-1);
	args->number_of_philosophers = (int)long_atoi(av[1]);
	args->time_to_die = (unsigned int)long_atoi(av[2]);
	args->time_to_eat = (unsigned int)long_atoi(av[3]);
	args->time_to_sleep = (unsigned int)long_atoi(av[4]);
	if (ac == 6)
		args->number_of_eat = (int)long_atoi(av[5]);
	else
		args->number_of_eat = -1;
	args->stop = 0;
	pthread_mutex_init(&args->m_stop, NULL);
	pthread_mutex_init(&args->m_message, NULL);
	pthread_mutex_init(&args->m_last_eat, NULL);
	return (0);
}

void	init_philos(t_philos *philos, t_arg *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		philos[i].args = args;
		philos[i].identity = i + 1;
		philos[i].n = args->number_of_philosophers;
		philos[i].count = 0;
		philos[i].stop = 0;
		philos[i].time_die = args->time_to_die;
		philos[i].time_eat = args->time_to_eat;
		philos[i].time_sleep = args->time_to_sleep;
		philos[i].number_eat = args->number_of_eat;
		i++;
	}
}

void	take_forks(t_philos *philos, pthread_mutex_t *forks, int n)
{
	int	i;

	pthread_mutex_init(&forks[0], NULL);
	philos[0].left_fork = &forks[0];
	philos[0].right_fork = NULL;
	philos[0].right_fork = &forks[n - 1];
	i = 1;
	while (i < n)
	{
		pthread_mutex_init(&forks[i], NULL);
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[i - 1];
		i++;
	}
}
