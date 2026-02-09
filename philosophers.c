/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:09:47 by david             #+#    #+#             */
/*   Updated: 2026/02/08 18:23:40 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"

//mutex sao os garfos (temos que ter 2)

void init(t_params *params, int ac, char **av)
{
    if (ac == 6)
        params->n_teat = ft_atol(av[5]);
    else
        params->n_teat = -1;
    params->n_philo = ft_atol(av[1]);
    params->t_die = ft_atol(av[2]);
    params->t_eat = ft_atol(av[3]);
    params->t_sleep = ft_atol(av[4]);
    params->start_time = ft_get_time();
}
void *routine(void *p)
{
    t_philo *philo = p;

    if (philo->id % 2 == 0)
        accurate_sleep(10, philo->mutex_man);
    while (!check_dead(philo->mutex_man))
    {
        philo_eat(philo);
        if (philo->count_eat == philo->params.n_teat)
            return NULL;    
        philo_sleep(philo);
        philo_think(philo);
    }
    return NULL;
}

void free_all(t_data *data)
{
    int i;

    i = 0;
    while(i < data->params.n_philo)
    {
        pthread_mutex_destroy(&data->mutex_man.forks[i]);
        pthread_mutex_destroy(&data->mutex_man.philo_lock[i]);
        i++;
    }
    pthread_mutex_destroy(&data->mutex_man.end_lock);
    pthread_mutex_destroy(&data->mutex_man.printf_lock);
    free(data->philo);
    free(data->mutex_man.forks);
    free(data->mutex_man.philo_lock);
}

bool check_time_to_die(t_data *data)
{
    int i;
 
    i = 0;
    while(i < data->params.n_philo)
    {
        pthread_mutex_lock(&data->mutex_man.philo_lock[i]);
        if ((ft_get_time() - data->philo[i].last_eat ) >= data->params.t_die)
        {
            pthread_mutex_lock(&data->mutex_man.end_lock);
            data->mutex_man.end_flag = true;
            pthread_mutex_unlock(&data->mutex_man.end_lock);
            pthread_mutex_unlock(&data->mutex_man.philo_lock[i]);
            pthread_mutex_lock(&data->mutex_man.printf_lock);
            printf("%ld %d died\n", ft_get_time() - data->params.start_time, data->philo[i].id);
            pthread_mutex_unlock(&data->mutex_man.printf_lock);
            return (false);
        }
        pthread_mutex_unlock(&data->mutex_man.philo_lock[i]);
        i++;
    }
    return(true);
}

bool check_is_full(t_data *data)
{
    int i;
    int check;
    
    i = 0;
    check = 0;
    while(i < data->params.n_philo)
    {
        pthread_mutex_lock(&data->mutex_man.philo_lock[i]);
        if (data->philo[i].tou_cheio == true)
            check++;
        if (check == data->params.n_philo)
        {
            pthread_mutex_lock(&data->mutex_man.end_lock);
            data->mutex_man.end_flag = true;
            pthread_mutex_unlock(&data->mutex_man.end_lock);
            pthread_mutex_unlock(&data->mutex_man.philo_lock[i]);
            printf("\nBUUUUUURP!!!\n");
            return(false) ;
        }
        pthread_mutex_unlock(&data->mutex_man.philo_lock[i]);
        i++;
    }
    return(true);
}

void check_end(t_data *data)
{
    while(1)
    {
        if (!check_time_to_die(data) || !check_is_full(data))
            break;
        usleep(1000);
    }
}

int main(int ac, char **av)
{
    if (ac == 5 || ac == 6)
    {
        t_data data;
        int i;
        memset(&data, 0, sizeof (t_data));
        if(!invalid_input(av))
            return(1);
        init(&data.params, ac, av);

        create(&data);
        usleep(100);
        i = 0;
        check_end(&data);
        while(i < data.params.n_philo)
        {
            pthread_join(data.philo[i].thread, NULL);
            i++;
        }
        free_all(&data);
        return(0);
    }
    return(1);

}
