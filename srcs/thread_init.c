/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:14:39 by abkasmi           #+#    #+#             */
/*   Updated: 2022/05/19 03:41:15 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_thread(t_global *global, t_thread *thread, t_philo *philo)
{
	int			verif;

	if (alloc(global, thread, philo))
		return (1);
	verif = init_variables(global);
	if (verif)
	{
		free(thread);
		free(global);
		free(philo);
		ft_free(global->philo_tab, verif);
		return (1);
	}
	philo->philo_id = 0;
	if (create(global, thread))
	{
		ft_free_all(global, philo, thread);
		return (1);
	}
	if (ft_join_and_destroy(global, philo, thread))
		return (1);
	ft_free_all(global, philo, thread);
	return (0);
}

int	init_variables(t_global *global)
{
	int	i;

	global->start = get_time();
	global->is_alive = 1;
	global->total_eat = 0;
	i = -1;
	while (++i < global->n_philo)
	{
		global->philo_tab[i] = malloc(sizeof(t_philo));
		if (!global->philo_tab[i])
			return (i);
		global->philo_tab[i]->mutex_id = i;
		global->philo_tab[i]->global2 = global;
		global->philo_tab[i]->time_philo_eat = global->start;
		global->philo_tab[i]->must_eat = 0;
	}
	global->mutex = malloc(sizeof(pthread_mutex_t) * global->n_philo);
	if (!global->mutex)
		return (i);
	return (0);
}

int	create(t_global *global, t_thread *thread)
{
	int	i;

	i = -1;
	global->t = 1;
	if (pthread_mutex_init(&global->boss_mutex, NULL))
		return (1);
	while (++i < global->n_philo)
		if (pthread_mutex_init(&global->mutex[i], NULL))
			return (1);
	i = -1;
	while (++i < global->n_philo)
	{
		global->philo_tab[i]->philo_id = i + 1;
		if (pthread_create(&thread->thread[i], NULL, &philosophers,
				global->philo_tab[i]))
			return (1);
	}
	global->t = 0;
	return (0);
}

void	verify_philo(t_global *global, int i)
{
	while (1)
	{
		++i;
		if (global->n_t_must_eat)
		{
			if (global->total_eat == global->n_philo)
			{	
				global->is_alive = 0;
				break ;
			}
		}
		if ((get_time() - global->philo_tab[i]->time_philo_eat)
			> global->t_die)
		{
			global->is_alive = 0;
			printf("%d %d died\n", get_time() - global->start,
				global->philo_tab[i]->philo_id);
			break ;
		}
		else if (i == global->n_philo - 1)
			i = -1;
	}
}

int	alloc(t_global *global, t_thread *thread, t_philo *philo)
{
	global->philo_tab = malloc(sizeof(t_philo) * global->n_philo);
	if (!global->philo_tab)
	{
		free(thread);
		free(global);
		free(philo);
		return (1);
	}
	return (0);
}
