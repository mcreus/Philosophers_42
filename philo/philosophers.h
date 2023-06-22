/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcreus <mcreus@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:40:47 by mcreus            #+#    #+#             */
/*   Updated: 2023/06/22 14:13:32 by mcreus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_arg{
	int						number_of_philosophers;
	unsigned int			time_to_die;
	unsigned int			time_to_eat;
	unsigned int			time_to_sleep;
	unsigned int			t_start;
	int						number_of_eat;
	int						stop;
	pthread_mutex_t			m_stop;
	pthread_mutex_t			m_message;
	pthread_mutex_t			m_last_eat;
}	t_arg;

typedef struct s_philos{
	t_arg					*args;
	int						identity;
	int						n;
	int						count;
	unsigned int			time_die;
	unsigned int			time_eat;
	unsigned int			time_sleep;
	int						number_eat;
	unsigned int			time_to_last_eat;
	int						stop;
	pthread_t				the_die;
	pthread_mutex_t			*right_fork;
	pthread_mutex_t			*left_fork;
}	t_philos;

void			activity(t_philos *philos);
void			init_philos(t_philos *philos, t_arg *args);
void			print_status(t_philos *philo, char *status);
void			ft_bzero(void *str, size_t n);
int				ft_isdigit(int c);
int				ft_strlen(char *str);
int				ft_strcmp(const char *s1, const char *s2);
long			long_atoi(char *str);
void			destroy_mutex(t_arg *args, pthread_mutex_t *forks);
int				init_thread(t_philos *philo, t_arg *args, pthread_t *thread);
unsigned int	get_time(void);
void			ft_usleep(unsigned int time_in_ms);
void			take_forks(t_philos *philos, pthread_mutex_t *forks, int n);
int				init_info(int ac, char **av, t_arg *args);

#endif
