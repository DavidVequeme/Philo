/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 22:03:42 by david             #+#    #+#             */
/*   Updated: 2026/02/08 17:41:12 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long ft_atol(char *s)
{
    long i;
    int result;

    i = 0;
    result = 0;
    while(s[i])
    {
        result = (result * 10) + (s[i] - '0');
        i++;
    }
    return(result);
}

void    *ft_calloc(size_t num, size_t tam)
{
    void    *buffer;
 
    if ((tam != 0 && num != 0) && num > SIZE_MAX / tam)
        return (NULL);
    buffer = malloc(num * tam);
    if (!buffer)
        return (NULL);
    memset(buffer, 0, num * tam);
    return (buffer);
}

long    ft_get_time(void)
{
    struct timeval    tv;

    if (gettimeofday(&tv, NULL) == -1)
        return (-1);
    return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

int	check_dead(t_mutex_man *mutex)
{
	int		check;

	pthread_mutex_lock(&mutex->end_lock);
	check = mutex->end_flag;
	pthread_mutex_unlock(&mutex->end_lock);
	return (check);
}
void accurate_sleep(long time, t_mutex_man *mutex)
{
    long start;
    long i;
    
    start = ft_get_time();
    while (1)
    {
        if (check_dead(mutex))
            break;
        i = ft_get_time() - start;
        if (i >= time)
            break ;
        usleep(1000);   
    }
}