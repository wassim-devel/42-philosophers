/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:01:35 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/12 16:50:17 by wlalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	args_init(int argc, char **argv, t_data *dt_t_r)
{
	dt_t_r->args.is_one_philo_dead = false;
	dt_t_r->args.list_length = ft_atoi(argv[1]);
	dt_t_r->args.time_to_die = ft_atoi(argv[2]);
	dt_t_r->args.time_to_eat = ft_atoi(argv[3]);
	dt_t_r->args.time_to_sleep = ft_atoi(argv[4]);
	dt_t_r->args.b_t = cur_t();
	pthread_mutex_init(&dt_t_r->args.dead_mutex, NULL);
	pthread_mutex_init(&dt_t_r->args.printf_mutex, NULL);
	if (argc == 6)
		dt_t_r->args.eat_c
			= ft_atoi(argv[5]);
}

t_data	*init_values(int argc, char **argv)
{
	t_data	*dt_t_r;
	int		i;

	dt_t_r = malloc(sizeof(t_data));
	if (!dt_t_r)
		return (NULL);
	i = 0;
	dt_t_r->ph_l = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!dt_t_r->ph_l)
		return (free(dt_t_r), NULL);
	args_init(argc, argv, dt_t_r);
	while (i < ft_atoi(argv[1]))
	{
		init_loop(dt_t_r, i);
		pthread_mutex_init(&dt_t_r->ph_l[i].l_fork.mutex, NULL);
		pthread_mutex_init(&dt_t_r->ph_l[i].currtime_mutex, NULL);
		pthread_mutex_init(&dt_t_r->ph_l[i].ate_mutex, NULL);
		if (i != ft_atoi(argv[1]) - 1)
			dt_t_r->ph_l[i].r_fork = &dt_t_r->ph_l[i + 1].l_fork;
		else
			dt_t_r->ph_l[i].r_fork = &dt_t_r->ph_l[0].l_fork;
		i++;
	}
	return (dt_t_r);
}

int	philo_eat(t_philo *data)
{
	if (data[0].args->list_length == 1)
		return (0);
	return (philo_eat_normal(data));
}

void	*routine(void *arg)
{
	t_philo	*data;

	data = arg;
	pthread_mutex_lock(&data[0].currtime_mutex);
	data[0].curr_time = cur_t();
	pthread_mutex_unlock(&data[0].currtime_mutex);
	if (data->i % 2 == 0)
		ft_usleep(data->args->time_to_eat / 10);
	while (1)
	{
		pthread_mutex_lock(&data->args->dead_mutex);
		if (data->args->is_one_philo_dead == true)
			return (pthread_mutex_unlock(&data->args->dead_mutex), NULL);
		pthread_mutex_unlock(&data->args->dead_mutex);
		printf_think(data);
		if (!philo_eat(data))
			return (NULL);
		pthread_mutex_lock(&data->args->dead_mutex);
		if (data->args->is_one_philo_dead == true)
			return (pthread_mutex_unlock(&data->args->dead_mutex), NULL);
		pthread_mutex_unlock(&data->args->dead_mutex);
		printf_sleep(data);
		ft_usleep(data->args->time_to_sleep);
	}
}

int	threading(char **argv, t_data *data, pthread_t *th)
{
	int			i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		if (pthread_create(&th[i], NULL, &routine, &data->ph_l[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}
