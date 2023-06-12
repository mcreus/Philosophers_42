/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcreus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:07:07 by mcreus            #+#    #+#             */
/*   Updated: 2023/05/31 15:49:40 by mcreus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	just_one_philo(t_philos *philos)
{
	if (philos->args.number_of_philosophers == 1)
	{
		philos->time = get_time();
		if (pthread_create(&(philos->philos), NULL, &routine_for_one, philos))
		{
			pthread_mutex_lock(philos->message);
			printf("philosopher %d was not created...\n", 1);
			return (0);
		}
		return (0);
	}
	return (1);
}

int	start_philos(t_philos *philosophers)
{
	int	i;

	i = 0;
	if (!just_one_philo(philosophers))
		return (0);
	while (i < philosophers->args.number_of_philosophers)
	{
		philosophers[i].time = get_time();
		philosophers[i].time_of_last_eat = philosophers[i].time;
		if (pthread_create(&((philosophers[i]).philos), NULL, &routine,
				&philosophers[i]) || pthread_detach(philosophers[i].philos))
		{
			pthread_mutex_lock(philosophers->message);
			printf("philosopher %d was not created.\n", i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_philos(t_philos *philos, t_arg philo)
{
	int	i;

	i = 0;
	philos->check_die = (int *)malloc(sizeof(int));
	philos->count_eat = (int *)malloc(sizeof(int));
	if (philos->check_die == NULL || philos->count_eat == NULL)
		return (write(1, "not allocated memory\n", 21));
	philos->check_die[0] = 1;
	philos->count_eat[0] = 0;
	while (i < philo.number_of_philosophers)
	{
		philos[i].args = philo;
		philos[i].identity = i + 1;
		philos[i].check_die = philos[0].check_die;
		philos[i].count_eat = philos[0].count_eat;
		i++;
	}
	if (init_forks(philos) || init_mutex(philos))
		return (1);
	return (0);
}

int	init_forks(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->args.number_of_philosophers)
	{
		philos[i].left_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (philos[i].left_fork == NULL)
			return (write(1, "not allocated memory\n", 21));
		pthread_mutex_init(philos[i].left_fork, NULL);
		i++;
	}
	i = 0;
	while (i < philos->args.number_of_philosophers)
	{
		if (i == 0)
			philos[i].right_fork
				= philos[philos->args.number_of_philosophers - 1].left_fork;
		else
			philos[i].right_fork = philos[i - 1].left_fork;
		i++;
	}
	return (0);
}

int	init_mutex(t_philos *philos)
{
	int	i;

	i = 0;
	philos->message = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	philos->die = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	philos->eat = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (philos->message == NULL || philos->die == NULL || philos->eat == NULL)
		return (write(1, "not allocated memory\n", 21));
	pthread_mutex_init(philos->message, NULL);
	pthread_mutex_init(philos->die, NULL);
	pthread_mutex_init(philos->eat, NULL);
	while (i < philos->args.number_of_philosophers)
	{
		philos[i].message = philos->message;
		philos[i].die = philos->die;
		philos[i].eat = philos->eat;
		i++;
	}
	return (0);
}
