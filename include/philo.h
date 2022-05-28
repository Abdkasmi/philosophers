/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:34:36 by abkasmi           #+#    #+#             */
/*   Updated: 2022/05/19 03:44:47 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <sys/time.h>
//# include "../wraloc/wraloc.h"

typedef struct s_thread{
	pthread_t		*thread;
}				t_thread;

typedef struct s_global{
	long			n_philo;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	int				n_t_must_eat;
	int				is_alive;
	int				total_eat;
	int				t;
	int				ac;
	useconds_t		start;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	boss_mutex;
	struct s_philo	**philo_tab;
}				t_global;

typedef struct s_philo{
	int				philo_id;
	int				mutex_id;
	long			time_philo_eat;
	int				must_eat;
	struct s_global	*global2;
}				t_philo;

int			init_thread(t_global *glo, t_thread *thread, t_philo *philo);
int			init_struct(t_global *global, char **arg, int ac);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(char *str);
int			create(t_global *global, t_thread *thread);
int			init_variables(t_global *global);
int			alloc(t_global *global, t_thread *thread, t_philo *philo);
int			ft_join_and_destroy(t_global *glo, t_philo *phil, t_thread *thread);

useconds_t	get_time(void);

void		ft_usleep(long wait_time);
void		speaking(char *s, t_philo *philo);
void		*philosophers(void *arg);
void		routine(t_philo *philo);
void		ft_free(t_philo **tab, int n);
void		ft_free_all(t_global *global, t_philo *philo, t_thread *thread);
void		verify_philo(t_global *global, int i);

#endif