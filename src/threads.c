/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:24:04 by pierre            #+#    #+#             */
/*   Updated: 2024/08/11 15:06:14 by pierre           ###   ########.fr       */
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
		if (pthread_create(&data->thread[i], NULL, &routine, &data->philos[i]) != 0)
		{
			ft_putstr_fd("Error in thread creation !\n", 2);
			exit(1);
		}
		i++;
	}
	if (pthread_create(data->monitor, NULL, &monitor, data) != 0)
	{
		ft_putstr_fd("Error in thread creation !\n", 2);
		exit(1);
	}
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo*)arg;
	while (!is_dead(philo))
	{
		display(philo, 't');
		if (!eat(philo))
			break ;
		if (!ssleep(philo))
			break;
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

void	*monitor(void	*arg)
{
	int	i;
	t_philo *philos;
	t_data	*data;

	data = (t_data*)arg;
	philos = data->philos;
	i = 0;
	while (1)
	{
		if (i > data->numb_philo)
			i = 0;
		if (has_starved(data, &philos[i]) || is_full(data, &philos[i]))
		{
			pthread_mutex_lock(data->dead_lock);
			*(data->dead) = 1;
			pthread_mutex_unlock(data->dead_lock);
			break ;
		}
		i++;
	}
	return (NULL);
}

int	has_starved(t_data *data, t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(data->checklstmeal_lock);
	if (time_diff(philo->last_meal, get_timestamp()) > (data->time_todie))
	{
		display(philo, 'd');
		ret = 1;
	}
	else
		ret = 0;	
	pthread_mutex_unlock(data->checklstmeal_lock);
	return (ret);
}

int	is_full(t_data *data, t_philo *philo)
{
	int	ret;

	if (data->max_eat > 0)
	{
		pthread_mutex_lock(data->checkeat_lock);
		if (philo->meals_eaten > data->max_eat)
			ret = 1;
		else
			ret = 0;
		pthread_mutex_unlock(data->checkeat_lock);
	}
	else
		ret = 0;
	return (ret);
}