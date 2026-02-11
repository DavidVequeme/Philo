/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvidal <dvidal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 22:01:27 by david             #+#    #+#             */
/*   Updated: 2026/02/09 16:32:36 by dvidal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
		print_philo("has taken fork\n", philo);
		print_philo("has taken fork\n", philo);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
		print_philo("has taken fork\n", philo);
		print_philo("has taken fork\n", philo);
	}
	pthread_mutex_lock(&philo->mutex_man->ph_lock[philo->id - 1]);
	philo->l_eat = ft_get_time();
	philo->count_eat += 1;
	if (philo->count_eat == philo->params.n_teat)
		philo->full = true;
	pthread_mutex_unlock(&philo->mutex_man->ph_lock[philo->id - 1]);
	print_philo("is eating\n", philo);
	accurate_sleep(philo->params.t_eat, philo->mutex_man);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	philo_think(t_philo *philo)
{
	print_philo("is thinking\n", philo);
}

void	philo_sleep(t_philo *philo)
{
	print_philo("is sleeping\n", philo);
	accurate_sleep(philo->params.t_sleep, philo->mutex_man);
}

void	print_philo(char *str, t_philo *philo)
{
	long	time;

	if (check_dead(philo->mutex_man))
		return ;
	pthread_mutex_lock(&philo->mutex_man->printf_lock);
	time = ft_get_time() - philo->params.s_t;
	printf("%ld %d %s", time, philo->id, str);
	pthread_mutex_unlock(&philo->mutex_man->printf_lock);
}

void	lonely(char **av)
{
	long	time;

	time = ft_atol(av[2]);
	printf("0 1 has taken a fork\n");
	usleep(time * 1000);
	printf("%ld 1 died\n", time);
}
