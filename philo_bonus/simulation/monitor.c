/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 23:03:15 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/10 16:14:31 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers_bonus.h"

void	*watch_philo(void *args)
{
	t_philo	*philo_args;

	philo_args = (t_philo *) args;
	while (true)
	{
		sem_wait (philo_args->last_meal_sem);
		if (get_time () - philo_args->last_meal
			>= philo_args->gen_data->time_to_die)
		{
			sem_wait (philo_args->gen_data->printing_sem);
			printf ("%u %d died\n", get_time ()
				- philo_args->gen_data->start_time, philo_args->id);
			usleep(300);
			sem_post (philo_args->last_meal_sem);
			sem_post (philo_args->gen_data->simulation_sem);
			return (NULL);
		}
		sem_post (philo_args->last_meal_sem);
		ft_sleeper (1);
	}
	return (NULL);
}

void	*detect_full_philos(void	*param)
{
	t_args	*args;
	int		i;

	i = 0;
	args = (t_args *) param;
	while (i < args->gen_data.p_nb)
	{
		sem_wait (args->philos_data[i].done_eating_sem);
		i++;
	}
	sem_post (args->gen_data.simulation_sem);
	return (NULL);
}
