/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checks.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 11:40:48 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/06/19 10:29:38 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_game_over(t_data *data)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&data->g_data->mutex_death);
	if (data->g_data->game_over)
		ret = 1;
	pthread_mutex_unlock(&data->g_data->mutex_death);
	return (ret);
}

int	check_eat_time(t_data *data)
{
	if (data->g_data->time_to_eat >= data->g_data->time_to_die)
	{
		put_message(data, 1, data->time_last_eat);
		ft_msleep(data->g_data, data->g_data->time_to_die);
		put_message(data, 4, timestamp(data->g_data));
		return (1);
	}
	return (0);
}

int	check_sleep_time(t_data *data)
{
	if (data->g_data->time_to_sleep >= data->g_data->time_to_die \
		- data->g_data->time_to_eat)
	{
		put_message(data, 2, timestamp(data->g_data));
		ft_msleep(data->g_data, data->g_data->time_to_die \
			- data->g_data->time_to_eat);
		put_message(data, 4, timestamp(data->g_data));
		return (1);
	}
	return (0);
}

int	check_times_eaten(t_data *data)
{
	if (data->g_data->num_must_eat != 0)
	{
		data->times_eaten++;
		if (data->times_eaten >= data->g_data->num_must_eat)
			return (1);
	}
	return (0);
}

int	check_time_to_die(t_data *data)
{
	unsigned long	time;

	time = timestamp(data->g_data);
	if ((time - data->time_last_eat) >= data->g_data->time_to_die)
	{
		put_message(data, 4, time);
		return (1);
	}
	return (0);
}
