/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvidal <dvidal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:43:52 by dvidal            #+#    #+#             */
/*   Updated: 2026/02/09 16:56:09 by dvidal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdint.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_prm
{
	long	t_die;
	long	s_t;
	long	t_sleep;
	long	t_eat;
	int		n_ph;
	int		n_teat;

}	t_prm;

typedef struct s_mutex_man
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*ph_lock;
	pthread_mutex_t	printf_lock;
	pthread_mutex_t	end_lock;
	bool			end_flag;

}	t_mutex_man;

typedef struct s_philo
{
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_t		thread;
	t_prm			params;
	t_mutex_man		*mutex_man;
	long			l_eat;
	int				id;
	int				count_eat;
	bool			full;

}	t_philo;

typedef struct s_data
{
	t_prm		prm;
	t_philo		*ph;
	t_mutex_man	mutex_man;
	long		start_time;

}	t_data;

void	free_all(t_data *data);
long	ft_atol(char *s);
void	*ft_calloc(size_t num, size_t tam);
long	ft_get_time(void);
void	accurate_sleep(long time, t_mutex_man *mutex);
int		check_dead(t_mutex_man *mutex);
bool	create_mutex(t_data *data);
bool	create_philo(t_data *data);
bool	create(t_data *data);
void	philo_eat(t_philo *philo);
void	philo_think(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	print_philo(char *str, t_philo *philo);
void	*routine(void *p);
bool	invalid_input(char **av);
void	lonely(char **av);
bool	check_time_to_die(t_data *dt);
bool	check_is_full(t_data *data);
void	check_end(t_data *data);

#endif