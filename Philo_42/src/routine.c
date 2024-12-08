/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:32:45 by lboumahd          #+#    #+#             */
/*   Updated: 2024/12/08 20:06:52 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time(void)
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
	printf("philo[%d] %s ", philo->p_id, arg); 
	// a completer et indexer philo ID
	pthread_mutex_unlock(&philo->data->m_print);
}

void	is_eating(t_philo *philo)
{
	t_data *data;

	data = philo->data;
	//add eat flag ??????
	pthread_mutex_lock(philo->l_fork);
	philo_print("l_fork is locked\n", philo);
	pthread_mutex_lock(philo->r_fork);
	philo_print("r_fork is locked\n", philo);
	pthread_mutex_lock(&data->m_meal);
	philo_print("is eating\n", philo);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&data->m_meal);
	ft_usleep(data->t_to_eat);
	philo->has_eaten++;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	is_sleeping(t_philo *philo)
{
	ft_usleep(philo->data->t_to_sleep);
}

void	is_thinking(t_philo *philo)
{
	philo_print("is thinking", philo);
}