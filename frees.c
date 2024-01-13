/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:36:35 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/12 15:25:15 by wlalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads(pthread_t *th, size_t length)
{
	size_t	i;

	i = 0;
	while (i < length)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

void	free_all(pthread_t *th, t_data *data, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&data->ph_l[i].l_fork.mutex);
		pthread_mutex_destroy(&data->ph_l[i].currtime_mutex);
		pthread_mutex_destroy(&data->ph_l[i].ate_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->args.dead_mutex);
	pthread_mutex_destroy(&data->args.printf_mutex);
	free(th);
	free(data->ph_l);
	free(data);
}
