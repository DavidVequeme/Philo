/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:19:32 by david             #+#    #+#             */
/*   Updated: 2026/01/22 13:25:51 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool invalid_input(char **av)
{
    int i;
    int j;

    i = 1;
    while(av[i])
    {
        j = 0;
        while(av[i][j])
        {
            if(av[i][j] < '0' || av[i][j] > '9')
                return(false);
            j++;
        }
        i++;
    }
    return(true);
    
}