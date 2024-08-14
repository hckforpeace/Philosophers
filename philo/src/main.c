/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:34:05 by pierre            #+#    #+#             */
/*   Updated: 2024/08/14 17:42:04 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{

	if (argc == 5 || argc == 6)
	{
		if (parser(&argv[1]))
			simulation(&argv[1], argc);
		else
			write(2, "Error(s) in arguments\n", 22);
	}
    return (0);
}
void	simulation(char **args, int argc)
{
	t_data	*data;

	data = (struct s_data*)malloc(sizeof(struct s_data));
	if (!data)
		return ;
	data->numb_philo = ft_atoi(args[0]);
	alloc_dataparams(data);
	init_mutexs(data);
	data->dead = 0;
	data->time_todie = ft_atoi(args[1]);
	data->philos = init_philos(args, data->forks, data);
	if (argc == 6)
		data->max_eat = ft_atoi(args[4]);
	else
		data->max_eat = -1;
	init_threads(data);
	monitor(data);
	join(data);
	destroy_mutexs(data);
	free_exit(data, 0);
}

void	join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->numb_philo)
	{
		if (pthread_join(data->thread[i], NULL) != 0)
		{
			ft_putstr_fd("An error has occured while joining a thread\n", 2);
			exit(1);
		}
		i++;
	}
}

t_philo	*init_philos(char **argv, pthread_mutex_t *forks, t_data *data)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = data->philos;
	while (i < data->numb_philo)
	{
		(&philos[i])->time_to_eat = ft_atoi(argv[2]);
		(&philos[i])->time_to_sleep = ft_atoi(argv[3]);
		(&philos[i])->last_meal = -1;
		init_dataphilo(data, &philos[i], i, forks);
		i++;
	}
	return (philos);
}

void	init_dataphilo(t_data *data, t_philo *philo, int id, pthread_mutex_t *forks)
{
		philo->id = id;
		philo->dead = &data->dead;
		philo->meals_eaten = 0;
		philo->numb_philo = data->numb_philo;
		if (data->numb_philo == 2 && id == 1)
		{
			philo->left_fork = &forks[0];
			philo->right_fork = &forks[1];
		}
		else
		{
			philo->left_fork = &forks[assign_forks(LEFT, data->numb_philo, id)];
			philo->right_fork = &forks[assign_forks(RIGHT, data->numb_philo, id)];
		}
		philo->write_lock = data->write_lock;
		philo->counteat_lock = data->checkeat_lock;
		philo->changelstmeal_lock = data->checklstmeal_lock;
		philo->dead_lock = data->dead_lock;
}
