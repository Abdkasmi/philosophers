/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:47:09 by abkasmi           #+#    #+#             */
/*   Updated: 2022/05/19 04:29:33 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	to_do(t_global *global, t_philo *philo, t_thread *thread, char **av)
{
	if (!init_struct(global, av, global->ac))
	{
		free(global);
		free(philo);
		return (0);
	}
	thread->thread = malloc(sizeof(t_thread) * global->n_philo);
	if (!thread->thread)
	{
		free(global);
		free(philo);
		return (0);
	}
	if (init_thread(global, thread, philo))
		return (0);
	return (1);
}

int	main(int ac, char *av[])
{
	t_global	*global;
	t_philo		*philo;
	t_thread	thread;

	global = malloc(sizeof(t_global));
	if (!global)
		return (1);
	philo = malloc(sizeof(t_philo));
	if (!philo)
	{
		free(global);
		return (1);
	}
	global->ac = ac;
	if (ac == 5 || ac == 6)
	{
		if (!to_do(global, philo, &thread, av))
			return (0);
	}
	else
		write(1, "Arguments error\n", 17);
	return (0);
}
