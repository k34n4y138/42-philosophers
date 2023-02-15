/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:23:17 by zmoumen           #+#    #+#             */
/*   Updated: 2023/02/14 17:55:04 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(char *str)
{
	int	res;

	if (!str)
		return (0);
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	res = 0;
	while (*str && '0' >= *str && *str <= '9')
	{
		res = (res * 10) + *str++ - 48;
		if (res < 0)
			return (-1);
	}
	if (*str)
		return (-1);
	return (res);
}
