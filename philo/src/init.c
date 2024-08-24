/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:20:25 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/08/23 11:13:01 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* inits the t_data struct and checks for possible logic 
errors and inits mutexs */
int	init(int argc, char **argv, t_data *data)
{
	data->numb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->dead = 0;
	data->all_ate = 0;
	if (argc == 5)
		data->max_eat = -1;
	else
		data->max_eat = ft_atoi(argv[5]);
	if (data->numb_philo == 0 || data->max_eat == 0 || data->numb_philo > 200)
		return (1);
	if (init_mutexs(data))
		return (1);
	init_philos(data);
	return (0);
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->numb_philo)
	{
		data->philosophers[i].id = i;
		data->philosophers[i].left_fork = i;
		data->philosophers[i].right_fork = (i + 1) % data->numb_philo;
		data->philosophers[i].last_meal = 0;
		data->philosophers[i].meals_eaten = 0;
		data->philosophers[i].data = data;
		i++;
	}
}

int	init_mutexs(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->numb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->write, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->meal_check, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->incr_eat, NULL) != 0)
		return (1);
	return (0);
}

int	get_mealtimes(t_data *data, t_philo *philo)
{
	int	val;

	pthread_mutex_lock(&data->incr_eat);
	val = philo->meals_eaten;
	pthread_mutex_unlock(&data->incr_eat);
	return (val);
}
