/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvidal <dvidal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 22:03:42 by david             #+#    #+#             */
/*   Updated: 2026/02/11 11:04:56 by dvidal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atol(char *s)
{
	long	i;
	int		result;

	i = 0;
	result = 0;
	while (s[i])
	{
		result = (result * 10) + (s[i] - '0');
		i++;
	}
	return (result);
}

void	*ft_calloc(size_t num, size_t tam)
{
	void	*buffer;

	if ((tam != 0 && num != 0) && num > SIZE_MAX / tam)
		return (NULL);
	buffer = malloc(num * tam);
	if (!buffer)
		return (NULL);
	memset(buffer, 0, num * tam);
	return (buffer);
}

long	ft_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return (time.tv_sec * 1000L + time.tv_usec / 1000L);
}

int	check_dead(t_mutex_man *mutex)
{
	int	check;

	pthread_mutex_lock(&mutex->end_lock);
	check = mutex->end_flag;
	pthread_mutex_unlock(&mutex->end_lock);
	return (check);
}

void	accurate_sleep(long time, t_mutex_man *mutex)
{
	long	start;

	start = ft_get_time();
	while (time > (ft_get_time() - start))
	{
		if (check_dead(mutex))
			break ;
		usleep(500);
	}
}
