/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 00:45:48 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/09 00:09:06 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	notify_philo_death(t_args *args, int i)
{
	pthread_mutex_lock (&(args->gen_data.simulation_mtx));
	args->gen_data.simulation_up = false;
	pthread_mutex_unlock (&(args->gen_data.simulation_mtx));
	pthread_mutex_lock (&(args->gen_data.print_mtx));
	printf ("%u %d died\n", get_time () - args->gen_data.start_time, i + 1);
	pthread_mutex_unlock (&(args->gen_data.print_mtx));
}

void	check_full_philos(t_args *args, int i, int *full_philos, bool *stop)
{
	pthread_mutex_lock (&(args->philos[i].meal_count_mtx));
	if (!args->philos[i].counted
		&& (args->philos[i].number_of_meals >= args->gen_data.min_meals_nb))
	{
		args->philos[i].counted = true;
		(*full_philos)++;
	}
	pthread_mutex_unlock (&(args->philos[i].meal_count_mtx));
	if (*full_philos == args->gen_data.p_nb)
	{
		pthread_mutex_lock (&(args->gen_data.simulation_mtx));
		args->gen_data.simulation_up = false;
		pthread_mutex_unlock (&(args->gen_data.simulation_mtx));
		*stop = true;
	}
}

void	find_a_corpse(t_args *args)
{
	int		i;
	bool	stop;
	int		full_philos;

	i = 0;
	stop = false;
	full_philos = 0;
	while (!stop)
	{
		if (i == args->gen_data.p_nb)
			i = 0;
		pthread_mutex_lock (&(args->philos[i].last_meal_mtx));
		if (get_time () - args->philos[i].last_meal
			>= args->gen_data.time_to_die)
		{
			notify_philo_death (args, i);
			stop = true;
		}
		pthread_mutex_unlock (&(args->philos[i].last_meal_mtx));
		if (args->gen_data.min_meals_nb != -1)
			check_full_philos (args, i, &full_philos, &stop);
		i++;
		usleep (500);
	}
}
