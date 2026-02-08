/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 22:01:27 by david             #+#    #+#             */
/*   Updated: 2026/02/08 17:12:11 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void philo_eat(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->l_fork);
        pthread_mutex_lock(philo->r_fork);
        print_philo("picked up a garfoh\n", philo);
        print_philo("picked up a garfoh\n", philo); 
    }
    else
    {
        pthread_mutex_lock(philo->r_fork);
        pthread_mutex_lock(philo->l_fork);
        print_philo("picked up a garfoh\n", philo);
        print_philo("picked up a garfoh\n", philo);
    }
    pthread_mutex_lock(&philo->mutex_man->philo_lock[philo->id - 1]);    //lock
    philo->count_eat += 1;
    if (philo->count_eat == philo->params.n_teat)
        philo->tou_cheio = true;
    philo->last_eat = ft_get_time(); 
    print_philo("has eaten\n", philo);
    accurate_sleep(philo->params.t_eat, philo->mutex_man);
    pthread_mutex_unlock(&philo->mutex_man->philo_lock[philo->id - 1]);    //lock
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
}

void philo_think(t_philo *philo)
{
    print_philo("is thinking HMMMMMMMM\n", philo);
}

void philo_sleep(t_philo *philo)
{
    accurate_sleep(philo->params.t_sleep, philo->mutex_man);
    print_philo("is going to sleep zzzzzzz\n", philo);
}

void print_philo(char *str, t_philo *philo)
{

    long time;
    if (check_dead(philo->mutex_man))
        return ;
    pthread_mutex_lock(&philo->mutex_man->printf_lock);    //lock
    time = ft_get_time() - philo->params.start_time;
    printf("%ld %d %s", time, philo->id, str);
    pthread_mutex_unlock(&philo->mutex_man->printf_lock);  //lock

}