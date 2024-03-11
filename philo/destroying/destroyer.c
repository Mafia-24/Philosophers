/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:47:47 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/08 00:47:29 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	destroy_forks(pthread_mutex_t *forks, int philos_num)
{
	while (philos_num--)
	{
		pthread_mutex_destroy (&(forks[philos_num]));
	}
	free (forks);
}

void	destroy_philos_data(t_philo_data *data, int filos_num)
{
	int	i;

	i = 0;
	while (i < filos_num)
	{
		pthread_mutex_destroy (&(data[i].last_meal_mtx));
		pthread_mutex_destroy (&(data[i].meal_count_mtx));
		i++;
	}
}
