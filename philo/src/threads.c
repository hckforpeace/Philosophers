/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:24:04 by pierre            #+#    #+#             */
/*   Updated: 2024/08/19 17:47:27 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_threads(t_data *data)
{
	int			i;

	i = 0;
	while (i < data->numb_philo)
	{
		data->philos[i].first_timestamp = get_timestamp();
		data->philos[i].last_meal = get_timestamp();
		if (pthread_create(&data->thread[i], NULL, &routine, &data->philos[i]) != 0)
		{
			ft_putstr_fd("Error in thread creaidtion !\n", 2);
			exit(1);
		}
		i++;
	}
}

static void	delay(t_philo *philo)
{
	long long	now;
	long long	lst_meal;
	long long	diff;

	if (is_dead(philo))
		return ;
	pthread_mutex_lock(philo->changelstmeal_lock);
	lst_meal = philo->last_meal;
	pthread_mutex_unlock(philo->changelstmeal_lock);
	now = get_timestamp();
	diff = now - lst_meal;
	if (philo->numb_philo % 2 == 1)
	{
		thread_sleep(3 * philo->time_to_eat - diff);
		return ;
	}
	thread_sleep(2 * philo->time_to_eat - diff);
}
void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo*)arg;
	thread_sleep(philo->time_to_eat  * ((philo->id ) % 2 == 1));
	thread_sleep(philo->time_to_eat * (philo->numb_philo % 2
				&& (philo->id ) == philo->numb_philo - 1));
	while (!is_dead(philo))
	{
		if (!eat(philo))
			break ;
		if (!ssleep(philo))
			break;
		if (!think(philo))
			break ;
		delay(philo);
		// usleep(100);
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
	long long	now;
	long long	lst_meal;

	philos = data->philos;
	i = 0;
	while (1)
	{
		i = i % data->numb_philo;
		pthread_mutex_lock(data->checklstmeal_lock);
		lst_meal = data->philos[i].last_meal;
		pthread_mutex_unlock(data->checklstmeal_lock);
		now = get_timestamp();
		if (now - lst_meal > data->time_todie)
		{
			pthread_mutex_lock(data->dead_lock);
			data->dead = 1;
			pthread_mutex_unlock(data->dead_lock);
			display(&philos[i], 'd');
			break ;
		}
/* 		
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
		 */
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
