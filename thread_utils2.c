/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:13:50 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/12 16:45:13 by wlalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	increase_ate_count(t_philo *data)
{
	pthread_mutex_lock(&data->ate_mutex);
	data->ate_c++;
	pthread_mutex_unlock(&data->ate_mutex);
}

void	assign_currtime(t_philo *data)
{
	pthread_mutex_lock(&data[0].currtime_mutex);
	data[0].curr_time = cur_t();
	pthread_mutex_unlock(&data[0].currtime_mutex);
}

void	assign_isphilodead(t_data *d, bool value)
{
	pthread_mutex_lock(&d->args.dead_mutex);
	d->args.is_one_philo_dead = value;
	pthread_mutex_unlock(&d->args.dead_mutex);
}

void	assign_false_ifdidntfullyate(t_data *d, bool *all_philo_ate,
			size_t i, int argc)
{
	pthread_mutex_lock(&d->ph_l[i].ate_mutex);
	if (argc == 6 && d->args.eat_c > d->ph_l[i].ate_c)
		*all_philo_ate = false;
	pthread_mutex_unlock(&d->ph_l[i].ate_mutex);
}

int	trigger_die_event(t_data *d, size_t i, pthread_t *th)
{
	pthread_mutex_unlock(&d->ph_l[i].currtime_mutex);
	assign_isphilodead(d, true);
	printf_die(d, i);
	if (!join_threads(th, d->args.list_length))
		return (1);
	return (0);
}
