/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:09:47 by david             #+#    #+#             */
/*   Updated: 2026/02/04 17:14:35 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"

//mutex sao os garfos (temos que ter 2)


int ft_atoi(char *s)
{
    int i;
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

void init(t_params *params, int ac, char **av)
{
    if (ac == 6)
        params->n_teat = ft_atoi(av[5]);
    else
        params->n_teat = -1;
    params->n_philo = ft_atoi(av[1]);
    params->t_die = ft_atoi(av[2]);
    params->t_eat = ft_atoi(av[3]);
    params->t_sleep = ft_atoi(av[4]);
    params->start_time = ft_get_time();
}

void accurate_sleep(int i)
{
    int time;
  
    time = i * 1000;
    usleep(time);
}

void print_philo(char *str, t_philo *philo)
{

    long time;
    //if ()         FUNCAO DA MORTE
        
    pthread_mutex_lock(&philo->mutex_man->printf_lock);    //lock
    time = ft_get_time() - philo->params.start_time;
    printf("%ld %d %s", time, philo->id, str);
    pthread_mutex_unlock(&philo->mutex_man->printf_lock);  //lock

}


void philo_sleep(t_philo *philo)
{
    accurate_sleep(philo->params.t_sleep);
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
        pthread_mutex_lock(philo->l_fork);
        pthread_mutex_lock(philo->r_fork);
    }
    
    pthread_mutex_lock(&philo->mutex_man->end_lock);    //lock

    philo->count_eat += 1;
    print_philo("has eaten\n", philo);
    accurate_sleep(philo->params.t_eat);
    pthread_mutex_unlock(&philo->mutex_man->end_lock);    //lock
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
        accurate_sleep(10);
    while (i < philo->params.n_teat)
    {

        philo_eat(philo);    
        philo_sleep(philo);
        philo_think(philo);
        i++;
    }
    return NULL;
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
            return (false); //lembrar de fazer uam funçao para dar free a tudo
        if (pthread_mutex_init(&data->mutex_man.forks[i], NULL) != 0)
            return (false); //lembrar de fazer uam funçao para dar free a tudo
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
        //printf("L fork = %p of philo : %d\n", data->philo[i].l_fork, i);
        //printf("R fork = %p of philo : %d\n", data->philo[i].r_fork, i);
        
        
        data->philo[i].id = i + 1;
        data->philo[i].params = data->params; 
        data->philo[i].mutex_man = &data->mutex_man;
        pthread_create(&data->philo[i].thread, NULL, &routine, &data->philo[i]);
        i++;
    }
    
    i = 0;
    while(i < data->params.n_philo)
    {
        pthread_join(data->philo[i].thread, NULL);
        i++;
    }
}
void create(t_data *data)
{
    // printf("%p\n", philo);
    // printf("times eaten : %d\n", philo->count_eat);
    // printf("id : %d\n", philo->id);
    // printf("last eaten : %ld ago\n", philo->last_eat);
    // printf("Thread : %p\n", &philo->thread);
    // printf("Left fork : %p\n", philo->l_fork);
    // printf("Right fork : %p\n", philo->r_fork);
    
    create_mutex(data);
    create_philo(data);
    

}

int main(int ac, char **av)
{
    if (ac == 5 || ac == 6)
    {
        t_data data;

        memset(&data, 0, sizeof (t_data));
        memset(&data.params, 0, sizeof (t_params));
        memset(&data.mutex_man, 0, sizeof (t_mutex_man));
    
        if(!invalid_input(av))
            return(1);
        init(&data.params, ac, av);
        
        create(&data);
                
        pthread_mutex_destroy(data.mutex_man.forks);
        pthread_mutex_destroy(data.mutex_man.philo_lock);
        pthread_mutex_destroy(&data.mutex_man.end_lock);
        pthread_mutex_destroy(&data.mutex_man.printf_lock);

        return(0);
    }
    return(1);

}
