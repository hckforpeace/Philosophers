/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:54:28 by pierre            #+#    #+#             */
/*   Updated: 2024/08/08 19:03:04 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	display(t_philo *philo, char state)
{
	pthread_mutex_lock(philo->write_lock);
	if (state == 'l')
		printf("%ld %d has taken left fork\n", get_timestamp(), philo->id);
	else if (state == 'r')
		printf("%ld %d has taken right fork\n", get_timestamp(), philo->id);
	else if (state == 'e')
		printf("%ld %d is eating\n", get_timestamp(), philo->id);
	else if (state == 's')
		printf("%ld %d is sleeping\n", get_timestamp(), philo->id);
	else if (state == 't')
		printf("%ld %d is thinking\n", get_timestamp(), philo->id);
	else if (state == 'd')
		printf("%ld %d died\n", get_timestamp(), philo->id);
	pthread_mutex_unlock(philo->write_lock);
}