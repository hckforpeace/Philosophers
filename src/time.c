/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:52:13 by pierre            #+#    #+#             */
/*   Updated: 2024/08/08 18:45:51 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_lstmeal(t_philo *philo)
{
	struct timeval	tv;

	pthread_mutex_lock(philo->changelstmeal_lock);
	if (gettimeofday(&tv, NULL) != 1)
		exit(1);
	philo->last_meal = (tv.tv_sec / 1000) + (tv.tv_usec * 1000);
	pthread_mutex_unlock(philo->changelstmeal_lock);
}

long	get_timestamp()
{
	struct timeval	tv;
	long			time_stamp;

	if (gettimeofday(&tv, NULL) != 1)
		exit(1);
	time_stamp = (tv.tv_sec / 1000) + (tv.tv_usec * 1000);
	return (time_stamp);
}