/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:22:38 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/08 05:15:53 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers_bonus.h"

int	is_num(char *arg)
{
	if (*arg == '+')
		arg++;
	if (!(*arg))
		return (0);
	while (*arg)
	{
		if ((*arg < '0') || (*arg > '9'))
			return (0);
		arg++;
	}
	return (1);
}

void	print_instructions(void)
{
	printf("\033[1;31mWrong arguments!\033[0m\n\n");
	printf("\033[1;32mCorrect arguments format :\033[0m\n\n");
	printf ("1) p_nb 			[+][1 - 1000]\n");
	printf ("2) time_to_die 					[+][1 - 4294967295]\n");
	printf ("3) time_to_eat 					[+][1 - 4294967295]\n");
	printf ("4) time_to_sleep 				[+][1 - 4294967295]\n");
	printf ("5) [min_meals_nb] 	[+][1 - 1000]\n");
}

int	wrong_number(char *arg, int i, t_args *args)
{
	unsigned int	nb;

	if (((i == 0) || (i == 4)))
	{
		nb = (unsigned int) ft_atoi (arg);
		if (!nb)
			return (1);
		else if (i == 0)
			args->gen_data.p_nb = (int) nb;
		else
			args->gen_data.min_meals_nb = (int) nb;
	}
	else
	{
		nb = ft_ato_ui (arg);
		if (!nb)
			return (1);
		else if (i == 1)
			args->gen_data.time_to_die = nb;
		else if (i == 2)
			args->gen_data.time_to_eat = nb;
		else
			args->gen_data.time_to_sleep = nb;
	}
	return (0);
}

int	check_and_store_args(int ac, char **av, t_args *args)
{
	int	i;

	i = 0;
	while (i < ac - 1)
	{
		if (!is_num (av[i + 1]) || wrong_number (av[i + 1], i, args))
			return (print_instructions (), 0);
		i++;
	}
	return (1);
}
