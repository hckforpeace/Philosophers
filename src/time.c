/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:52:13 by pierre            #+#    #+#             */
/*   Updated: 2024/08/10 19:22:01 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_lstmeal(t_philo *philo)
{
	struct timeval	tv;
	long long		ret;

	pthread_mutex_lock(philo->changelstmeal_lock);
	if (gettimeofday(&tv, NULL) != 0)
	{
		ft_putstr_fd("Error has occured in gettimeofday!!\n", 2);
		exit(1);
	}
	ret = get_timestamp() - philo->first_timestamp;
	philo->last_meal = ret;
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