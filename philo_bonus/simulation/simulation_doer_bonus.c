/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_doer_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:24:44 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/08 05:20:58 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers_bonus.h"

void	take_forks(t_general_data *gen_data, int id)
{
	sem_wait (gen_data->forks_sem);
	sem_wait (gen_data->printing_sem);
	printf ("%u %d has taken a fork\n", get_time () - gen_data->start_time, id);
	sem_post (gen_data->printing_sem);
	sem_wait (gen_data->forks_sem);
	sem_wait (gen_data->printing_sem);
	printf ("%u %d has taken a fork\n", get_time () - gen_data->start_time, id);
	sem_post (gen_data->printing_sem);
}

void	go_to_eat(t_philo *data)
{
	take_forks (data->gen_data, data->id);
	sem_wait (data->last_meal_sem);
	data->last_meal = get_time ();
	sem_post (data->last_meal_sem);
	sem_wait (data->gen_data->printing_sem);
	printf ("%u %d is eating\n", get_time ()
		- data->gen_data->start_time, data->id);
	sem_post (data->gen_data->printing_sem);
	ft_sleeper (data->gen_data->time_to_eat);
	sem_post (data->gen_data->forks_sem);
	sem_post (data->gen_data->forks_sem);
}

void	think_and_sleep(t_philo *data)
{
	sem_wait (data->gen_data->printing_sem);
	printf ("%u %d is sleeping\n", get_time ()
		- data->gen_data->start_time, data->id);
	sem_post (data->gen_data->printing_sem);
	ft_sleeper (data->gen_data->time_to_sleep);
	sem_wait (data->gen_data->printing_sem);
	printf ("%u %d is thinking\n", get_time ()
		- data->gen_data->start_time, data->id);
	sem_post (data->gen_data->printing_sem);
}

void	do_routine(t_philo *data)
{
	int			count;
	pthread_t	hday;

	count = 0;
	if (pthread_create(&hday, NULL, watch_philo, data))
	{
		sem_post (data->done_eating_sem);
		exit (1);
	}
	while (1)
	{
		if (count == data->gen_data->min_meals_nb)
			sem_post (data->done_eating_sem);
		go_to_eat (data);
		think_and_sleep (data);
		count++;
	}
	pthread_detach (hday);
	exit (0);
}
