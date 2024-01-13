/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat_funcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:29:29 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/12 17:04:00 by wlalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_dead(t_philo *data)
{
	pthread_mutex_lock(&data->args->dead_mutex);
	if (data->args->is_one_philo_dead == true)
		return (pthread_mutex_unlock(&data->l_fork.mutex),
			pthread_mutex_unlock(&data->r_fork->mutex),
			pthread_mutex_unlock(&data->args->dead_mutex), 0);
	pthread_mutex_unlock(&data->args->dead_mutex);
	return (1);
}

int	philo_eat_normal(t_philo *data)
{
	pthread_mutex_lock(&data->args->dead_mutex);
	if (data->args->is_one_philo_dead == true)
		return (pthread_mutex_unlock(&data->args->dead_mutex), 0);
	pthread_mutex_unlock(&data->args->dead_mutex);
	pthread_mutex_lock(&data->l_fork.mutex);
	pthread_mutex_lock(&data->args->dead_mutex);
	if (data->args->is_one_philo_dead == true)
		return (pthread_mutex_unlock(&data->l_fork.mutex),
			pthread_mutex_unlock(&data->args->dead_mutex), 0);
	pthread_mutex_unlock(&data->args->dead_mutex);
	printf_fork(data);
	pthread_mutex_lock(&data->r_fork->mutex);
	if (!check_if_dead(data))
		return (0);
	printf_fork(data);
	assign_currtime(data);
	printf_eat(data);
	ft_usleep(data->args->time_to_eat);
	increase_ate_count(data);
	pthread_mutex_unlock(&data->r_fork->mutex);
	pthread_mutex_unlock(&data->l_fork.mutex);
	return (1);
}

bool	did_philo_ate(int argc, bool all_philo_ate, t_data *data, pthread_t *th)
{
	if (argc == 6 && all_philo_ate == true)
	{
		pthread_mutex_lock(&data->args.dead_mutex);
		data->args.is_one_philo_dead = true;
		pthread_mutex_unlock(&data->args.dead_mutex);
		if (!join_threads(th, data->args.list_length))
			return (1);
		free_all(th, data, data->args.list_length);
		return (true);
	}
	return (false);
}

int	is_finished(int argc, t_data *d, pthread_t *th)
{
	bool	all_philo_ate;
	size_t	i;

	while (1)
	{
		i = 0;
		all_philo_ate = true;
		while (i < d->args.list_length)
		{
			pthread_mutex_lock(&d->ph_l[i].currtime_mutex);
			if (cur_t() - d->ph_l[i].curr_time > d->args.time_to_die)
			{
				if (trigger_die_event(d, i, th) == 1)
					return (1);
				free_all(th, d, d->args.list_length);
				return (0);
			}
			pthread_mutex_unlock(&d->ph_l[i].currtime_mutex);
			assign_false_ifdidntfullyate(d, &all_philo_ate, i, argc);
			i++;
		}
		if (did_philo_ate(argc, all_philo_ate, d, th))
			return (0);
		ft_usleep(2);
	}
}
