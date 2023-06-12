/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcreus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:35:11 by mcreus            #+#    #+#             */
/*   Updated: 2023/05/31 16:09:40 by mcreus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_free(t_philos *philos)
{
	int		i;

	i = 0;
	pthread_mutex_destroy(philos[i].eat);
	pthread_mutex_destroy(philos[i].message);
	pthread_mutex_destroy(philos[i].die);
	while (i < philos->args.number_of_philosophers)
	{
		pthread_mutex_destroy(philos[i].left_fork);
		free(philos[i].left_fork);
		i++;
	}
	free(philos->message);
	free(philos->die);
	free(philos->eat);
	free(philos->check_die);
	free(philos->count_eat);
	free(philos);
}

void	wait_philos(t_philos *philos, int nb_of_eat)
{
	while (1)
	{
		pthread_mutex_lock(philos->die);
		if (!*(philos->check_die))
			break ;
		pthread_mutex_unlock(philos->die);
		pthread_mutex_lock(philos->eat);
		if (*(philos->count_eat) == nb_of_eat)
			break ;
		pthread_mutex_unlock(philos->eat);
		usleep(50);
	}
}

int	main(int ac, char **av)
{
	t_arg		args;
	t_philos	*philos;

	if (ac == 5 || ac == 6)
	{
		if (!parse(av) || !arg_to_int(av, &args))
			return (0);
		philos = (t_philos *)malloc(sizeof(t_philos)
				* args.number_of_philosophers);
		if (!philos)
			return (write(1, "no memory allocated\n", 20));
		if (init_philos(philos, args) || start_philos(philos))
			return (0);
		wait_philos(philos, args.number_of_philosophers);
		ft_free(philos);
	}
	else
		printf("Error, not argument\n");
}
