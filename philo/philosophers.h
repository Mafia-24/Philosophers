/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:13:52 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/08 04:01:00 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <sys/_types.h>
# include <machine/types.h>

typedef struct s_general_data
{
	int				p_nb;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				min_meals_nb;
	bool			simulation_up;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	simulation_mtx;
	unsigned int	start_time;
}	t_general_data;

typedef struct s_philo_data
{
	int				id;
	unsigned int	last_meal;
	int				number_of_meals;
	pthread_mutex_t	last_meal_mtx;
	pthread_mutex_t	meal_count_mtx;
	pthread_mutex_t	*first_fork_mtx;
	pthread_mutex_t	*second_fork_mtx;
	t_general_data	*gen_data;
	bool			counted;
}	t_philo_data;

typedef struct s_args
{
	t_philo_data	*philos;
	pthread_t		*philosophers;
	t_general_data	gen_data;
	pthread_mutex_t	*forks;
}	t_args;

// str_functions
size_t			ft_strlen(char *arg);
int				ft_strcmp(char *str1, char *str2);

// parsing
int				check_and_store_args(int ac, char **av, t_args *args);
int				wrong_number(char *arg, int i, t_args *args);
int				is_num(char *arg);
unsigned long	ft_ato_ui(char *arg);
int				ft_atoi(char *arg);

// printing 
void			print_instructions(void);

// simulation
int				simulate(t_args *args);
void			*find_what_to_do(void *param);
void			notify_philo_death(t_args *args, int i);
void			check_full_philos(t_args *args, int i,
					int *full_philos, bool *stop);
void			find_a_corpse(t_args *args);
void			go_to_eat(t_philo_data *p_data);
void			lock_forks(t_philo_data *p_data);
void			think_and_sleep(t_philo_data *p_data);

// init
int				create_forks(t_args *args, int i);
int				init_filo_data(t_args *args, int i);
int				create_philos(t_args *args);
int				allocate_philos_mem(t_args *args);

// destroying
void			destroy_forks(pthread_mutex_t *forks, int philos_num);
void			destroy_philos_data(t_philo_data *data, int filos_num);

// time
unsigned int	get_time(void);
void			ft_sleeper(unsigned int ammount);

// notifying
void			notify_on_sleeping(t_philo_data *p_data,
					unsigned int timestamp);
void			notify_on_thinking(t_philo_data *p_data,
					unsigned int timestamp);
void			notify_fork_taken(t_philo_data *p_data, unsigned int timestamp);
void			notify_on_eating(t_philo_data *p_data, unsigned int timestamp);

#endif