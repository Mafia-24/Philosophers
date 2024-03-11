/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_to_num_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:57:55 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/08 18:33:07 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers_bonus.h"

static int	is_int(char *arg)
{
	size_t	len;

	if (*arg == '+')
		arg++;
	while (*arg == '0')
	{
		arg++;
	}
	len = ft_strlen (arg);
	if (len == 0 || len > 10 || (len == 10
			&& (ft_strcmp (arg, "2147483647") == 1)))
		return (0);
	return (1);
}

int	ft_atoi(char *arg)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	if (!is_int (arg))
		return (0);
	if (arg[i] == '+')
		i++;
	while (arg[i])
	{
		res *= 10;
		res += arg[i] - 48;
		i++;
	}
	return (res);
}

static int	is_long(char *arg)
{
	size_t	len;

	if (*arg == '+')
		arg++;
	while (*arg == '0')
	{
		arg++;
	}
	len = ft_strlen (arg);
	if (len == 0 || len > 10 || (len == 10
			&& (ft_strcmp (arg, "4294967295") == 1)))
		return (0);
	return (1);
}

unsigned long	ft_ato_ui(char *arg)
{
	unsigned int	res;
	int				i;

	res = 0;
	i = 0;
	if (!is_long (arg))
		return (0);
	if (arg[i] == '+')
		i++;
	while (arg[i])
	{
		res *= 10;
		res += arg[i] - 48;
		i++;
	}
	return (res);
}
