/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:36:11 by lboumahd          #+#    #+#             */
/*   Updated: 2024/12/11 14:42:41 by lboumahd         ###   ########.fr       */
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
	while ((get_time() - start) < time)
		usleep(500);

}

void	free_mutex(t_data *data)
{
	int i;

	i = 0;
	pthread_mutex_destroy(&data->m_print);
	pthread_mutex_destroy(&data->m_meal);
	pthread_mutex_destroy(&data->m_dead);
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	free(data->philos);
}
int	is_dig(char *av)
{
	int i;

	i = 0;
	while(av[i])
	{
		if(av[i] < '0' || av[i] > '9')
			return(0);
		i++;
	}
	return (1);
}
int	check_data (char **av)
{
	if(ft_atoi(av[1]) > 400 || ft_atoi(av[1]) <= 0 
	|| !is_dig(av[1]))
		return(write(2, "Invalid arg\n", 12), 1);
	if(ft_atoi(av[2]) <= 0 || !is_dig(av[2]))
		return(write(2, "Invalid arg\n", 12), 1);
	if(ft_atoi(av[3]) <= 0 || !is_dig(av[3]))
		return(write(2, "Invalid ar3\n", 12), 1);
	if(ft_atoi(av[4]) <= 0 || !is_dig(av[4]))
		return(write(2, "Invalid arg\n", 12), 1);
	if(av[5] && (ft_atoi(av[5]) < 0 || !is_dig(av[5])))
		return(write(2, "Invalid arg\n", 12), 1);
	return(0);
}
