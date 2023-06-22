/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 09:41:36 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/06/22 14:17:11 by wingessorac   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>

# ifndef MAX_THREADS
#  define MAX_THREADS 10240
# endif

# define FAILD_ARGUMENTS 1
# define FAILD_MALLOC_GDATA 2
# define FAILD_INIT_GDATA 3
# define FAILD_MAKE_THREADS 4
# define FAILD_JOIN_THREADS 5

typedef enum e_message
{
	FORK = 0,
	EAT,
	SLEEP,
	THINK,
	DEAD,
}	t_message;

typedef struct s_gdata
{
	int					num_philo;
	int					*forks;
	pthread_t			*threads;
	pthread_mutex_t		*mutex_forks;
	pthread_mutex_t		mutex_print;
	pthread_mutex_t		mutex_death;
	struct timeval		start_time;
	unsigned long		time_to_die;
	unsigned long		time_to_eat;
	unsigned long		time_to_sleep;
	int					num_must_eat;
	int					game_over;
}	t_gdata;

typedef struct s_data
{
	unsigned long		time_last_eat;
	int					times_eaten;
	int					thread_no;
	int					fork_num_1;
	int					fork_num_2;
	int					forks_in_hand;
	t_gdata				*g_data;
}	t_data;

void			*routine(void *arg);

//utils
unsigned long	timestamp(t_gdata *data);
void			ft_msleep(t_gdata *data, unsigned long milliseconds);
void			put_message(t_data *data, t_message msg, unsigned long time);
void			free_gdata(t_gdata *data);

//checks
int				check_game_over(t_data *data);
int				check_eat_time(t_data *data);
int				check_sleep_time(t_data *data);
int				check_times_eaten(t_data *data);
int				check_time_to_die(t_data *data);

//init
int				check_arguments(int argc, char **argv);
int				init_gdata(int argc, char **argv, t_gdata *g_data);
int				init_data(int i, t_data *data, t_gdata *g_data);

//thread_ops
int				make_threads(t_gdata *g_data, t_data *data);
int				join_threads(t_gdata *g_data);
void			destroy_mutex_free(t_gdata *g_data);

//atoi
int				ft_isdigit(int c);
long long		ft_atol(const char *str);
int				check_digit(int argc, char **argv);
int				check_limits(int argc, char **argv);

#endif
