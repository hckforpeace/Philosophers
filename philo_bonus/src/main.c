/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:34:05 by pierre            #+#    #+#             */
/*   Updated: 2024/09/26 12:59:10 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (parser(&argv[1]))
			simulation(&argv[0], argc);
		else
			display_error(0);
	}
	else
		display_error(0);
	return (0);
}

/* Init, launch simulation and checks errors */
void	simulation(char **argv, int argc)
{
	t_data	data;

	if (init(argc, argv, &data))
	{
		display_error(1);
		return ;
	}
	if (launch_children(&data))
	{
		display_error(2);
		return ;
	}
}

/* locks dead_lock mutex to access a shared data */
int	is_dead(t_data *data)
{
	int	state;

	state = 0;
	pthread_mutex_lock(&data->dead_lock);
	state = data->dead;
	pthread_mutex_unlock(&data->dead_lock);
	return (state);
}

/* chooses depending on philos id which fork he will pick first */
static void	choose_fork(t_data *data, t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		display(data, philo, 'f');
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		display(data, philo, 'f');
	}
	else
	{
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		display(data, philo, 'f');
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		display(data, philo, 'f');
	}
}

/* eat routine */
void	eat(t_data *data, t_philo *philo)
{
	choose_fork(data, philo);
	pthread_mutex_lock(&data->meal_check);
	display(data, philo, 'e');
	philo->last_meal = get_timestamp();
	pthread_mutex_unlock(&data->meal_check);
	pthread_mutex_lock(&data->incr_eat);
	philo->meals_eaten++;
	pthread_mutex_unlock(&data->incr_eat);
	thread_sleep(data, data->time_to_eat);
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
}
