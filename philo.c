/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:28:44 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/12 15:26:53 by wlalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	small_check_error(int argc, char **argv)
{
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0
		|| ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0)
		return (1);
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) < 0)
			return (1);
		if (ft_atoi(argv[5]) == 0)
			return (2);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t	*th;
	t_data		*data;

	if (argc == 5 || argc == 6)
	{
		if (small_check_error(argc, argv))
			return (1);
		else if (small_check_error(argc, argv) == 2)
			return (0);
		data = init_values(argc, argv);
		if (!data)
			return (1);
		th = malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
		if (!th)
			return (1);
		if (!threading(argv, data, th))
			return (1);
		ft_usleep(2);
		if (is_finished(argc, data, th))
			return (1);
		return (0);
	}
	else
		printf("Not the good number of args\n");
}
