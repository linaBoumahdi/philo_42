/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_brother.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:05:25 by lboumahd          #+#    #+#             */
/*   Updated: 2024/12/10 15:55:03 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "philo.h"

// a changer 
int check_philos(t_philo *philo)
{
	long time;

	pthread_mutex_lock(&philo->data->m_meal);
	time = get_time() - philo->last_meal;
	if(time >= philo->data->t_to_die && philo->is_busy == 0)
		return(pthread_mutex_unlock(&philo->data->m_meal), 1);
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


void	*bigbrother(void *arg)
{
	t_philo *philos;

	philos = (t_philo *)arg;
	while(1)
	{
		if(stop_philo(philos))
		{
			break;
		}
	}
	return (arg);
}
