/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:47:39 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/08 05:15:12 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <sys/_types.h>
# include <machine/types.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_general_data
{
	int				p_nb;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				min_meals_nb;
	unsigned int	start_time;
	sem_t			*printing_sem;
	sem_t			*forks_sem;
	sem_t			*simulation_sem;
}	t_general_data;

typedef struct s_philo
{
	int				id;
	t_general_data	*gen_data;
	unsigned int	last_meal;
	sem_t			*last_meal_sem;
	sem_t			*done_eating_sem;
}	t_philo;

typedef struct s_args
{
	t_general_data	gen_data;
	t_philo			*philos_data;
}	t_args;

// str_functions
size_t			ft_strlen(char *arg);
int				ft_strcmp(char *str1, char *str2);
char			*ft_strcat(char *str, int c);

// parsing
int				check_and_store_args(int ac, char **av, t_args *args);
int				wrong_number(char *arg, int i, t_args *args);
int				is_num(char *arg);
unsigned long	ft_ato_ui(char *arg);
int				ft_atoi(char *arg);

// printing functions
void			print_instructions(void);

// simulation
int				simulate(t_args *args);
void			do_routine(t_philo *data);
int				init_args(t_args *args);
int				create_philos(t_args *args, pid_t *pids);

// time 
unsigned int	get_time(void);

// monitoring
void			*watch_philo(void *args);
void			*detect_full_philos(void	*param);

void			ft_sleeper(unsigned int ammount);

//destroyer
void			close_global_sems(t_args *args);
void			close_private_sems(t_args *args);

#endif