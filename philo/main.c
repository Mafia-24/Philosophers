/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:13:06 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/08 17:44:39 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char *av[])
{
	t_args	args;

	if (ac != 5 && ac != 6)
	{
		printf ("Wrong number of arguments!\n");
		return (1);
	}
	args.gen_data.min_meals_nb = -1;
	if (!check_and_store_args (ac, av, &args))
		return (1);
	if (simulate (&args) == -1)
	{
		printf ("An error has occured!\n");
		return (1);
	}
	return (0);
}
