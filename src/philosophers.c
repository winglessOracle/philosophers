/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 09:56:54 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/06/22 14:18:21 by wingessorac   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	put_forks(t_data *data)
{
	pthread_mutex_lock(&data->g_data->mutex_forks[data->fork_num_1]);
	data->g_data->forks[data->fork_num_1] = 1;
	pthread_mutex_unlock(&data->g_data->mutex_forks[data->fork_num_1]);
	pthread_mutex_lock(&data->g_data->mutex_forks[data->fork_num_2]);
	data->g_data->forks[data->fork_num_2] = 1;
	pthread_mutex_unlock(&data->g_data->mutex_forks[data->fork_num_2]);
}

int	get_forks(t_data *data)
{
	data->forks_in_hand = 0;
	while (data->forks_in_hand < 2)
	{
		pthread_mutex_lock(&data->g_data->mutex_forks[data->fork_num_1]);
		if (data->g_data->forks[data->fork_num_1] == 1)
		{
			put_message(data, 0, timestamp(data->g_data));
			data->g_data->forks[data->fork_num_1] = 0;
			data->forks_in_hand++;
		}
		pthread_mutex_unlock(&data->g_data->mutex_forks[data->fork_num_1]);
		if (check_time_to_die(data))
			return (1);
		pthread_mutex_lock(&data->g_data->mutex_forks[data->fork_num_2]);
		if (data->g_data->forks[data->fork_num_2] == 1)
		{
			put_message(data, 0, timestamp(data->g_data));
			data->g_data->forks[data->fork_num_2] = 0;
			data->forks_in_hand++;
		}
		pthread_mutex_unlock(&data->g_data->mutex_forks[data->fork_num_2]);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_data			*data;

	data = arg;
	data->time_last_eat = timestamp(data->g_data);
	if (data->thread_no % 2 == 0)
		ft_msleep(data->g_data, 5);
	while (!check_game_over(data))
	{
		put_message(data, 3, timestamp(data->g_data));
		if (get_forks(data) == 1)
			return (free(data), NULL);
		data->time_last_eat = timestamp(data->g_data);
		if (check_eat_time(data))
			return (free(data), NULL);
		put_message(data, 1, data->time_last_eat);
		ft_msleep(data->g_data, data->g_data->time_to_eat);
		put_forks(data);
		if (check_times_eaten(data) || check_sleep_time(data))
			return (free(data), NULL);
		put_message(data, 2, timestamp(data->g_data));
		ft_msleep(data->g_data, data->g_data->time_to_sleep);
	}
	return (free(data), NULL);
}

int	main(int argc, char **argv)
{
	t_gdata		*g_data;
	t_data		*data;

	data = NULL;
	if (check_arguments(argc, argv))
		return (FAILD_ARGUMENTS);
	g_data = malloc(sizeof(t_gdata));
	if (!g_data)
		return (FAILD_MALLOC_GDATA);
	if (init_gdata(argc, argv, g_data))
		return (destroy_mutex_free(g_data), FAILD_INIT_GDATA);
	gettimeofday(&g_data->start_time, NULL);
	if (make_threads(g_data, data))
		return (destroy_mutex_free(g_data), FAILD_MAKE_THREADS);
	if (join_threads(g_data))
		return (destroy_mutex_free(g_data), FAILD_JOIN_THREADS);
	if (!g_data->game_over && argv[5])
		printf("%ld All Philosophers are full after %d meal(s)\n", \
			timestamp(g_data), g_data->num_must_eat);
	return (destroy_mutex_free(g_data), 0);
}
