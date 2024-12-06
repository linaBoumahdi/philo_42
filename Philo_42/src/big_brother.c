/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_brother.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:05:25 by lboumahd          #+#    #+#             */
/*   Updated: 2024/12/06 23:25:26 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "philo.h"

 int	is_rip(t_philo *philo)
 {
		//check if philo died the moment
 }

//check starvation ???/ 
 int	are_full(t_philo *philo)
 {
	//check if they all ate the av[5]
 }

void	*bigbrother(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while(1)
	{
		if(is_rip(philo) || are_full(philo))
			break;
	}
}