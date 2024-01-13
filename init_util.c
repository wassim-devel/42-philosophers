/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:48:41 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/12 16:51:29 by wlalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_loop(t_data *data, int i)
{
	data->ph_l[i].curr_time = 0;
	data->ph_l[i].i = i + 1;
	data->ph_l[i].ate_c = 0;
	data->ph_l[i].args = &data->args;
}
