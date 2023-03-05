/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:19:44 by zmoumen           #+#    #+#             */
/*   Updated: 2023/03/05 17:57:49 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

void	*ft_calloc(int size, int count)
{
	void	*ptr;

	ptr = malloc(size * count);
	if (ptr)
		memset(ptr, 0, size * count);
	return (ptr);
}

int	ft_atoi(char *str)
{
	int	res;

	if (!str)
		return (-1);
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	res = 0;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = (res * 10) + *str++ - 48;
		if (res < 0)
			return (-1);
	}
	if (*str)
		return (-1);
	return (res);
}

long	get_ms_time(long origin)
{
	struct timeval	tmv;

	gettimeofday(&tmv, NULL);
	return ((tmv.tv_sec * 1000 + (tmv.tv_usec / 1000)) - origin);
}

void	mssleep(long ms)
{
	long	tosleep;
	long	sleeptill;

	sleeptill = get_ms_time(0) + ms;
	tosleep = 3 * (ms / 4) * 1000;
	usleep(tosleep);
	tosleep = get_ms_time(0);
	while (tosleep < sleeptill)
	{
		usleep(100);
		tosleep = get_ms_time(0);
	}	
}
