/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcreus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:49:10 by mcreus            #+#    #+#             */
/*   Updated: 2023/05/30 17:00:59 by mcreus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(int time_to_sleep, long long exec_time, t_philos *philos)
{
	while (1)
	{
		usleep(50);
		if (philos)
			check_time_to_die(philos);
		if ((get_time() - exec_time) >= time_to_sleep)
			break ;
	}
}

void	*routine_for_one(void *args)
{
	t_philos	*philos;

	philos = (t_philos *)args;
	pthread_mutex_lock(philos->message);
	pthread_mutex_lock(philos->left_fork);
	printf("%lldms philo %d has taken a fork\n", (get_time() - philos->time),
		philos->identity);
	ft_usleep(philos->args.time_to_die, get_time(), NULL);
	pthread_mutex_lock(philos->die);
	*(philos->check_die) = 0;
	printf("%lldms philo %d died \n", (get_time() - philos->time),
		philos->identity);
	pthread_mutex_unlock(philos->die);
	return (NULL);
}

void	*routine(void *args)
{
	t_philos	*philos;

	philos = (t_philos *)args;
	if (philos->identity % 2 == 0)
		ft_usleep(30, get_time(), NULL);
	while (1)
	{
		check_time_to_die(philos);
		take_left_fork(philos);
		take_right_fork(philos);
		if (!is_eating(philos))
			break ;
		is_sleeping(philos);
		is_thinking(philos);
	}
	pthread_mutex_lock(philos->eat);
	*(philos->count_eat) += 1;
	pthread_mutex_unlock(philos->eat);
	return (NULL);
}

void	check_time_to_die(t_philos *philos)
{
	if ((get_time() - philos->time_of_last_eat) >= philos->args.time_to_die)
	{
		pthread_mutex_lock(philos->message);
		pthread_mutex_lock(philos->die);
		*(philos->check_die) = 0;
		printf("%lldms philo %d died\n", (get_time() - philos->time),
			philos->identity);
		pthread_mutex_unlock(philos->die);
	}
}
