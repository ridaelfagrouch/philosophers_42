/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:55:05 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/04/20 14:55:08 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

//*****************************************************************************

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	check_is_digit(char *str)
{
	int	j;

	j = 0;
	if (str[j] == '-' || str[j] == '+')
			j++;
	while (ft_isdigit(str[j]) && str[j] != '\0')
		j++;
	if (ft_isdigit(str[j]) == 0 && str[j] != '\0')
	{
		write(2, "error!\n", 7);
		exit(1);
	}
}
