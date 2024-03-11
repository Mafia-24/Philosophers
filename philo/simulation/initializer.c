/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 00:44:27 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/09 23:01:49 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	create_forks(t_args *args, int i)
{
	args->forks = (pthread_mutex_t *) malloc
		(args->gen_data.p_nb * sizeof (pthread_mutex_t));
	if (!args->forks)
		return (-1);
	while (i < args->gen_data.p_nb)
	{
		if (pthread_mutex_init (&(args->forks[i]), NULL))
		{
			if (i != 0)
				while (--i)
					pthread_mutex_destroy (&(args->forks[i]));
			free (args->forks);
			return (-1);
		}
		i++;
	}
	if (pthread_mutex_init (&(args->gen_data.print_mtx), NULL))
		return (destroy_forks (args->forks, args->gen_data.p_nb), -1);
	if (pthread_mutex_init (&(args->gen_data.simulation_mtx), NULL))
	{
		pthread_mutex_destroy (&(args->gen_data.print_mtx));
		return (destroy_forks (args->forks, args->gen_data.p_nb), -1);
	}
	return (0);
}

int	init_filo_data(t_args *args, int i)
{
	args->philos[i].id = i + 1;
	args->philos[i].last_meal = args->gen_data.start_time;
	args->philos[i].number_of_meals = 0;
	args->philos->counted = false;
	if (i == 0)
		args->philos[i].first_fork_mtx = &args->forks[args->gen_data.p_nb - 1];
	else
		args->philos[i].first_fork_mtx = &args->forks[i - 1];
	args->philos[i].second_fork_mtx = &args->forks[i];
	args->philos[i].gen_data = &(args->gen_data);
	if (pthread_mutex_init (&(args->philos[i].last_meal_mtx), NULL))
		return (-1);
	if (pthread_mutex_init (&(args->philos[i].meal_count_mtx), NULL))
		return (-1);
	return (0);
}

int	create_philos(t_args *args)
{
	int	i;

	i = 0;
	args->gen_data.start_time = get_time();
	while (i < args->gen_data.p_nb)
	{
		if ((init_filo_data (args, i) == -1) || pthread_create
			(&args->philosophers[i], NULL, find_what_to_do, &args->philos[i]))
		{
			pthread_mutex_destroy (&(args->philos[i].last_meal_mtx));
			pthread_mutex_destroy (&(args->philos[i].meal_count_mtx));
			while (i != 0 && (i--))
			{
				pthread_mutex_destroy (&(args->philos[i].last_meal_mtx));
				pthread_mutex_destroy (&(args->philos[i].meal_count_mtx));
				pthread_detach (args->philosophers[i]);
			}
			destroy_forks (args->forks, args->gen_data.p_nb);
			pthread_mutex_destroy (&(args->gen_data.print_mtx));
			pthread_mutex_destroy (&(args->gen_data.simulation_mtx));
			return (free (args->philosophers), free (args->philos), -1);
		}
		i++;
	}
	return (0);
}

int	allocate_philos_mem(t_args *args)
{
	args->philosophers = (pthread_t *)
		malloc (args->gen_data.p_nb * sizeof (pthread_t));
	if (!args->philosophers)
	{
		destroy_forks (args->forks, args->gen_data.p_nb);
		pthread_mutex_destroy (&(args->gen_data.print_mtx));
		pthread_mutex_destroy (&(args->gen_data.simulation_mtx));
		return (-1);
	}
	args->philos = (t_philo_data *)
		malloc (args->gen_data.p_nb * sizeof(t_philo_data));
	if (!args->philos)
	{
		destroy_forks (args->forks, args->gen_data.p_nb);
		pthread_mutex_destroy (&(args->gen_data.print_mtx));
		pthread_mutex_destroy (&(args->gen_data.simulation_mtx));
		return (free (args->philosophers), -1);
	}
	return (0);
}
