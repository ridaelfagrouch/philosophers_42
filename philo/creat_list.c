/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:00:26 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/05/05 14:00:29 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_node	*new_node(int index, t_info *info, t_erreur *isexit)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
	{
		*isexit = yes;
		return (NULL);
	}
	if (pthread_mutex_init(&node->fork, NULL))
	{
		*isexit = yes;
		return (NULL);
	}
	node->index = index;
	node->last_meal = 0;
	node->nmb_of_eat = 0;
	node->share = info;
	node->next = NULL;
	return (node);
}

//*****************************************************************************

static void	add_back(t_node **lst, t_node *node)
{
	t_node	*new;

	if (!node)
		return ;
	if (!lst[0])
	{
		lst[0] = node;
		node->next = node;
		return ;
	}
	new = lst[0];
	while (new->next != lst[0])
		new = new->next;
	new->next = node;
	node->next = lst[0];
}

//*****************************************************************************

void	creatlist(t_info *info, t_erreur *isexit)
{
	int	i;

	i = 0;
	info->head = NULL;
	while (i < info->nmb_of_thread)
	{
		add_back(&info->head, new_node(i, info, isexit));
		if (*isexit == yes)
			return ;
		i++;
	}
	info->tmp = info->head;
}
