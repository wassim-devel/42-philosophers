/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:36:15 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/12 15:56:25 by wlalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printf_sleep(t_philo *data)
{
	pthread_mutex_lock(&data->args->printf_mutex);
	printf("%ld %ld is sleeping\n",
		cur_t() - data->args->b_t, data->i);
	pthread_mutex_unlock(&data->args->printf_mutex);
}

void	printf_eat(t_philo *data)
{
	pthread_mutex_lock(&data->args->printf_mutex);
	printf("%ld %ld is eating\n",
		cur_t() - data->args->b_t, data->i);
	pthread_mutex_unlock(&data->args->printf_mutex);
}

void	printf_fork(t_philo *data)
{
	pthread_mutex_lock(&data->args->printf_mutex);
	printf("%ld %ld has taken a fork\n",
		cur_t() - data->args->b_t, data->i);
	pthread_mutex_unlock(&data->args->printf_mutex);
}

void	printf_think(t_philo *data)
{
	pthread_mutex_lock(&data->args->printf_mutex);
	printf("%ld %ld is thinking\n",
		cur_t() - data->args->b_t, data->i);
	pthread_mutex_unlock(&data->args->printf_mutex);
}

void	printf_die(t_data *d, size_t i)
{
	pthread_mutex_lock(&d->args.printf_mutex);
	printf("%ld %ld died\n",
		cur_t() - d->args.b_t, d->ph_l[i].i);
	pthread_mutex_unlock(&d->args.printf_mutex);
}
