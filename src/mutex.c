/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:37:50 by pierre            #+#    #+#             */
/*   Updated: 2024/08/08 10:34:30 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_mutexs(t_data *data, int nbr)
{
	init_forks(data, nbr);
	if (!data->forks)
		return ;
	// data->write_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(data->write_lock, NULL) != 0)
	{
		mutex_destroy(data->forks, data->numb_philo);
		free(data->forks);
		free(data);
		exit(1);
	}
	// data->dead_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(data->write_lock, NULL) != 0)
	{
		mutex_destroy(data->write_lock, 1);
		mutex_destroy(data->forks, data->numb_philo);
		free(data->forks);
		free(data);
		exit(1);		
	}
}

static void init_forks(t_data *data, int nbr)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nbr);
	if (!forks)
		return (NULL);
	while (i < nbr)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			write(2, "Error mutex creation exiting program !\n", 39);
			mutex_destroy(nbr, forks);
			free(forks);
			data->forks = NULL;
			return ;
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
			return (id + 1);
	}
}