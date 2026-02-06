/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:09:47 by david             #+#    #+#             */
/*   Updated: 2026/02/06 21:53:29 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"

//mutex sao os garfos (temos que ter 2)


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

void accurate_sleep(long time, t_mutex_man *mutex)
{
    long start;
    
    start = ft_get_time();
    while (time > (ft_get_time() - start))
    {
        if (check_dead(mutex))
            break;
        usleep(500);   
    }
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


void philo_sleep(t_philo *philo)
{
    accurate_sleep(philo->params.t_sleep, philo->mutex_man);
    print_philo("is going to sleep zzzzzzz\n", philo);
}

void philo_eat(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        print_philo("picked up a garfoh\n", philo);
        print_philo("picked up a garfoh\n", philo); 
        pthread_mutex_lock(philo->l_fork);
        pthread_mutex_lock(philo->r_fork);
    }
    else
    {
        print_philo("picked up a garfoh\n", philo);
        print_philo("picked up a garfoh\n", philo);
        pthread_mutex_lock(philo->r_fork);
        pthread_mutex_lock(philo->l_fork);
    }
    pthread_mutex_lock(&philo->mutex_man->philo_lock[philo->id - 1]);    //lock
    philo->count_eat += 1;
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


void *routine(void *p)
{
    t_philo *philo = p;
    int i;

    i = 0;
    if (philo->id % 2 == 0)
        accurate_sleep(10, philo->mutex_man);
    while (i < philo->params.n_teat || check_dead(philo->mutex_man))
    {
        philo_eat(philo);    
        philo_sleep(philo);
        philo_think(philo);
        i++;
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
        data->philo->params.start_time = ft_get_time();
        pthread_create(&data->philo[i].thread, NULL, &routine, &data->philo[i]);
        i++;
    }
}
void create(t_data *data)
{   
    create_mutex(data);
    create_philo(data);
}

void timoty(t_data *data)
{
    int i;
    
    printf("lol");
    i = 0;
    while(1)
    {
        i = 0;
        while(i < data->params.n_philo)
        {
            pthread_mutex_lock(&data->mutex_man.philo_lock[i]);
            if ((ft_get_time() - data->philo[i].last_eat) > data->params.t_die)
            {
                pthread_mutex_lock(&data->mutex_man.end_lock);
                data->mutex_man.end_flag = true;
                pthread_mutex_unlock(&data->mutex_man.end_lock);
                pthread_mutex_unlock(&data->mutex_man.philo_lock[i]);
                break;
            }
            pthread_mutex_unlock(&data->mutex_man.philo_lock[i]);
            i++;
        }
        i++;
    }
}

int main(int ac, char **av)
{
    if (ac == 5 || ac == 6)
    {
        t_data data;

        memset(&data, 0, sizeof (t_data));
        // memset(&data.params, 0, sizeof (t_params));
        // memset(&data.mutex_man, 0, sizeof (t_mutex_man));
    
        if(!invalid_input(av))
            return(1);
        init(&data.params, ac, av);

        create(&data);
        int i;

        i = 0;
        timoty(&data);
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
