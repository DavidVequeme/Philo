/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 22:06:55 by david             #+#    #+#             */
/*   Updated: 2026/02/06 23:06:10 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool create_mutex(t_data *data)
{
    int i;

    i = 0;
    
    data->mutex_man.forks = ft_calloc(data->params.n_philo, sizeof (pthread_mutex_t));
    data->mutex_man.philo_lock = ft_calloc(data->params.n_philo, sizeof (pthread_mutex_t));

    if (data->mutex_man.forks == NULL || data->mutex_man.philo_lock == NULL)
        return (free(data->mutex_man.forks), free(data->mutex_man.philo_lock), false);
    pthread_mutex_init(&data->mutex_man.end_lock, NULL);
    pthread_mutex_init(&data->mutex_man.printf_lock, NULL);
    while(i < data->params.n_philo)
    {
        if (pthread_mutex_init(&data->mutex_man.philo_lock[i], NULL) != 0)
            return (free_all(data), false); //lembrar de fazer uam funçao para dar free a tudo
        if (pthread_mutex_init(&data->mutex_man.forks[i], NULL) != 0)
            return (free_all(data), false); //lembrar de fazer uam funçao para dar free a tudo
        i++;
    }
    return (true);
}
void create_philo(t_data *data)
{
    int  i;

    i = 0;
    data->philo = ft_calloc(data->params.n_philo, sizeof (t_philo));
    while(i < data->params.n_philo)
    {
        data->philo[i].l_fork = &data->mutex_man.forks[i];
        if (i == 0)
            data->philo[i].r_fork = &data->mutex_man.forks[data->params.n_philo - 1];
        else
            data->philo[i].r_fork = &data->mutex_man.forks[i - 1];
        data->philo[i].id = i + 1;
        data->philo[i].params = data->params; 
        data->philo[i].mutex_man = &data->mutex_man;
        data->philo->last_eat = ft_get_time();
        pthread_create(&data->philo[i].thread, NULL, &routine, &data->philo[i]);
        i++;
    }
}
void create(t_data *data)
{   
    create_mutex(data);
    create_philo(data);
}