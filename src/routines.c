/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:58:07 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/08/11 15:05:53 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eat(t_philo *philo)
{
    if (!lock_choice(philo));
		return (0);
    display(philo, 'e');
    philo->is_eating = 1;
	thread_sleep(philo->time_to_eat);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    philo->is_eating = 0;
    set_lstmeal(philo);
    incr_eat(philo);
	return (1);
}

void    incr_eat(t_philo *philo)
{
    pthread_mutex_lock(philo->counteat_lock);
    philo->meals_eaten++;
    pthread_mutex_unlock(philo->counteat_lock);
}

int	lock_choice(t_philo *philo)
{
    if (philo->id % 2)
    {
		if (lock_mutex(philo, LEFT, 0))
			return (0);
		if (lock_mutex(philo, RIGHT, 1))
			return (0);
		return (1);
    }
    else
    {
		if (lock_mutex(philo, RIGHT, 0))
			return (0);
		if (lock_mutex(philo, LEFT, 1))
			return (0);
		return (1);
    }
}

int	ssleep(t_philo *philo)
{
	display(philo, 's');
    thread_sleep(philo->time_to_sleep);
}
int	lock_mutex(t_philo *philo, int side, int liberate)
{
	if (side == LEFT)
	{
		if (!is_dead(philo))
		{
			if (liberate)
				pthread_mutex_unlock(philo->right_fork);
			return (0);
		}
		pthread_mutex_lock(philo->left_fork);
		display(philo, 'l');
		return (1);
	}
	else
	{
		if (!is_dead(philo))
		{
			if (liberate)
				pthread_mutex_unlock(philo->left_fork);
			return (0);
		}
		pthread_mutex_lock(philo->right_fork);
		display(philo, 'r');
		return (1);
	}
}
