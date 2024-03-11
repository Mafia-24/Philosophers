/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_doer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:01:25 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/08 03:57:52 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	think_and_sleep(t_philo_data *p_data)
{
	notify_on_sleeping (p_data, get_time ());
	ft_sleeper (p_data->gen_data->time_to_sleep);
	notify_on_thinking (p_data, get_time ());
}

void	lock_forks(t_philo_data *p_data)
{
	pthread_mutex_lock (p_data->first_fork_mtx);
	notify_fork_taken (p_data, get_time ());
	pthread_mutex_lock (p_data->second_fork_mtx);
	notify_fork_taken (p_data, get_time ());
}

void	go_to_eat(t_philo_data *p_data)
{
	lock_forks (p_data);
	pthread_mutex_lock (&(p_data->last_meal_mtx));
	p_data->last_meal = get_time ();
	pthread_mutex_unlock (&(p_data->last_meal_mtx));
	notify_on_eating (p_data, get_time ());
	ft_sleeper (p_data->gen_data->time_to_eat);
	pthread_mutex_unlock (p_data->first_fork_mtx);
	pthread_mutex_unlock (p_data->second_fork_mtx);
	pthread_mutex_lock (&p_data->meal_count_mtx);
	p_data->number_of_meals++;
	pthread_mutex_unlock (&p_data->meal_count_mtx);
}

void	*find_what_to_do(void *param)
{
	t_philo_data	*p_data;

	p_data = (t_philo_data *) param;
	if (!(p_data->id % 2))
		usleep(150);
	while (1)
	{
		pthread_mutex_lock (&p_data->gen_data->simulation_mtx);
		if (!(p_data->gen_data->simulation_up))
			break ;
		pthread_mutex_unlock (&p_data->gen_data->simulation_mtx);
		go_to_eat (p_data);
		think_and_sleep (p_data);
	}
	pthread_mutex_unlock (&p_data->gen_data->simulation_mtx);
	return (NULL);
}
