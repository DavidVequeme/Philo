/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvidal <dvidal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:09:47 by david             #+#    #+#             */
/*   Updated: 2026/02/11 11:17:42 by dvidal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init(t_prm *params, int ac, char **av)
{
	if (ac == 6)
		params->n_teat = ft_atol(av[5]);
	else
		params->n_teat = -1;
	params->n_ph = ft_atol(av[1]);
	params->t_die = ft_atol(av[2]);
	params->t_eat = ft_atol(av[3]);
	params->t_sleep = ft_atol(av[4]);
	params->s_t = ft_get_time();
}

void	*routine(void *p)
{
	t_philo	*philo;

	philo = p;
	pthread_mutex_lock(&philo->mutex_man->ph_lock[philo->id - 1]);
	philo->l_eat = ft_get_time();
	pthread_mutex_unlock(&philo->mutex_man->ph_lock[philo->id - 1]);
	if (philo->id % 2 == 0)
		accurate_sleep(10, philo->mutex_man);
	while (!check_dead(philo->mutex_man))
	{
		philo_eat(philo);
		if (philo->full)
			break ;
		philo_sleep(philo);
		usleep(500);
	}
	return (NULL);
}

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->prm.n_ph)
	{
		pthread_mutex_destroy(&data->mutex_man.forks[i]);
		pthread_mutex_destroy(&data->mutex_man.ph_lock[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mutex_man.end_lock);
	pthread_mutex_destroy(&data->mutex_man.printf_lock);
	free(data->ph);
	free(data->mutex_man.forks);
	free(data->mutex_man.ph_lock);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	if (ac == 5 || ac == 6)
	{
		i = 0;
		if (!invalid_input(av))
			return (1);
		if (ft_atol(av[1]) == 1)
			return (lonely(av), 0);
		memset(&data, 0, sizeof(t_data));
		init(&data.prm, ac, av);
		if (!create(&data))
			free_all(&data);
		usleep(100);
		check_end(&data);
		while (i < data.prm.n_ph)
		{
			pthread_join(data.ph[i].thread, NULL);
			i++;
		}
		free_all(&data);
		return (0);
	}
	return (1);
}
