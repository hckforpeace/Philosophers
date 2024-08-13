/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:24:04 by pierre            #+#    #+#             */
/*   Updated: 2024/08/13 19:17:18 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_threads(t_data *data)
{
	int			i;
	long long	time;

	time = get_timestamp();
	i = 0;
	while (i < data->numb_philo)
	{
		data->philos[i].first_timestamp = time;
		data->philos[i].last_meal = time;
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
	if ((philo->id + 1) % 2 == 0)
		usleep(200);
	while (!is_dead(philo))
	{
		if (!eat(philo))
			break ;
		if (!think(philo))
			break ;
		if (!ssleep(philo))
			break;
		usleep(100);
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
		if (i > data->numb_philo - 1)
			i = 0;
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
	if (time_diff(philo->last_meal, get_timestamp()) > (data->time_todie))
		ret = 1;
	pthread_mutex_unlock(data->checklstmeal_lock);
	return (ret);
}

int	are_full(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	if (data->max_eat >= 0)
	{
		pthread_mutex_lock(data->checkeat_lock);
		while (i < data->numb_philo)
		{
			// printf("\nchecking philo: %d ", i);
			if (philos[i].meals_eaten < data->max_eat)
			{
				pthread_mutex_unlock(data->checkeat_lock);
				return (0);
			}
			i++;
		}
		pthread_mutex_unlock(data->checkeat_lock);
		return (1);
	}
	return (0);
}
