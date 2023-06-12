/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcreus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:20:00 by mcreus            #+#    #+#             */
/*   Updated: 2023/05/30 18:49:04 by mcreus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_left_fork(t_philos *philos)
{
	pthread_mutex_lock(philos->left_fork);
	check_time_to_die(philos);
	pthread_mutex_lock(philos->message);
	printf("%lldms philo %d has taken fork\n", (get_time() - philos->time),
		philos->identity);
	pthread_mutex_unlock(philos->message);
}

void	take_right_fork(t_philos *philos)
{
	pthread_mutex_lock(philos->right_fork);
	check_time_to_die(philos);
	pthread_mutex_lock(philos->message);
	printf("%lldms philo %d has taken a fork\n", (get_time() - philos->time),
		philos->identity);
	pthread_mutex_unlock(philos->message);
}

int	is_eating(t_philos *philos)
{
	philos->time_of_last_eat = get_time();
	pthread_mutex_lock(philos->message);
	printf("%lldms philo %d is eating\n", (get_time() - philos->time),
		philos->identity);
	pthread_mutex_unlock(philos->message);
	ft_usleep(philos->args.time_to_eat, get_time(), NULL);
	pthread_mutex_unlock(philos->left_fork);
	pthread_mutex_unlock(philos->right_fork);
	if (philos->args.number_of_times_each_philosopher_must_eat)
	{
		philos->args.number_of_times_each_philosopher_must_eat --;
		if (!philos->args.number_of_times_each_philosopher_must_eat)
			return (0);
	}
	return (1);
}

void	is_sleeping(t_philos *philos)
{
	pthread_mutex_lock(philos->message);
	printf("%lldms philo %d is sleeping\n", (get_time() - philos->time),
		philos->identity);
	pthread_mutex_unlock(philos->message);
	ft_usleep(philos->args.time_to_sleep, get_time(), philos);
}

void	is_thinking(t_philos *philos)
{
	pthread_mutex_lock(philos->message);
	printf("%lldms philo %d is thinking\n", (get_time() - philos->time),
		philos->identity);
	pthread_mutex_unlock(philos->message);
}
