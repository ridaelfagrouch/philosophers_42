/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 11:44:05 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/04/22 11:44:08 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wite_space(const char *str, long int *i)
{
	*i = 0;
	while ((str[*i] == ' ') || (str[*i] == '\r')
		|| (str[*i] == '\n') || (str[*i] == '\t')
		|| (str[*i] == '\v') || (str[*i] == '\f'))
	{
		*i += 1;
	}
}

static int	len_str(const char *str, enum e_erreur *exit_)
{
	int	len;

	len = 0;
	if (ft_strlen(str) == 1 && (str[0] == '-' || str[0] == '+'))
	{
		write(2, "error: invalid arg!!\n", 21);
		*exit_ = erreur_;
		return (0);
	}
	if (str[0] == '-' || str[0] == '+')
		str++;
	while (*str == '0')
		str++;
	while (str[len])
		len++;
	if (len > 10)
		return (1);
	else
		return (0);
}

static void	error_(int sign, long int k, const char *str, enum e_erreur *exit_)
{
	if ((sign * k) > 2147483647 || (sign * k) < -2147483648)
	{
		write(2, "error: invalid arg!!\n", 21);
		*exit_ = erreur_;
		return ;
	}
	if (len_str(str, exit_))
	{
		write(2, "error: invalid nember!!\n", 24);
		*exit_ = erreur_;
		return ;
	}
	if (*exit_ == erreur_)
		return ;
}

int	ft_atoi(const char *str, enum e_erreur *exit_)
{
	char		*src;
	int			sign;
	long int	k;
	long int	i;

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
	error_(sign, k, str, exit_);
	if (*exit_ == erreur_)
		return (0);
	return (sign * k);
}
