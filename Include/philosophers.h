/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:18:23 by pierre            #+#    #+#             */
/*   Updated: 2024/08/08 10:32:02 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSPHERS_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# define LEFT 0
# define RIGHT 1

typedef struct s_philo
{
	int					id;
	int					eating;
	int					*dead;
	int					meals_eaten;
	int					numb_philo;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;	
	int					limit_sim;
	long long			last_meal;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		*dead_lock;
}	t_philo;

typedef struct s_data
{
	int					dead;
	int					numb_philo;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		*dead_lock;
	pthread_t			*pthread;
	t_philo				*philos;
}	t_data;

// parser.c
int				parser(char **argv);
void			*init_mutexs(t_data *data, int nbr);
void			mutex_destroy(int nbr, pthread_mutex_t *forks);

//mutex
int	assign_forks(int side, int totalforks, int id);

//threads.c
void	routine(t_philo *philo);
void	init_threads(t_data *data);

//cycle.c
void	eat(t_philo *philosopher);

//time.c
void	set_lstmeal(t_philo *philo);

#endif