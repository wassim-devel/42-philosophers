/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:41:36 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/03 13:21:06 by wlalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	number;
	int	signe;

	number = 0;
	signe = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signe *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		number = number * 10 + (*str - 48);
		str++;
	}
	return (number * signe);
}

int	ft_usleep(size_t time_in_ms)
{
	size_t	begin_time;

	begin_time = cur_t();
	while ((cur_t() - begin_time) < time_in_ms)
		usleep(500);
	return (0);
}

size_t	cur_t(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}
