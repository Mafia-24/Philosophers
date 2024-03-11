/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_functions_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:57:40 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/08 05:16:34 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers_bonus.h"

size_t	ft_strlen(char *arg)
{
	size_t	len;

	len = 0;
	while (arg[len])
	{
		len++;
	}
	return (len);
}

int	ft_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 > *str2)
			return (1);
		else if (*str1 < *str2)
			return (-1);
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

static int	get_size(int n)
{
	long int	size;

	size = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		size++;
		n *= -1;
	}
	while (n / 10)
	{
		size++;
		n /= 10;
	}
	if (n % 10)
	{
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char		*res;
	int			i;
	long int	subn;

	subn = n;
	res = (char *) malloc ((get_size(n) + 1));
	if (!res)
		return (NULL);
	i = get_size(n);
	*(res + i--) = '\0';
	res[0] = '0';
	if (subn < 0)
	{
		*res = '-';
		subn *= -1;
	}
	while (subn / 10)
	{
		*(res + i) = '0' + subn % 10;
		subn /= 10;
		i--;
	}
	if (subn % 10)
		*(res + i) = '0' + subn % 10;
	return (res);
}

char	*ft_strcat(char *str, int c)
{
	char	*res;
	char	*num;
	int		i;

	num = ft_itoa (c);
	if (!num)
		return (NULL);
	res = (char *) malloc((ft_strlen(str) + ft_strlen(num) + 1) * sizeof(char));
	if (!res)
		return (free (num), NULL);
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	i = 0;
	while (num[i])
	{
		res[i] = num[i];
		i++;
	}
	res[i] = '\0';
	free (num);
	return (res);
}
