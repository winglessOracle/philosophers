/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   atol.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 15:33:04 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/06/19 15:18:47 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

long long	ft_atol(const char *str)
{
	int			i;
	long long	output;
	int			sign;

	i = 0;
	output = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		output = output * 10 + (str[i] - '0');
		i++;
	}
	return (sign * output);
}

int	check_digit(int argc, char **argv)
{
	int		i;
	int		j;
	char	*argument;

	i = 1;
	while (i < argc)
	{
		argument = argv[i];
		j = 0;
		if (argument[j] == '+')
			j++;
		while (argument[j])
		{
			if (!ft_isdigit(argument[j]))
			{
				printf("Invalid argument. Expected a positive integer\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_limits(int argc, char **argv)
{
	int		i;

	if (ft_atol(argv[1]) > MAX_THREADS)
	{
		printf("Input exceeds MAX_THREADS (%d)\n", MAX_THREADS);
		return (1);
	}
	i = 2;
	while (i < argc)
	{
		if (ft_atol(argv[i]) > INT_MAX)
		{
			printf("Input argument exceeds MAX_INT\n");
			return (1);
		}
		i++;
	}
	return (0);
}
