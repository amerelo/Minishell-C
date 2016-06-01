/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 18:27:03 by amerelo           #+#    #+#             */
/*   Updated: 2016/03/13 18:27:04 by amerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_remove_in_lst(t_info *info)
{
	t_lst	*prev_1;
	t_lst	*tmp;

	tmp = info->lst;
	prev_1 = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, info->av[1]) == 0)
		{
			free(tmp->info);
			free(tmp->name);
			if (prev_1 != NULL)
				prev_1->next = tmp->next;
			else
				info->lst = tmp->next;
			free(tmp);
			info->size -= 1;
			return ;
		}
		prev_1 = tmp;
		tmp = tmp->next;
	}
}

int		ft_unsetenv(t_info *info)
{
	if (!info->av[1])
		ft_putstr_fd("ft_setenv: too few arguments\n", 2);
	else if (info->av[2])
		ft_putstr_fd("ft_setenv: too many arguments\n", 2);
	else if (ft_strchr(info->av[1], '=') != NULL)
		ft_putstr_fd("ft_setenv: = can't be assigned\n", 2);
	else
		ft_remove_in_lst(info);
	return (-1);
}

void	ft_add_in_lst(t_info *i, int mod)
{
	t_lst	*tmp;

	tmp = i->lst;
	while (1)
	{
		if (tmp && ft_strcmp(tmp->name, i->av[1]) == 0)
		{
			if (mod == 1)
			{
				(tmp->info) ? free(tmp->info) : 1;
				if (i->av[1] && i->av[2])
					tmp->info = ft_strdup(i->av[2]);
			}
			return ;
		}
		if (tmp == NULL || tmp->next == NULL)
		{
			ft_initlist(&i->lst, &tmp);
			i->size++;
			tmp->name = ft_strdup(i->av[1]);
			tmp->info = (i->av[1] && i->av[2]) ? ft_strdup(i->av[2]) : NULL;
			return ;
		}
		tmp = tmp->next;
	}
}

int		ft_setenv(t_info *info)
{
	int		mod;

	mod = 0;
	if (!info->av[1])
	{
		ft_env(info);
		return (-1);
	}
	if (info->av[2] && info->av[3] && (ft_strcmp(info->av[3], "1") == 0))
		mod = 1;
	else if (info->av[2] && info->av[3] && (ft_strcmp(info->av[3], "0") != 0))
	{
		ft_putstr_fd("ft_setenv: bad argument\n", 2);
		return (-1);
	}
	if (info->av[2] && info->av[3] && info->av[4])
		ft_putstr_fd("ft_setenv: too many argumens\n", 2);
	else if (ft_strchr(info->av[1], '=') || (info->av[2] &&\
	ft_strchr(info->av[2], '=')))
		ft_putstr_fd("ft_setenv: = can't be assigned\n", 2);
	else
		ft_add_in_lst(info, mod);
	return (-1);
}
