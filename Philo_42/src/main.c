/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:00:39 by lboumahd          #+#    #+#             */
/*   Updated: 2024/12/11 14:34:03 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	init_data(t_data *data, char **av)
{
	data->n_philo = ft_atoi(av[1]);
	data->t_to_die = ft_atoi(av[2]);
	data->t_to_eat = ft_atoi(av[3]);
	data->t_to_sleep = ft_atoi(av[4]);
	data->stop_philo = 0;
	if (av[5])
		data->meals_to_eat = ft_atoi(av[5]);
	else
		data->meals_to_eat = -1;
	return(0);
}

int	init_philo(t_data *data)
{
	int i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->n_philo);
	if(!data->philos)
		return(-1);
	while(i < data->n_philo)
	{
		data->philos[i].has_started = get_time();
		data->philos[i].has_eaten = 0;
		data->philos[i].last_meal = get_time();
		data->philos[i].p_id = i + 1;
		data->philos[i].t_id = 0;
		data->philos[i].data = data;
		data->philos[i].is_dead = &data->stop_philo;
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[(i + 1) % data->n_philo];
		i++;
	}
	return(0);
}

int init_mutex(t_data *data)
{
	int i;

	i = 0;
	while(i < data->n_philo)
	{
		if(pthread_mutex_init(&data->forks[i], NULL))
			return(-1)	;
			i++;
	}
	if(pthread_mutex_init(&data->m_print, NULL))
		return(-1);
	if(pthread_mutex_init(&data->m_dead, NULL))
		return(-1);
	if(pthread_mutex_init(&data->m_meal, NULL))
		return(-1);
	return(0);
}
int	init_threads(t_data *data)
{
	pthread_t big_brother;
	int	i;

	i = -1;
	if(pthread_create(&big_brother, NULL, &bigbrother, data->philos))
		return(-1);
	while(++i < data->n_philo)
	{
		if(pthread_create(&data->philos[i].t_id, NULL, &routine, &(data->philos[i])))
		{
   			 perror("Thread creation failed");
  			  return (-1);
		}
	}
	if(pthread_join(big_brother, NULL) != 0)
		return (-1);
	for(i = 0; i < data->n_philo; i++)
    {
        if(pthread_join(data->philos[i].t_id, NULL) != 0)
        {
		    perror("Thread join failed");
            return (-1);
        }
    }
	return(0);
}
int	start_philo(t_data *data)
{
	int i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->forks)
			return(-1);
	if(init_mutex(data) == -1)
	{
		free(data->forks);
		return(-1);
	}
	if(init_philo(data) == -1)
	{
		free_mutex(data); 
		free(data->forks);
		return (-1);
	}
	if (init_threads(data) == -1)
	{
		free_mutex(data); 
		free(data->forks);
		free(data->philos);
		return (-1);
	}	
	return(0);
}

int main(int ac, char **av)
{
	t_data	data;

	if(ac != 5 && ac != 6)
		return(-1);
	if (check_data(av))
		return(-1);
	if(init_data(&data, av) != 0)
		return(-1);
	if(start_philo(&data) == -1)
		return(-1);
	free_mutex(&data); 
	return(0);
}