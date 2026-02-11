/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvidal <dvidal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:37:16 by dvidal            #+#    #+#             */
/*   Updated: 2026/02/11 11:20:31 by dvidal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	check_time_to_die(t_data *dt)
{
	int	i;
	int	dif;

	
	i = 0;
	while (i < dt->prm.n_ph)
	{
		pthread_mutex_lock(&dt->mutex_man.ph_lock[i]);
		dif = ft_get_time() - dt->ph[i].l_eat;
		if (dif >= dt->prm.t_die && !dt->ph[i].full)
		{
			pthread_mutex_lock(&dt->mutex_man.end_lock);
			dt->mutex_man.end_flag = true;
			pthread_mutex_unlock(&dt->mutex_man.end_lock);
			pthread_mutex_lock(&dt->mutex_man.printf_lock);
			printf("%ld %d died\n", ft_get_time() - dt->prm.s_t, dt->ph[i].id);
			pthread_mutex_unlock(&dt->mutex_man.printf_lock);
			pthread_mutex_unlock(&dt->mutex_man.ph_lock[i]);
			return (false);
		}
		pthread_mutex_unlock(&dt->mutex_man.ph_lock[i]);
		i++;
	}
	return (true);
}

bool	check_is_full(t_data *data)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (i < data->prm.n_ph)
	{
		pthread_mutex_lock(&data->mutex_man.ph_lock[i]);
		if (data->ph[i].full == true)
			check++;
		if (check == data->prm.n_ph)
		{
			pthread_mutex_lock(&data->mutex_man.end_lock);
			data->mutex_man.end_flag = true;
			pthread_mutex_unlock(&data->mutex_man.end_lock);
			pthread_mutex_unlock(&data->mutex_man.ph_lock[i]);
			return (false);
		}
		pthread_mutex_unlock(&data->mutex_man.ph_lock[i]);
		i++;
	}
	return (true);
}

void	check_end(t_data *data)
{
	while (1)
	{
		if (!check_time_to_die(data) || !check_is_full(data))
			break ;
		usleep(500);
	}
}
