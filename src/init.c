/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/30 10:05:24 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/06/19 15:17:49 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_arguments(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Invalid number of arguments. Expected 4 or 5\n");
		return (1);
	}
	if (check_digit(argc, argv) || check_limits(argc, argv))
		return (1);
	return (0);
}

void	set_values(int argc, char **argv, t_gdata *g_data)
{
	g_data->game_over = 0;
	g_data->num_philo = (int)ft_atol(argv[1]);
	g_data->time_to_die = (unsigned long)ft_atol(argv[2]);
	g_data->time_to_eat = (unsigned long)ft_atol(argv[3]);
	g_data->time_to_sleep = (unsigned long)ft_atol(argv[4]);
	if (argc == 6)
		g_data->num_must_eat = (int)ft_atol(argv[5]);
	else
		g_data->num_must_eat = 0;
}

int	init_gdata(int argc, char **argv, t_gdata *g_data)
{
	int	i;

	i = 0;
	set_values(argc, argv, g_data);
	g_data->threads = malloc(sizeof(pthread_t) * (g_data->num_philo));
	if (!g_data->threads)
		return (1);
	g_data->forks = malloc(sizeof(int) * g_data->num_philo);
	if (!g_data->forks)
		return (1);
	g_data->mutex_forks = malloc(sizeof(pthread_mutex_t) * g_data->num_philo);
	if (!g_data->mutex_forks)
		return (1);
	while (i < g_data->num_philo)
	{
		g_data->forks[i] = 1;
		if (pthread_mutex_init(&g_data->mutex_forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&g_data->mutex_print, NULL) != 0 \
		|| pthread_mutex_init(&g_data->mutex_death, NULL) != 0)
		return (1);
	return (0);
}

int	init_data(int i, t_data *data, t_gdata *g_data)
{
	i++;
	data->g_data = g_data;
	data->times_eaten = 0;
	data->thread_no = i;
	data->fork_num_1 = i - 1;
	if (data->thread_no == 1)
		data->fork_num_2 = data->g_data->num_philo - 1;
	else
		data->fork_num_2 = i - 2;
	return (0);
}
