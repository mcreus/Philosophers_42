/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcreus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:40:47 by mcreus            #+#    #+#             */
/*   Updated: 2023/06/01 10:36:57 by mcreus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct s_arg{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
}	t_arg;

typedef struct s_philos{
	int				identity;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*message;
	pthread_mutex_t	*die;
	pthread_mutex_t	*eat;
	int				*check_die;
	int				*count_eat;
	long			time_of_last_eat;
	pthread_t		philos;
	long			time;
	t_arg			args;
}	t_philos;

void		ft_free(t_philos *philos);
void		wait_philos(t_philos *philos, int nb_of_eat);
int			main(int ac, char **av);
void		take_left_fork(t_philos *philos);
void		take_right_fork(t_philos *philos);
int			is_eating(t_philos *philos);
void		is_sleeping(t_philos *philos);
void		is_thinking(t_philos *philos);
int			just_one_philo(t_philos *philos);
int			start_philos(t_philos *philosophers);
int			init_forks(t_philos *philos);
int			init_philos(t_philos *philos, t_arg philo);
int			init_mutex(t_philos *philos);
int			parse(char **av);
int			check_arg(char **av);
int			arg_to_int(char **av, t_arg *philos);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
void		ft_usleep(int time_to_sleep, long long exec_time, t_philos *philos);
void		*routine_for_one(void *args);
void		*routine(void *args);
void		check_time_to_die(t_philos *philos);
long long	get_time(void);

#endif
