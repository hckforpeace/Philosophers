/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:34:05 by pierre            #+#    #+#             */
/*   Updated: 2024/08/08 10:35:46 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{
	t_data  *data;

	if (argc == 5 || argc == 6)
	{
		if (parcer(&argv[1]))
			simulation(argc, &argv[1]);
		else
			write(2, "Error(s) in arguments\n", 22);
	}
    return (0);
}

void	simulation(char *args, int argc)
{
	t_data	*data;

	data = (struct s_struct*)malloc(sizeof(struct s_data*));
	if (!data)
		return ;
	init_mutexs(data, ft_atoi(args[0]));
	if (!data->forks)
	{
		free(data);
		return ;
	}
	data->numb_philo = ft_atoi(args[0]);
	data->dead = 0;
	data->philos = init_philos(argc, args, data->forks, data);
	init_threads(data);
	join(data);
}

void	join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->numb_philo)
	{
		if (pthread_join(data->pthread[i], NULL) != 0)
		{
			write(2, "An error has occured while joining a thread\n", 44);
			exit(1);
		}
		i++;
	}
}

t_philo	*init_philos(int argc, char **argv, pthread_mutex_t *forks, t_data *data)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = (struct s_philo*)malloc(sizeof(struct s_philo*) * ft_atoi(argv[0]));
	if (!philos)
		return (NULL);
	while (i < ft_atoi(argv[0]))
	{
		(&philos[i])->time_to_die = ft_atoi(argv[1]);
		(&philos[i])->time_to_eat = ft_atoi(argv[2]);
		(&philos[i])->time_to_sleep = ft_atoi(argv[3]);
		if (argc == 6)
			(&philos[i])->limit_sim = ft_atoi(argv[4]);
		else
			(&philos[i])->limit_sim = -1;
		(&philos[i])->last_meal = -1;
		init_dataphilo(data, &philos[i], i, forks);
		i++;
	}
	return (philos);
}

void	init_dataphilo(t_data *data, t_philo *philo, int id, pthread_mutex_t *forks)
{
		philo->id = id;
		philo->dead = &(data->dead);
		philo->meals_eaten = 0;
		philo->left_fork = &forks[assign_forks(LEFT, data->numb_philo, id)];
		philo->right_fork = &forks[assign_forks(RIGHT, data->numb_philo, id)];
		philo->numb_philo = data->numb_philo;
}