/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:58:29 by abkasmi           #+#    #+#             */
/*   Updated: 2022/05/17 16:35:42 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_struct(t_global *global, char **arg, int ac)
{
	global->n_philo = ft_atoi(arg[1]);
	global->t_die = ft_atoi(arg[2]);
	global->t_eat = ft_atoi(arg[3]);
	global->t_sleep = ft_atoi(arg[4]);
	global->n_t_must_eat = 0;
	if (ac == 6)
		global->n_t_must_eat = ft_atoi(arg[5]);
	if (global->n_philo < 1)
	{
		write(1, "Error!\n", 7);
		return (0);
	}
	if (ac == 5 && (global->t_die < 0 || global->t_sleep < 0
			|| global->t_eat < 0))
	{
		write(1, "Error!\n", 7);
		return (0);
	}
	if (ac == 6 && (global->t_die < 0 || global->t_sleep < 0
			|| global->t_eat < 0 || global->n_t_must_eat < 0))
	{
		write(1, "Error!\n", 7);
		return (0);
	}
	return (1);
}
