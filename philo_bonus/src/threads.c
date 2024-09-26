/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:24:04 by pierre            #+#    #+#             */
/*   Updated: 2024/09/26 14:53:16 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Launches philo's thread, monitors with the main thread */
int	launch_children(t_data *data)
{
	int			i;
	int			pid;
	i = 0;
	while (i < data->nbr_philo)
	{
		pid = fork();
		if (pid == 0)
			routine();
		i++;
	}
	if (data->numb_philo > 1)
		monitor(data, data->philosophers);
	clear_mutthre(data, philos);
	return (0);
}

/* destroy threads and mutexs */
void	clear_mutthre(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->numb_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			break ;
		i++;
	}
	i = 0;
	while (i < data->numb_philo)
	{
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
			break ;
		i++;
	}
	pthread_mutex_destroy(&data->meal_check);
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->incr_eat);
}

/* philo's routine */
void	*routine(t_data *data, int num)
{
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (data->numb_philo == 1)
	{
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		display(data, philo, 'f');
		pthread_mutex_unlock(&data->forks[philo->left_fork]);
		thread_sleep(data, data->time_to_die + 1);
		return (display(data, philo, 'd'), NULL);
	}
	if (philo->id % 2)
		usleep(15000);
	while (!is_dead(data))
	{
		eat(data, philo);
		if (all_ate(data))
			break ;
		display(data, philo, 's');
		thread_sleep(data, data->time_to_sleep);
		display(data, philo, 't');
	}
	return (NULL);
}

/* checks if a philo is dead or if all the philo's are full */
void	monitor(t_data *data, t_philo *philos)
{
	int	i;

	while (!all_ate(data))
	{
		i = 0;
		while (i < data->numb_philo && !is_dead(data))
		{
			pthread_mutex_lock(&data->meal_check);
			if (get_timestamp() - philos[i].last_meal > data->time_to_die)
				set_dead(data, &philos[i]);
			pthread_mutex_unlock(&data->meal_check);
			usleep(10);
			i++;
		}
		if (data->dead)
			break ;
		i = 0;
		while (i < data->numb_philo && data->max_eat != -1
			&& get_mealtimes(data, &philos[i]) >= data->max_eat)
			i++;
		if (i == data->numb_philo)
			data->all_ate = 1;
	}
}

int	all_ate(t_data *data)
{
	int	state;

	state = 0;
	pthread_mutex_lock(&data->meal_check);
	state = data->all_ate;
	pthread_mutex_unlock(&data->meal_check);
	return (state);
}
