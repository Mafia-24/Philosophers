/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 00:46:59 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/09 00:18:57 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_sleeper(unsigned int ammount)
{
	unsigned int	start_time;
	unsigned int	current_time;

	start_time = get_time ();
	current_time = get_time ();
	while (current_time - start_time < ammount)
	{
		current_time = get_time ();
		usleep(100);
	}
}

unsigned int	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}
