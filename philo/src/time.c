/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:52:13 by pierre            #+#    #+#             */
/*   Updated: 2024/08/21 20:01:02 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_lstmeal(t_philo *philo)
{
	struct timeval	tv;

	pthread_mutex_lock(philo->changelstmeal_lock);
	if (gettimeofday(&tv, NULL) != 0)
	{
		ft_putstr_fd("Error has occured in gettimeofday!!\n", 2);
		exit(1);
	}
	philo->last_meal = get_timestamp(); 
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->changelstmeal_lock);
}

long long	get_timestamp()
{
	struct timeval	tv;
	long long		time_stamp;
	long long 		seconds;
	long long	 	microseconds;

	if (gettimeofday(&tv, NULL) != 0)
	{
		ft_putstr_fd("Error has occured in gettimeofday!\n", 2);
		exit(1);
	}
	seconds = tv.tv_sec * 1000;
	microseconds = tv.tv_usec / 1000;
	time_stamp = seconds + microseconds;
	return (time_stamp);
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}
int	thread_sleep(long long time)
{
	long long	start;
	long long	now;

	start = get_timestamp();
	now = start;
	while (now - start < time)
	{
		usleep(1);
		now = get_timestamp();
	}
	return (1);
}