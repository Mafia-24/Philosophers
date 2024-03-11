/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:48:52 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/08 00:31:34 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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
