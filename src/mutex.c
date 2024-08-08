/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:37:50 by pierre            #+#    #+#             */
/*   Updated: 2024/08/08 19:24:45 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_mutexs(t_data *data, int nbr)
{
	init_forks(data, nbr);
	if (!data->forks)
		return ;
	if (pthread_mutex_init(data->write_lock, NULL) != 0)
	{
		mutex_destroy(data->forks, data->numb_philo);
		free(data->forks);
		free(data);
		exit(1);
	}
	init_mutexsaux(data);
}

void	init_mutexsaux(t_data *data)
{
	if (pthread_mutex_init(data->checkeat_lock, NULL) != 0)
	{
		mutex_destroy(data->write_lock, 1);
		mutex_destroy(data->forks, data->numb_philo);
		mutex_destroy(data->checkeat_lock, 1);
		free(data->forks);
		free(data);
		exit(1);
	}
	if (pthread_mutex_init(data->checklstmeal_lock, NULL) != 0)
	{
		mutex_destroy(data->write_lock, 1);
		mutex_destroy(data->forks, data->numb_philo);
		mutex_destroy(data->checkeat_lock, 1);
		mutex_destroy(data->checklstmeal_lock, 1);
		free(data->forks);
		free(data);
		exit(1);
	}
}

void init_forks(t_data *data, int nbr)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nbr);
	if (!forks)
		return ;
	while (i < nbr)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			write(2, "Error mutex creation exiting program !\n", 39);
			mutex_destroy(forks, nbr);
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