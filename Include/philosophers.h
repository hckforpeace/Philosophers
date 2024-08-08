/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:18:23 by pierre            #+#    #+#             */
/*   Updated: 2024/08/08 19:41:33 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

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
	int					*dead;
	int					meals_eaten;
	int					numb_philo;
	int					is_eating;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;	
	unsigned int		last_meal;

	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		*counteat_lock;
	pthread_mutex_t		*changelstmeal_lock;
	pthread_mutex_t		*dead_lock;
}	t_philo;

typedef struct s_data
{
	int					*dead;
	int					numb_philo;
	int					max_eat;
	int					time_todie;

	pthread_mutex_t		*forks;
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*checkeat_lock;
	pthread_mutex_t		*checklstmeal_lock;

	pthread_t			*thread;
	pthread_t			*monitor;
	t_philo				*philos;
}	t_data;

//main.c
void	simulation(char **args, int argc);
void	join(t_data *data);
t_philo	*init_philos(char **argv, pthread_mutex_t *forks, t_data *data);
void	init_dataphilo(t_data *data, t_philo *philo, int id, pthread_mutex_t *forks);


//mutex
int	assign_forks(int side, int totalforks, int id);
void	init_mutexs(t_data *data, int nbr);
void	init_mutexsaux(t_data *data);
void	mutex_destroy(pthread_mutex_t *mutex, int nbr);
void init_forks(t_data *data, int nbr);

//threads.c
void	init_threads(t_data *data);
void	*routine(void *arg);
int	is_dead(t_philo *philo);
void	*monitor(void *arg);
int	has_starved(t_data *data, t_philo *philo);
int	is_full(t_data *data, t_philo *philo);

//cycle.c
void	eat(t_philo *philosopher);

//time.c
void	set_lstmeal(t_philo *philo);
long	get_timestamp();

//display.c
void	display(t_philo *philo, char state);

//routine.c
void    eat(t_philo *philo);
void    incr_eat(t_philo *philo);
void    lock_choice(t_philo *philo);
void	ssleep(int think);

//parser.c
int	parser(char **argv);
int	is_overflow(char *str);
#endif