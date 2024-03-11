/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_starter_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:08:16 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/10 16:15:29 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers_bonus.h"

int	end_simulation(t_args *args, pid_t *pids)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	usleep(100);
	if (pthread_create (&monitor_thread, NULL, detect_full_philos, args))
	{
		close_global_sems (args);
		close_private_sems (args);
		free (pids);
		free (args->philos_data);
		while (i < args->gen_data.p_nb)
		{
			kill (pids[i], SIGKILL);
			i++;
		}
		return (-1);
	}
	sem_wait (args->gen_data.simulation_sem);
	pthread_detach (monitor_thread);
	while (i < args->gen_data.p_nb)
		kill (pids[i++], SIGKILL);
	return (0);
}

int	simulate(t_args *args)
{
	pid_t	*pids;

	if (init_args (args) == -1)
		return (-1);
	pids = (pid_t *) malloc (args->gen_data.p_nb * sizeof (pid_t));
	if (!pids)
	{
		free (args->philos_data);
		return (close_global_sems (args), -1);
	}
	if (create_philos (args, pids) == -1)
		return (close_global_sems (args), -1);
	if (end_simulation (args, pids) == -1)
		return (-1);
	free (pids);
	close_global_sems (args);
	close_private_sems (args);
	free (args->philos_data);
	return (0);
}
