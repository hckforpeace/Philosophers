/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:58:07 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/08/08 18:50:31 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    eat(t_philo *philo)
{
    lock_choice(philo);
    display(philo, 'e');
    philo->is_eating = 1;
    usleep(philo->time_to_eat * 1000);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    philo->is_eating = 0;
    set_lstmeal(philo);
    incr_eat(philo);
}

void    incr_eat(t_philo *philo)
{
    pthread_mutex_lock(philo->counteat_lock);
    philo->meals_eaten++;
    pthread_mutex_unlock(philo->counteat_lock);
}

void    lock_choice(t_philo *philo)
{
    if (philo->id % 2)
    {
        pthread_mutex_lock(philo->left_fork);
        display(philo, 'l');
        pthread_mutex_lock(philo->right_fork);
        display(philo, 'r');
    }
    else
    {
        pthread_mutex_lock(philo->right_fork);
        display(philo, 'r');
        pthread_mutex_lock(philo->left_fork);
        display(philo, 'l');
    }
}

void	ssleep(int think)
{
    usleep(think);
}
