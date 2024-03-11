/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_starter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:28:34 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/10 16:07:31 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	simulate(t_args *args)
{
	int		i;

	i = 0;
	args->gen_data.simulation_up = true;
	if (create_forks (args, 0) == -1)
		return (-1);
	if (allocate_philos_mem (args) == -1)
		return (-1);
	if (create_philos (args) == -1)
		return (-1);
	find_a_corpse (args);
	while (i < args->gen_data.p_nb)
	{
		pthread_detach (args->philosophers[i]);
		i++;
	}
	free (args->philosophers);
	destroy_philos_data(args->philos, args->gen_data.p_nb);
	free (args->philos);
	destroy_forks (args->forks, args->gen_data.p_nb);
	pthread_mutex_destroy (&(args->gen_data.print_mtx));
	pthread_mutex_destroy (&(args->gen_data.simulation_mtx));
	return (0);
}
