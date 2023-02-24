/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:19:44 by zmoumen           #+#    #+#             */
/*   Updated: 2023/02/24 14:20:36 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

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
