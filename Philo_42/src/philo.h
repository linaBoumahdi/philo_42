/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:00:56 by lboumahd          #+#    #+#             */
/*   Updated: 2024/12/08 19:31:56 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>

typedef struct s_data t_data;
typedef	struct s_philo{
	int			p_id;
	pthread_t 	t_id;
	unsigned long		last_meal;
	int			has_eaten;
	bool		is_dead;
	unsigned long	has_started;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t *r_fork;
	t_data			*data;
}t_philo;

typedef struct s_data{
	int				n_philo;
	long			t_to_die;
	long			t_to_eat;
	long			t_to_sleep;
	int				meals_to_eat;
	bool			stop_philo;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_dead;
	pthread_mutex_t m_meal;
	pthread_mutex_t *forks;
	t_philo			*philos;
}t_data;

//functions 

int main(int ac, char **av);
int init_mutex(t_data *data);
int	start_philo(t_data *data);
int	init_philo(t_data *data);
void	assign_forks(t_data * data, int i);
void	*routine(void *arg);
int	init_data(t_data *data, char **av);
void	is_sleeping(t_philo *philo);
void	is_thinking(t_philo *philo);
void	is_eating(t_philo *philo);
void	philo_print(char *arg, t_philo *philo);
unsigned long	get_time(void);
void	*bigbrother(void *arg);
long	ft_atoi(const char *arg);
void	ft_usleep(long time);
void	*bigbrother(void *arg);
void	free_mutex(t_data *data);





#endif