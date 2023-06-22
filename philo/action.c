/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcreus <mcreus@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:20:00 by mcreus            #+#    #+#             */
/*   Updated: 2023/06/22 15:28:32 by mcreus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	right_philo(t_philos *philos)
{
	pthread_mutex_lock(philos->right_fork);
	pthread_mutex_lock(&philos->args->m_message);
	print_status(philos, "has taken a fork");
	pthread_mutex_unlock(&philos->args->m_message);
	if (philos->n == 1)
	{
		pthread_mutex_unlock(philos->right_fork);
		ft_usleep(philos->time_die);
		return ;
	}
	pthread_mutex_lock(philos->left_fork);
	pthread_mutex_lock(&philos->args->m_message);
	print_status(philos, "has taken a fork");
	pthread_mutex_unlock(&philos->args->m_message);
	pthread_mutex_lock(&philos->args->m_message);
	print_status(philos, "is eating");
	pthread_mutex_unlock(&philos->args->m_message);
	philos->count++;
	pthread_mutex_lock(&philos->args->m_last_eat);
	philos->time_to_last_eat = get_time();
	pthread_mutex_unlock(&philos->args->m_last_eat);
	ft_usleep(philos->time_eat);
	pthread_mutex_unlock(philos->right_fork);
	pthread_mutex_unlock(philos->left_fork);
}

void	left_philo(t_philos *philos)
{
	pthread_mutex_lock(philos->left_fork);
	pthread_mutex_lock(&philos->args->m_message);
	print_status(philos, "has taken a fork");
	pthread_mutex_unlock(&philos->args->m_message);
	if (philos->n == 1)
	{
		pthread_mutex_unlock(philos->left_fork);
		ft_usleep(philos->time_die);
		return ;
	}
	pthread_mutex_lock(philos->right_fork);
	pthread_mutex_lock(&philos->args->m_message);
	print_status(philos, "has taken a fork");
	pthread_mutex_unlock(&philos->args->m_message);
	pthread_mutex_lock(&philos->args->m_message);
	print_status(philos, "is eating");
	pthread_mutex_unlock(&philos->args->m_message);
	philos->count++;
	pthread_mutex_lock(&philos->args->m_last_eat);
	philos->time_to_last_eat = get_time();
	pthread_mutex_unlock(&philos->args->m_last_eat);
	ft_usleep(philos->time_eat);
	pthread_mutex_unlock(philos->left_fork);
	pthread_mutex_unlock(philos->right_fork);
}

void	eat_activity(t_philos *philos)
{
	if (philos->identity % 2 == 0)
		right_philo(philos);
	else
		left_philo(philos);
}

void	activity(t_philos *philos)
{
	eat_activity(philos);
	if (philos->number_eat != 1 && philos->count == philos->number_eat)
	{
		pthread_mutex_lock(&philos->args->m_stop);
		philos->stop = 1;
		pthread_mutex_unlock(&philos->args->m_stop);
		return ;
	}
	pthread_mutex_lock(&philos->args->m_message);
	print_status(philos, "is sleeping");
	pthread_mutex_unlock(&philos->args->m_message);
	ft_usleep(philos->time_sleep);
	pthread_mutex_lock(&philos->args->m_message);
	print_status(philos, "is thinking");
	pthread_mutex_unlock(&philos->args->m_message);
	if (philos->n % 2 != 0)
		ft_usleep(100);
}
