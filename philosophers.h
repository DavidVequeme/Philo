


#ifndef FILOSOFERS
#define FILOSOFERS

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdint.h>
# include <stdbool.h>
# include <sys/time.h>


typedef struct s_params
{
    long t_die;
    long start_time;
    int n_philo;
    int t_eat;
    int t_sleep;
    int n_teat;

} t_params;


typedef struct s_mutex_man
{

    pthread_mutex_t *forks;
    pthread_mutex_t *philo_lock;
    pthread_mutex_t printf_lock;
    pthread_mutex_t end_lock;
    bool end_flag;
    

} t_mutex_man;


typedef struct s_philo
{
    pthread_mutex_t *l_fork;
    pthread_mutex_t *r_fork;
    pthread_t thread;
    t_params params;
    t_mutex_man *mutex_man;
    long last_eat;
    int id;
    int count_eat;
    
} t_philo;    


typedef struct s_data
{
    t_params params;
    t_philo *philo;
    t_mutex_man mutex_man;
    long start_time;

} t_data;





bool invalid_input(char **av);

#endif