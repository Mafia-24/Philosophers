/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 05:12:19 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/08 05:21:38 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers_bonus.h"

void	ft_sleeper(unsigned int ammount)
{
	unsigned int	start_time;
	unsigned int	current_time;

	start_time = get_time ();
	current_time = get_time ();
	while (current_time - start_time < ammount)
	{
		current_time = get_time ();
		usleep(500);
	}
}

unsigned int	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}
