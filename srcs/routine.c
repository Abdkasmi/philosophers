/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:11:24 by abkasmi           #+#    #+#             */
/*   Updated: 2022/05/17 15:07:36 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	speaking(char *s, t_philo *philo)
{
	pthread_mutex_lock(&philo->global2->boss_mutex);
	if (!ft_strncmp(s, "is eating", 10))
	{
		philo->must_eat++;
		if (philo->must_eat == philo->global2->n_t_must_eat)
			philo->global2->total_eat++;
	}
	if (!philo->global2->is_alive)
	{
		pthread_mutex_unlock(&philo->global2->boss_mutex);
		return ;
	}
	printf("%d %d %s\n", get_time() - philo->global2->start,
		philo->philo_id, s);
	pthread_mutex_unlock(&philo->global2->boss_mutex);
}

void	routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->global2->mutex[philo->mutex_id]);
	speaking("took a fork", philo);
	if (philo->philo_id < philo->global2->n_philo)
		pthread_mutex_lock(&philo->global2->mutex[philo->mutex_id + 1]);
	else if (philo->global2->n_philo != 1)
		pthread_mutex_lock(&philo->global2->mutex[0]);
	else
		return ;
	speaking("took a fork", philo);
	speaking("is eating", philo);
	philo->time_philo_eat = get_time();
	ft_usleep(philo->global2->t_eat);
	if (philo->philo_id < philo->global2->n_philo)
		pthread_mutex_unlock(&philo->global2->mutex[philo->mutex_id + 1]);
	else if (philo->global2->n_philo != 1)
		pthread_mutex_unlock(&philo->global2->mutex[0]);
	pthread_mutex_unlock(&philo->global2->mutex[philo->mutex_id]);
	speaking("is sleeping", philo);
	ft_usleep(philo->global2->t_sleep);
	speaking("is thinking", philo);
}

void	*philosophers(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if ((philo->philo_id) % 2 == 0)
		ft_usleep(200);
	while (philo->global2->is_alive)
	{
		routine(philo);
		if (philo->global2->n_philo == 1)
		{
			pthread_mutex_unlock(&philo->global2->mutex[philo->mutex_id]);
			break ;
		}
	}
	return (NULL);
}
