/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notifying.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:44:44 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/08 03:57:15 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	notify_on_sleeping(t_philo_data *p_data, unsigned int timestamp)
{
	pthread_mutex_lock (&(p_data->gen_data->print_mtx));
	pthread_mutex_lock (&(p_data->gen_data->simulation_mtx));
	if (p_data->gen_data->simulation_up)
		printf ("%u %d is sleeping\n",
			timestamp - p_data->gen_data->start_time, p_data->id);
	pthread_mutex_unlock (&(p_data->gen_data->simulation_mtx));
	pthread_mutex_unlock (&(p_data->gen_data->print_mtx));
}

void	notify_on_thinking(t_philo_data *p_data, unsigned int timestamp)
{
	pthread_mutex_lock (&(p_data->gen_data->print_mtx));
	pthread_mutex_lock (&(p_data->gen_data->simulation_mtx));
	if (p_data->gen_data->simulation_up)
		printf ("%u %d is thinking\n",
			timestamp - p_data->gen_data->start_time, p_data->id);
	pthread_mutex_unlock (&(p_data->gen_data->simulation_mtx));
	pthread_mutex_unlock (&(p_data->gen_data->print_mtx));
}

void	notify_fork_taken(t_philo_data *p_data, unsigned int timestamp)
{
	pthread_mutex_lock (&(p_data->gen_data->print_mtx));
	pthread_mutex_lock (&(p_data->gen_data->simulation_mtx));
	if (p_data->gen_data->simulation_up)
		printf ("%u %d has taken a fork\n",
			timestamp - p_data->gen_data->start_time, p_data->id);
	pthread_mutex_unlock (&(p_data->gen_data->simulation_mtx));
	pthread_mutex_unlock (&(p_data->gen_data->print_mtx));
}

void	notify_on_eating(t_philo_data *p_data, unsigned int timestamp)
{
	pthread_mutex_lock (&(p_data->gen_data->print_mtx));
	pthread_mutex_lock (&(p_data->gen_data->simulation_mtx));
	if (p_data->gen_data->simulation_up)
		printf ("%u %d is eating\n",
			timestamp - p_data->gen_data->start_time, p_data->id);
	pthread_mutex_unlock (&(p_data->gen_data->simulation_mtx));
	pthread_mutex_unlock (&(p_data->gen_data->print_mtx));
}
