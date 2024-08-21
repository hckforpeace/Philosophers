/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:58:07 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/08/21 19:55:24 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eat(t_philo *philo)
{
/* 	if (philo->id % 2 == 0)
		usleep(100); */
    lock_choice(philo);
	if (is_dead(philo))
		return (0);
	display(philo, 'e');
	set_lstmeal(philo);
	thread_sleep(philo->time_to_eat);
	// usleep(philo->time_to_eat * 1000);
	unlock_choice(philo);
	return (1);
}

void	unlock_choice(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

// void    incr_eat(t_philo *philo)
// {
//     pthread_mutex_lock(philo->counteat_lock);
//     // philo->meals_eaten++;
//     pthread_mutex_unlock(philo->counteat_lock);
// }

int	lock_choice(t_philo *philo)
{
    if (philo->id % 2)
    {
		usleep(500);
		pthread_mutex_lock(philo->right_fork);
		if (is_dead(philo))
		{
			pthread_mutex_unlock(philo->right_fork);
			return (0); 
		}
		display(philo, 'r');
		pthread_mutex_lock(philo->left_fork);
		if (is_dead(philo))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (0);
		}
		display(philo, 'l');
		return (1);
    }
    else
    {
		pthread_mutex_lock(philo->left_fork);
		if (is_dead(philo))
		{
			pthread_mutex_unlock(philo->left_fork);
			return (0);
		}
		display(philo, 'l');
		pthread_mutex_lock(philo->right_fork);
		if (is_dead(philo)) 	
		{	
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (0);
		}
		display(philo, 'r');
		return (1);
    }
}

int	ssleep(t_philo *philo)
{
	if (!is_dead(philo))
	{
		display(philo, 's');
    	thread_sleep(philo->time_to_sleep);
		// usleep(philo->time_to_sleep);
		return (1);
	}
	return (0);
}
/* int	lock_mutex(t_philo *philo, int side, int liberate)
{
	(void)liberate;
	if (side == LEFT)
	{
		// if (is_dead(philo))
		// {
		// 	if (liberate)pthread_mutex_unlock(philo->left_fork);
		// 		pthread_mutex_unlock(philo->right_fork);
		// 	return (0);
		// }
		pthread_mutex_lock(philo->left_fork);
		if (is_dead(philo)) {
			pthread_mutex_unlock(philo->left_fork);
			return(0);
		}
		display(philo, 'l');
		return (1);
	}
	else
	{
		// if (is_dead(philo))
		// {
		// 	if (liberate)
		// 		pthread_mutex_unlock(philo->left_fork);
		// 	return (0);
		// }
		pthread_mutex_lock(philo->right_fork);
		if (is_dead(philo)) {
			pthread_mutex_unlock(philo->right_fork);
			return(0);
		}
		display(philo, 'r');
		return (1);
	}
} */

int	think(t_philo *philo)
{
	if (is_dead(philo))
		return (0);
	else
	{
		// thread_sleep(9);
		display(philo, 't');
		// if ((philo->id % 2) == 0)
		// 	thread_sleep(200);
		return (1);
	}
}
