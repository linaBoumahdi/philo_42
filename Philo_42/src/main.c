/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:00:39 by lboumahd          #+#    #+#             */
/*   Updated: 2024/12/05 18:32:01 by lboumahd         ###   ########.fr       */
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

// int	keep_running(t_data *data)
// {
// 	//all_eaten
// 	//one_dead->return -1
// 	if (check_if_dead(data->philos) == 1 || check_if_all_ate(data->philos) == 1)
// 			return(0);
// 	return(1);
// }
void	*routine(void *arg)
{
	t_philo *philo;
	int i;

	i = 0;
	philo = (t_philo *)arg;
	// while(keep_running(philo->data))//separete between lonely philo :(
	while(1)
	{
		is_eating(philo);
		is_sleeping(philo);
		is_thinking(philo);
	}
	return (NULL);
}

void	assign_forks(t_data * data, int i)
{
	if(i == 0)
	{
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[data->n_philo];
	}	
	else if (i % 2 == 0)
	{
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[i - 1];
	}
	else
	{
		data->philos[i].l_fork = &data->forks[i - 1];
		data->philos[i].r_fork = &data->forks[i];
	}
}
int	init_philo(t_data *data)
{
	int i;

	i = 0;
	data->philos = malloc (sizeof(t_philo *));
	if(!data->philos)
		return(-1);
	while(i++ < data->n_philo)
	{
		data->philos[i].has_started = get_time();
		data->philos[i].has_eaten = 0;
		data->philos[i].last_meal = get_time(); // ???????
		data->philos[i].p_id = i;
		assign_forks(data, i);
	}
	return(0);
}

int init_mutex(t_data *data)
{
	int i;

	i = 0;
	while(i++ < data->n_philo)// check incrementation
	{
		if(pthread_mutex_init(&data->forks[i], NULL) == -1)
			return(-1);
			//destroy_philo(data);// or 0 ??? // a coder	
	}
	if(pthread_mutex_init(&data->m_print, NULL) == -1)
		return(-1);
	if(pthread_mutex_init(&data->m_dead, NULL) == -1)
		return(-1);
	if(pthread_mutex_init(&data->m_meal, NULL) == -1)
		return(-1);
	return(0);
}
int	start_philo(t_data *data)
{
	int i;

	i = 0;
	data->forks = malloc (sizeof(pthread_t) * data->n_philo);
	if (!data->forks)
			return(-1);
	if(init_philo(data) == -1)
	{
		free(data->forks);
		return (-1); // a voir
	}
	if(init_mutex(data) == -1)
	{
		free(data->forks);
		free(data->philos);
		return(-1);
	}
	while(i++ < data->n_philo)// check incrementation
	{
		if(pthread_create(&data->philos[i].t_id, NULL, &routine, &data->philos[i]))
			free_mutex(data);//free philos and forks also
		// if(data->n_philo == 1)
		// 	{
		// 		lonely_philo();
		// 		break;
		// 	}
	}
	//rip_philo(data); // check if dead
	//quit_philo(data);
	return(0);
}
int main(int ac, char **av)
{
	t_data	*data;

	if(ac != 5 && ac != 6)
		return(-1);//error a gerer 
	data = malloc(sizeof(t_data *));
	if(init_data(data, av) != 0)
		return(-1);
	if(start_philo(data) == -1)
		return(-1);
	// //potentially ? 
	free_mutex(data); // ptential seg fault 
	free(data);
	return(0);
}