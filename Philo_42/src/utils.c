/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:36:11 by lboumahd          #+#    #+#             */
/*   Updated: 2024/12/06 16:33:22 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

long	ft_atoi(const char *arg)
{
	int		i;
	int		neg;
	long	value;

	i = 0;
	value = 0;
	neg = 0;
	while ((arg[i] == ' ' || (arg[i] >= 9 && arg[i] <= 13)))
		i++;
	if (arg[i] == '-')
		neg = 1;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i] != '\0' && ft_isdigit(arg[i]))
	{
		if (value > 922337203685477580 || (value == 922337203685477580
				&& ((!neg && arg[i] - '0' > 7) || (neg && arg[i] - '0' > 8))))
			return (-1 * !neg);
		else
			value = (value * 10) + arg[i++] - '0';
	}
	if (neg)
		value = -value;
	return (value);
}


void	ft_usleep(long time)
{
	long	start;

	start = get_time();
	if (start == -1)
		return ;
	while ( (long)get_time() - start < time)
		usleep(500);
}

void	free_mutex(t_data *data)
{
	int i;

	i = 0;
	pthread_mutex_destroy(&data->m_print);
	// pthread_mutex_destroy(&data->m_meal);
	// pthread_mutex_destroy(&data->m_dead);
// 	while (i < data->n_philo)
// 	{
// 		pthread_mutex_destroy(&data->forks[i]);
// 		i++;
// 	}
}