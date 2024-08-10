/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:54:28 by pierre            #+#    #+#             */
/*   Updated: 2024/08/10 19:37:51 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	display(t_philo *philo, char state)
{
	long long time;

	pthread_mutex_lock(philo->write_lock);
	time = get_timestamp() - philo->first_timestamp;
	if (state == 'l')
		printf("%09lld %d has taken left fork\n", time, philo->id);
	else if (state == 'r')
		printf("%09lld %d has taken right fork\n", time, philo->id);
	else if (state == 'e')
		printf("%09lld %d is eating\n", time, philo->id);
	else if (state == 's')
		printf("%09lld %d is sleeping\n", time, philo->id);
	else if (state == 't')
		printf("%09lld %d is thinking\n", time, philo->id);
	else if (state == 'd')
		printf("%09lld %d died\n", time, philo->id);
	pthread_mutex_unlock(philo->write_lock);
}