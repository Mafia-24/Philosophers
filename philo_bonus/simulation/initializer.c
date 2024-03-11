/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 22:59:04 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/09 19:13:34 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers_bonus.h"

int	init_args(t_args *args)
{
	sem_unlink ("/forks");
	args->gen_data.forks_sem = sem_open("/forks",
			O_CREAT, 0644, args->gen_data.p_nb);
	if (args->gen_data.forks_sem == SEM_FAILED)
		return (-1);
	sem_unlink ("/print_sem");
	args->gen_data.printing_sem = sem_open("/print_sem", O_CREAT, 0644, 1);
	if (args->gen_data.printing_sem == SEM_FAILED)
		return (sem_close (args->gen_data.forks_sem), -1);
	sem_unlink ("/simulation_sem");
	args->gen_data.simulation_sem = sem_open("/simulation_sem",
			O_CREAT, 0644, 0);
	if (args->gen_data.simulation_sem == SEM_FAILED)
		return (sem_close (args->gen_data.forks_sem),
			sem_close (args->gen_data.printing_sem), -1);
	args->gen_data.start_time = get_time ();
	args->philos_data = (t_philo *) malloc
		(args->gen_data.p_nb * sizeof (t_philo));
	if (!args->philos_data)
		return (close_global_sems (args), -1);
	return (0);
}

static int	set_philo_data(t_args *args, int i)
{
	char	*sem_name;

	args->philos_data[i].id = i + 1;
	args->philos_data[i].gen_data = &args->gen_data;
	args->philos_data[i].last_meal = args->gen_data.start_time;
	sem_name = ft_strcat ("/lst_meals_sem_", i);
	if (!sem_name)
		return (-1);
	sem_unlink (sem_name);
	args->philos_data[i].last_meal_sem = sem_open (sem_name, O_CREAT, 0644, 1);
	free (sem_name);
	if (args->philos_data[i].last_meal_sem == SEM_FAILED)
		return (-1);
	sem_name = ft_strcat ("/done_eating_sem", i);
	if (!sem_name)
		return (sem_close (args->philos_data[i].last_meal_sem), -1);
	sem_unlink (sem_name);
	args->philos_data[i].done_eating_sem = sem_open
		(sem_name, O_CREAT, 0644, 0);
	free (sem_name);
	if (args->philos_data[i].done_eating_sem == SEM_FAILED)
		return (sem_close (args->philos_data[i].last_meal_sem), -1);
	return (0);
}

static void	philo_creation_failure(t_args *args, pid_t *pids, int i)
{
	while (i--)
	{
		kill (pids[i], SIGKILL);
		sem_close (args->philos_data[i].last_meal_sem);
		sem_close (args->philos_data[i].done_eating_sem);
	}
	free (args->philos_data);
	free (pids);
}

int	create_philos(t_args *args, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < args->gen_data.p_nb)
	{
		if (set_philo_data(args, i) == -1)
			return (philo_creation_failure (args, pids, i), -1);
		pids[i] = fork ();
		if (pids[i] == -1)
		{
			sem_close (args->philos_data[i].last_meal_sem);
			sem_close (args->philos_data[i].done_eating_sem);
			return (philo_creation_failure (args, pids, i), -1);
		}
		else if (pids[i] == 0)
		{
			do_routine (&args->philos_data[i]);
		}
		else
			i++;
	}
	return (0);
}
