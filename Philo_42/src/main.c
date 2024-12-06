/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:00:39 by lboumahd          #+#    #+#             */
/*   Updated: 2024/12/06 16:32:25 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//utils 
//get_time;
//ft_usleep
//atoi 
//ft_print
// int	check_data()
// {
// 	//checks if !digit and value <=0
// }
int	init_data(t_data *data, char **av)
{

	// if(check_data(av) == -1)
	// 	return(-1);
	data->n_philo = ft_atoi(av[1]);
	data->t_to_die = ft_atoi(av[2]);
	data->t_to_eat = ft_atoi(av[3]);
	data->t_to_sleep = ft_atoi(av[4]);
	data->stop_philo = 0; // ?????????
	if (av[5])
		data->meals_to_eat = ft_atoi(av[5]);
	else
		data->meals_to_eat = -1;
	return(0);
}


void	is_thinking(t_philo *philo)
{
	philo_print("is thinking", philo);
}

void	philo_print(char *arg, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_print);
	printf("%s\n", arg); 
	pthread_mutex_unlock(&philo->data->m_print);
}
void	*routine(void *arg)
{
	t_philo *philo;
	int i;

	i = 0;
	philo = (t_philo *)arg;
	while(i < 10)
	{
		is_thinking(philo);
		i++;
	}
	return (NULL);
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
		data->philos[i].last_meal = get_time(); // ???????
		data->philos[i].p_id = i;
		data->philos[i].t_id = 0;
		data->philos[i].data = data;
		i++;
	}
	return(0);
}

int init_mutex(t_data *data)
{
	int i;

	i = 0;
	if(pthread_mutex_init(&data->m_print, NULL))
		return(-1);
	return(0);
}
int	start_philo(t_data *data)
{
	int i;

	i = 0;
	
	
	if(init_mutex(data) == -1)
	{
		
		return(-1);
	}
	if(init_philo(data) == -1)
	{
	
		return (-1); 
	}
	while(i < data->n_philo)
	{
		printf("%d\n", i);
		if(pthread_create(&data->philos[i].t_id, NULL, routine, &(data->philos[i])))
		{
   			 perror("Thread creation failed");
  			  return (-1);
		}
	
		i++;
	}
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
int main(int ac, char **av)
{
	t_data	data;

	if(ac != 5 && ac != 6)
		return(-1);

	if(init_data(&data, av) != 0)
		return(-1);
	if(start_philo(&data) == -1)
		return(-1);
 
	free_mutex(&data);
	// free(data);
	return(0);
}