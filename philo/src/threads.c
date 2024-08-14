/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:24:04 by pierre            #+#    #+#             */
/*   Updated: 2024/08/14 19:51:40 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_threads(t_data *data)
{
	int			i;
	long long	time;

	time = 
	i = 0;
	while (i < data->numb_philo)
	{
		data->philos[i].first_timestamp = get_timestamp();
		data->philos[i].last_meal = get_timestamp();
		if (pthread_create(&data->thread[i], NULL, &routine, &data->philos[i]) != 0)
		{
			ft_putstr_fd("Error in thread creation !\n", 2);
			exit(1);
		}
		i++;
	}
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo*)arg;
	while (!is_dead(philo))
	{
		if (!eat(philo))
			break ;
		if (!ssleep(philo))
			break;
		if (!think(philo))
			break ;
		usleep(1);
	}
	return (NULL);
}

int	is_dead(t_philo *philo)
{
	int state;

	pthread_mutex_lock(philo->dead_lock);
	state = *(philo->dead);
	pthread_mutex_unlock(philo->dead_lock);
	return (state);
}

void	monitor(t_data *data)
{
	int	i;
	t_philo *philos;

	philos = data->philos;
	i = 0;
	while (1)
	{
		i = i % data->numb_philo;
		if (has_starved(data, &philos[i]))
		{
			pthread_mutex_lock(data->dead_lock);
			data->dead = 1;
			pthread_mutex_unlock(data->dead_lock);
			display(&philos[i], 'd');
			break ;
		}
		if (are_full(data, philos))
		{
			pthread_mutex_lock(data->dead_lock);
			data->dead = 1;
			pthread_mutex_unlock(data->dead_lock);
			break ;
		}
		i++;
		usleep(500);
	}
}

int	has_starved(t_data *data, t_philo *philo)
{
	int ret;

	ret = 0;
	pthread_mutex_lock(data->checklstmeal_lock);
	if (philo->last_meal != 0)
	{
		if (get_timestamp() - philo->last_meal > data->time_todie)
			ret = 1;
	}
	pthread_mutex_unlock(data->checklstmeal_lock);
	return (ret);
}

int	are_full(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	if (data->max_eat >= 0)
	{
		pthread_mutex_lock(data->checklstmeal_lock);
		while (i < data->numb_philo)
		{
			if (philos[i].meals_eaten < data->max_eat)
			{
				pthread_mutex_unlock(data->checklstmeal_lock);
				return (0);
			}
			i++;
		}
		pthread_mutex_unlock(data->checklstmeal_lock);
		return (1);
	}
	return (0);
}
