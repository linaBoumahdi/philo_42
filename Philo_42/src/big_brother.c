/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_brother.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:05:25 by lboumahd          #+#    #+#             */
/*   Updated: 2024/12/11 13:14:55 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "philo.h"


int	death_is_here(t_philo *philo)
{
	t_data *data ;
	
	data = philo->data;
	pthread_mutex_lock(&data->m_dead);
	if(*philo->is_dead == 1)
		return(pthread_mutex_unlock(&data->m_dead), 1);
	pthread_mutex_unlock(&data->m_dead);
	return (0);
}

int check_philos(t_philo *philo)
{
	long time;

	pthread_mutex_lock(&philo->data->m_meal);
	time = get_time() - philo->last_meal;
	if(time >= philo->data->t_to_die)
	{	
		pthread_mutex_unlock(&philo->data->m_meal);
		return(1);
	}
	pthread_mutex_unlock(&philo->data->m_meal);
	return (0);
}
 int	stop_philo(t_philo *philo)
 {
	int i;
	i = 0;
	
	while(i < philo->data->n_philo)
	{ 
		if (check_philos(&philo[i])) 
		{
			philo_print("died", &philo[i]);
			pthread_mutex_lock(&(philo[i].data->m_dead));
			*philo->is_dead = 1;
			pthread_mutex_unlock(&(philo[i].data->m_dead));
			return (1);
		}
		i++;
	}
	return(0);
 }
int	finished_eating(t_philo *philo)
{
	int	i;
	int	done_eating;
	i = 0;
	done_eating = 0;
	if(philo->data->meals_to_eat == -1)
		return(0);
	while(i < philo->data->n_philo)
	{
		pthread_mutex_lock(&philo->data->m_meal);
		if(philo[i].has_eaten == philo->data->meals_to_eat)
			done_eating++;
		pthread_mutex_unlock(&philo->data->m_meal);
		i++;
	}
	if (done_eating ==  philo->data->n_philo)
	{
		pthread_mutex_lock (&philo->data->m_dead);
		*philo->is_dead = 1;
		pthread_mutex_unlock (&philo->data->m_dead);
		return(1);
	}
	return(0);
}

void	*bigbrother(void *arg)
{
	t_philo *philos;

	philos = (t_philo *)arg;
	while(1)
	{
		if(stop_philo(philos) || finished_eating(philos))
			break;
	}
	return (arg);
}
