/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:52:13 by pierre            #+#    #+#             */
/*   Updated: 2024/08/09 23:03:24 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_lstmeal(t_philo *philo)
{
	struct timeval	tv;
	long long seconds;
	long long microseconds;

	pthread_mutex_lock(philo->changelstmeal_lock);
	if (gettimeofday(&tv, NULL) != 0)
	{
		ft_putstr_fd("Error has occured in gettimeofday!!\n", 2);
		exit(1);
	}
	seconds = tv.tv_sec * 1000;
	microseconds = tv.tv_usec / 1000;
	philo->last_meal = seconds + microseconds;
	pthread_mutex_unlock(philo->changelstmeal_lock);
}

long long	get_timestamp()
{
	struct timeval	tv;
	long long		time_stamp;

	if (gettimeofday(&tv, NULL) != 0)
	{
		ft_putstr_fd("Error has occured in gettimeofday!\n", 2);
		exit(1);
	}
	time_stamp = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_stamp);
}