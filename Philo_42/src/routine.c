/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:32:45 by lboumahd          #+#    #+#             */
/*   Updated: 2024/12/11 13:15:16 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
void	philo_print(char *arg, t_philo *philo)
{
	int time;
	pthread_mutex_lock(&philo->data->m_print);
	time = get_time() - philo->has_started; 
	if(!death_is_here(philo))
		printf("%i %d %s\n",time, philo->p_id, arg); 
	pthread_mutex_unlock(&philo->data->m_print);
}

void	is_eating(t_philo *philo)
{
	t_data *data;

	data = philo->data;
	pthread_mutex_lock(philo->l_fork);
	philo_print("has taken a fork", philo);
	pthread_mutex_lock(philo->r_fork);
	philo_print("has taken a fork", philo);
	pthread_mutex_lock(&data->m_meal);
	philo_print("is eating", philo);
	philo->last_meal = get_time();
	philo->has_eaten++;
	pthread_mutex_unlock(&data->m_meal);
	ft_usleep(data->t_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->p_id % 2 != 0)
		ft_usleep(philo->data->t_to_eat);
	 while(!death_is_here(philo))
	{
		is_eating(philo);
		philo_print("is sleeping", philo);
		ft_usleep(philo->data->t_to_sleep);
		philo_print("is thinking", philo);
	}
	return (arg);
}