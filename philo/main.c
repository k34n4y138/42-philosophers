/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:40:43 by zmoumen           #+#    #+#             */
/*   Updated: 2023/02/15 19:00:19 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <string.h>


/*
number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]
*/
int initvars(char *av[], t_args *pack, int ac)
{
    pack->num_of_philos = ft_atoi(av[1]);
    pack->time_to_die = ft_atoi(av[2]);
    pack->time_to_eat = ft_atoi(av[3]);
    pack->time_to_sleep = ft_atoi(av[4]);
    if (ac == 6)
    {
        pack->times_to_eat = ft_atoi(av[5]);
    }
    
    
}

int main(int ac, char **av)
{
    t_args pack;

    if (ac < 6)
        printf("NOT ENOUGH ARGUMENT!");
    
}