/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:26:40 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/12 16:49:41 by wlalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}				t_fork;

typedef struct s_args
{
	size_t			time_to_sleep;
	size_t			time_to_eat;
	size_t			time_to_die;
	size_t			eat_c;
	size_t			b_t;
	size_t			list_length;
	bool			is_one_philo_dead;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	printf_mutex;
}			t_args;

typedef struct s_philo
{
	size_t			ate_c;
	pthread_mutex_t	ate_mutex;
	size_t			curr_time;
	pthread_mutex_t	currtime_mutex;
	size_t			i;
	t_args			*args;
	t_fork			l_fork;
	t_fork			*r_fork;
}				t_philo;

typedef struct s_data
{
	t_args	args;
	t_philo	*ph_l;
}				t_data;

//init_and_threading.c
t_data	*init_values(int argc, char **argv);
int		threading(char **argv, t_data *data, pthread_t *th);

//init_util.c
void	init_loop(t_data *data, int i);

//utils.c
int		ft_atoi(const char *str);
int		ft_usleep(size_t time_in_ms);
size_t	cur_t(void);

//philo_eat_funcs.c
int		philo_eat_normal(t_philo *data);
int		is_finished(int argc, t_data *d, pthread_t *th);

//frees.c
void	free_all(pthread_t *th, t_data *data, size_t n);
int		join_threads(pthread_t *th, size_t length);

//thread_utils.c
void	printf_think(t_philo *data);
void	printf_sleep(t_philo *data);
void	printf_eat(t_philo *data);
void	printf_fork(t_philo *data);
void	printf_die(t_data *data, size_t i);

//thread_utils2.c
void	increase_ate_count(t_philo *data);
void	assign_currtime(t_philo *data);
void	assign_isphilodead(t_data *d, bool value);
void	assign_false_ifdidntfullyate(t_data *d, bool *all_philo_ate, size_t i,
			int argc);
int		trigger_die_event(t_data *d, size_t i, pthread_t *th);

#endif
