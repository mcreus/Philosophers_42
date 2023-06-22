/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcreus <mcreus@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:35:11 by mcreus            #+#    #+#             */
/*   Updated: 2023/06/22 15:33:56 by mcreus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_free(t_philos *philos, pthread_t *thread, pthread_mutex_t *forks)
{
	if (philos)
	{
		free(philos);
		philos = NULL;
	}
	if (thread)
	{
		free(thread);
		thread = NULL;
	}
	if (forks)
	{
		free(forks);
		forks = NULL;
	}
}

int	malloc_error(t_philos *philos, pthread_t *thread, pthread_mutex_t *forks)
{
	ft_free(philos, thread, forks);
	perror("philo");
	return (-1);
}

int	malloc_str(t_philos **philos, pthread_t **thread,
		pthread_mutex_t **forks, int n)
{
	*philos = malloc(sizeof(t_philos) * n);
	if (!*philos)
		return (malloc_error(*philos, *thread, *forks));
	*thread = malloc(sizeof(pthread_t) * n);
	if (!*thread)
		return (malloc_error(*philos, *thread, *forks));
	*forks = malloc(sizeof(pthread_mutex_t) * n);
	if (!*forks)
		return (malloc_error(*philos, *thread, *forks));
	return (0);
}

int	main(int ac, char **av)
{
	t_arg			args;
	t_philos		*philos;
	pthread_t		*thread;
	pthread_mutex_t	*forks;

	if (ac < 5 || ac > 6 || init_info(ac, av, &args) == -1)
	{
		printf("Error\nInvalid arguments\n");
		return (1);
	}
	philos = NULL;
	thread = NULL;
	forks = NULL;
	if (malloc_str(&philos, &thread, &forks, args.number_of_philosophers) == -1)
		return (1);
	init_philos(philos, &args);
	take_forks(philos, forks, args.number_of_philosophers);
	init_thread(philos, &args, thread);
	destroy_mutex(&args, forks);
	ft_free(philos, thread, forks);
	return (0);
}
