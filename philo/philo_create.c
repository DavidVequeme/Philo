/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvidal <dvidal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 22:06:55 by david             #+#    #+#             */
/*   Updated: 2026/02/11 10:54:59 by dvidal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	create_mutex_hlp(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->prm.n_ph)
	{
		if (pthread_mutex_init(&data->mutex_man.ph_lock[i], NULL) != 0)
			return (false);
		if (pthread_mutex_init(&data->mutex_man.forks[i], NULL) != 0)
			return (false);
		i++;
	}
	return (true);
}

bool	create_mutex(t_data *dt)
{
	dt->mutex_man.forks = ft_calloc(dt->prm.n_ph, sizeof(pthread_mutex_t));
	dt->mutex_man.ph_lock = ft_calloc(dt->prm.n_ph, sizeof(pthread_mutex_t));
	if (dt->mutex_man.forks == NULL || dt->mutex_man.ph_lock == NULL)
	{
		free(dt->mutex_man.forks);
		free(dt->mutex_man.ph_lock);
		return (false);
	}
	if (pthread_mutex_init(&dt->mutex_man.end_lock, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&dt->mutex_man.printf_lock, NULL) != 0)
		return (false);
	if (!create_mutex_hlp(dt))
		return (false);
	return (true);
}

bool	create_philo(t_data *dt)
{
	int	i;

	i = 0;
	dt->ph = ft_calloc(dt->prm.n_ph, sizeof(t_philo));
	while (i < dt->prm.n_ph)
	{
		dt->ph[i].l_fork = &dt->mutex_man.forks[i];
		if (i == 0)
			dt->ph[i].r_fork = &dt->mutex_man.forks[dt->prm.n_ph - 1];
		else
			dt->ph[i].r_fork = &dt->mutex_man.forks[i - 1];
		dt->ph[i].id = i + 1;
		dt->ph[i].params = dt->prm;
		dt->ph[i].mutex_man = &dt->mutex_man;
		dt->ph[i].full = false;
		if (pthread_create(&dt->ph[i].thread, NULL, &routine, &dt->ph[i]) != 0)
			return (false);
		i++;
	}
	return (true);
}

bool	create(t_data *data)
{
	return (create_mutex(data) && create_philo(data));
}
