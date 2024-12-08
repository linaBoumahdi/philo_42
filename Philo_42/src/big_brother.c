/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_brother.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:05:25 by lboumahd          #+#    #+#             */
/*   Updated: 2024/12/08 20:15:39 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "philo.h"

void check_philos(t_philo *philo)
{
	long time;

	pthread_mutex_lock(&philo->data->m_meal);
	time = get_time() - philo->last_meal;
	if(time >= philo->data->t_to_die)
		philo->is_dead = 1;
	pthread_mutex_unlock(&philo->data->m_meal);
}
 int	stop_philo(t_philo *philo)
 {
	int i;
	i = 0;

	while(i < philo->data->n_philo)
	{
		printf("is philo [%d]\n", i);
		check_philos(&philo[i]); 
		if (philo[i].is_dead) 
		{
			philo_print("is dead\n", &philo[i]);
			pthread_mutex_lock(&(philo[i].data)->m_dead);
			philo->data->stop_philo = 1;
			pthread_mutex_unlock(&(philo[i].data)->m_dead);
			return (10);
		}
		i++;
	}
	return(0);
 }

//check starvation ???/ 
//  int	are_full(t_philo *philo)
//  {
// 	//check if they all ate the av[5]
//  }

void	*bigbrother(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while(1)
	{
		// if(stop_philo(philo) || are_full(philo))
		// 	break;
		if(stop_philo(philo) == 10)
		{
			printf("hey\n");
			break;
		}
	//		break;
	}
	return (NULL);
}
