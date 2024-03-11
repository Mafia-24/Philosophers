/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroying.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 23:01:05 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/10 16:14:10 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers_bonus.h"

void	close_global_sems(t_args *args)
{
	sem_close (args->gen_data.simulation_sem);
	sem_close (args->gen_data.forks_sem);
	sem_close (args->gen_data.printing_sem);
}

void	close_private_sems(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->gen_data.p_nb)
	{
		sem_post (args->philos_data[i].done_eating_sem);
		sem_close (args->philos_data[i].done_eating_sem);
		sem_post (args->philos_data[i].last_meal_sem);
		sem_close (args->philos_data[i].last_meal_sem);
		i++;
	}
}
