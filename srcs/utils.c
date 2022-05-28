/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:03:04 by abkasmi           #+#    #+#             */
/*   Updated: 2022/05/19 04:04:16 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(char *str)
{
	int			i;
	long long	num;
	int			sign;

	i = 0;
	sign = 0;
	num = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = 1;
		i++;
	}
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			num = num * 10 + (str[i] - '0');
		else if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	if (sign)
		return (-num);
	return (num);
}

void	ft_usleep(long wait_time)
{
	long	start_time;

	start_time = get_time();
	while (get_time() - start_time < wait_time)
		usleep(250);
}

useconds_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		return (0);
	while (i < n - 1 && s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	if (i == n && s1[i] == s2[i])
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_free(t_philo **tab, int n)
{
	while (--n >= 0)
		free(tab[n]);
	free(tab);
	tab = NULL;
}
