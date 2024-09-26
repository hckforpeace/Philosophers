/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:20:25 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/26 23:22:54 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* inits the t_data struct and checks for possible logic 
errors and inits mutexs */
int	init(int argc, char **argv, t_data *data)
{
	data->nbr_philo = ft_atoi(argv[1]);
	data->meals_eaten = 0;
	data->ttd = ft_atoi(argv[2]);
	data->tte = ft_atoi(argv[3]);
	data->tts = ft_atoi(argv[4]);
	if (argc == 5)
		data->max_meals = -1;
	else
		data->max_meals = ft_atoi(argv[5]);
	if (data->nbr_philo == 0 || data->max_meals == 0)
		return (1);
	if (init_sems(data))
		return (1);
	return (0);
}

int	init_sems(t_data *data)
{
	data->forks = sem_open("forks", O_CREAT, 0666, data->nbr_philo);
	if (data->forks == SEM_FAILED)
		return (1);
	data->write = sem_open("write", O_CREAT, 0666, 1);
	if (data->forks == SEM_FAILED)
		return (1);
	return (0);
}
