/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 11:44:10 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/06/19 10:41:05 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	timestamp(t_gdata *g_data)
{
	unsigned long	timestp;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	timestp = (current_time.tv_sec - g_data->start_time.tv_sec) \
	* 1000 + (current_time.tv_usec - g_data->start_time.tv_usec) / 1000;
	return (timestp);
}

void	ft_msleep(t_gdata *g_data, unsigned long milliseconds)
{
	unsigned long	current_time;

	current_time = timestamp(g_data);
	while ((timestamp(g_data) - current_time) < milliseconds)
		usleep(500);
}

void	put_message(t_data *data, t_message msg, unsigned long time)
{
	pthread_mutex_lock(&data->g_data->mutex_print);
	if (msg == 0 && (!check_game_over(data)))
		printf("%ld %d %s\n", time, data->thread_no, "has taken a fork");
	if (msg == 1 && (!check_game_over(data)))
		printf("%ld %d %s\n", time, data->thread_no, "is eating");
	if (msg == 2 && (!check_game_over(data)))
		printf("%ld %d %s\n", time, data->thread_no, "is sleeping");
	if (msg == 3 && (!check_game_over(data)))
		printf("%ld %d %s\n", time, data->thread_no, "is thinking");
	if (msg == 4)
	{
		pthread_mutex_lock(&data->g_data->mutex_death);
		if (data->g_data->game_over == 0)
		{
			printf("%ld %d %s\n", time, data->thread_no, "died");
			data->g_data->game_over = 1;
		}
		pthread_mutex_unlock(&data->g_data->mutex_death);
	}
	pthread_mutex_unlock(&data->g_data->mutex_print);
}

void	free_gdata(t_gdata *gdata)
{
	(void)gdata;
	if (gdata->forks != NULL)
		free(gdata->forks);
	if (gdata->mutex_forks != NULL)
		free(gdata->mutex_forks);
	if (gdata->threads != NULL)
		free(gdata->threads);
	gdata->forks = NULL;
	gdata->mutex_forks = NULL;
	gdata->threads = NULL;
	if (gdata)
		free(gdata);
	gdata = NULL;
}
