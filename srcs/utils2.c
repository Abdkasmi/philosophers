/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:42:34 by abkasmi           #+#    #+#             */
/*   Updated: 2022/05/19 03:24:47 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_free_all(t_global *global, t_philo *philo, t_thread *thread)
{
	free(thread->thread);
	thread->thread = NULL;
	free(global->mutex);
	global->mutex = NULL;
	ft_free(global->philo_tab, global->n_philo);
	free(global);
	global = NULL;
	free(philo);
	philo = NULL;
}

int	ft_join_and_destroy(t_global *global, t_philo *philo, t_thread *thread)
{
	int	i;

	i = -1;
	verify_philo(global, -1);
	while (++i < global->n_philo)
	{
		if (pthread_join(thread->thread[i], NULL))
		{
			ft_free_all(global, philo, thread);
			return (1);
		}
	}
	i = -1;
	while (++i < global->n_philo)
		pthread_mutex_destroy(&global->mutex[i]);
	pthread_mutex_destroy(&global->boss_mutex);
	return (0);
}
