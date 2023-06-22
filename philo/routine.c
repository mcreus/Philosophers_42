/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcreus <mcreus@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:49:10 by mcreus            #+#    #+#             */
/*   Updated: 2023/06/22 14:01:38 by mcreus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*is_dead(void *arg)
{
	t_philos	*philo;
	int			stop;

	philo = (t_philos *)arg;
	stop = 0;
	while (!stop)
	{
		pthread_mutex_lock(&philo->args->m_last_eat);
		if (get_time() - philo->time_to_last_eat >= philo->time_die)
		{
			pthread_mutex_unlock(&philo->args->m_last_eat);
			pthread_mutex_lock(&philo->args->m_message);
			print_status(philo, "died");
			pthread_mutex_unlock(&philo->args->m_message);
		}
		else
			pthread_mutex_unlock(&philo->args->m_last_eat);
		pthread_mutex_lock(&philo->args->m_stop);
		stop = philo->args->stop + philo->stop;
		pthread_mutex_unlock(&philo->args->m_stop);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philos	*philo;
	int			stop;

	philo = (t_philos *)arg;
	philo->time_to_last_eat = philo->args->t_start;
	if (pthread_create(&philo->the_die, NULL, &is_dead, philo))
		perror("pthread_created failure");
	stop = 0;
	while (!stop)
	{
		activity(philo);
		pthread_mutex_lock(&philo->args->m_stop);
		stop = philo->args->stop + philo->stop;
		pthread_mutex_unlock(&philo->args->m_stop);
	}
	if (pthread_join(philo->the_die, NULL))
		perror("Pthread_join failure");
	return (NULL);
}

void	destroy_mutex(t_arg *args, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&args->m_last_eat);
	pthread_mutex_destroy(&args->m_message);
	pthread_mutex_destroy(&args->m_stop);
}

int	init_thread(t_philos *philo, t_arg *args, pthread_t *thread)
{
	int	i;

	i = 0;
	args->t_start = get_time();
	while (i < args->number_of_philosophers)
	{
		if (pthread_create(&thread[i], NULL, &routine, &philo[i]))
			perror("pthread_create failure");
		i++;
	}
	i = 0;
	while (i < args->number_of_philosophers)
	{
		if (pthread_join(thread[i], NULL))
			perror("pthread_join failure");
		i++;
	}
	return (0);
}
