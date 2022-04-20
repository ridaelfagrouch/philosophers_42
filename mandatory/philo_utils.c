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

void	wite_space(const char *str, unsigned int *i)
{
	while ((str[*i] == ' ') || (str[*i] == '\r')
		|| (str[*i] == '\n') || (str[*i] == '\t')
		|| (str[*i] == '\v') || (str[*i] == '\f'))
	{
		*i += 1;
	}
}

int	ft_atoi(const char *str)
{
	char			*src;
	unsigned int	i;
	int				sign;
	int				k;

	i = 0;
	sign = 1;
	k = 0;
	src = (char *) str;
	wite_space(str, &i);
	if (src[i] == '-')
	{
		sign = sign * -1;
		i++;
	}
	else if (src[i] == '+')
		i++;
	while (src[i] >= 48 && src[i] <= 57)
	{
		k = k * 10 + src[i] - '0';
		i++;
	}
	return (sign * k);
}

//*****************************************************************************

void	check_is_digit(char *str)
{
	int	j;

	j = 0;
	while (ft_isdigit(str[j]) && str[j] != '\0')
		j++;
	if (ft_isdigit(str[j]) == 0 && str[j] != '\0')
	{
		write(2, "error!\n", 7);
		exit(1);
	}
}
