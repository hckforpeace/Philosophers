/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:37:50 by pierre            #+#    #+#             */
/*   Updated: 2024/08/09 18:40:40 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_mutexs(t_data *data)
{	
	init_forks(data, data->numb_philo);
	if (pthread_mutex_init(data->write_lock, NULL) != 0)
	{
		mutex_destroy(data->forks, data->numb_philo);
		free_exit(data);
	}
	if (pthread_mutex_init(data->dead_lock, NULL) != 0)
	{
		mutex_destroy(data->write_lock, 1);
		mutex_destroy(data->forks, data->numb_philo);
		free_exit(data);
	}
	if (pthread_mutex_init(data->checkeat_lock, NULL) != 0)
	{
		mutex_destroy(data->dead_lock, 1);
		mutex_destroy(data->write_lock, 1);
		mutex_destroy(data->forks, data->numb_philo);
		free_exit(data);
	}
	init_mutexsaux(data);
}

void	init_mutexsaux(t_data *data)
{
	if (pthread_mutex_init(data->checklstmeal_lock, NULL) != 0)
	{
		mutex_destroy(data->checkeat_lock, 1);
		mutex_destroy(data->dead_lock, 1);
		mutex_destroy(data->write_lock, 1);
		mutex_destroy(data->forks, data->numb_philo);
		free_exit(data);
	}
}

void init_forks(t_data *data, int nbr)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = data->forks;
	i = 0;
	while (i < nbr)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			write(2, "Error mutex initialising mutexs exiting program !\n", 39);
			mutex_destroy(forks, i);
			free_exit(data);	
		}
		i++;
	}
	data->forks = forks;
}

void	mutex_destroy(pthread_mutex_t *mutex, int nbr)
{
	int	i;

	i = 0;
	while (i < nbr)
	{
		if (pthread_mutex_destroy(&mutex[i]) != 0)
			write(2, "Error in mutex destruction !\n", 29);
		i++;
	}
}

int	assign_forks(int side, int totalforks, int id)
{
	if (side == LEFT)
	{
		if (id == 0)
			return (totalforks - 1);
		else
			return (id - 1);		
	}
	else
	{
		if (id == (totalforks - 1))
			return (0);
		else
			return (id);
	}
}