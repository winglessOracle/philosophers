/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread_ops.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/30 10:28:45 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/06/19 10:08:50 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	make_threads(t_gdata *g_data, t_data *data)
{
	int	i;

	i = 0;
	while (i < g_data->num_philo)
	{
		data = malloc(sizeof(t_data));
		if (!data)
			return (1);
		if (init_data(i, data, g_data))
			return (1);
		if (pthread_create(&g_data->threads[i], NULL, &routine, data) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	join_threads(t_gdata *g_data)
{
	int	i;

	i = 0;
	while (i < g_data->num_philo)
	{
		if (pthread_join(g_data->threads[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	destroy_mutex_free(t_gdata *g_data)
{
	int	i;

	i = 0;
	while (i < g_data->num_philo)
	{
		pthread_mutex_destroy(&g_data->mutex_forks[i]);
		i++;
	}
	pthread_mutex_destroy(&g_data->mutex_print);
	pthread_mutex_destroy(&g_data->mutex_death);
	free_gdata(g_data);
}
