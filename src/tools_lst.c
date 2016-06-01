/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 17:27:03 by amerelo           #+#    #+#             */
/*   Updated: 2016/03/10 17:27:08 by amerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_initlist(t_lst **head, t_lst **inf)
{
	if (!(*head))
	{
		*inf = (t_lst *)malloc(sizeof(t_lst));
		*head = *inf;
		(*inf)->next = NULL;
	}
	else
	{
		(*inf)->next = (t_lst *)malloc(sizeof(t_lst));
		(*inf) = (*inf)->next;
		(*inf)->next = NULL;
	}
}

char	**lst_to_tab(t_info *info)
{
	int		x;
	t_lst	*tmp2;
	char	**tab;

	tab = (char **)ft_memalloc(sizeof(char *) * (info->size + 2));
	if (!tab)
		return (NULL);
	x = 0;
	tmp2 = info->lst;
	while (x <= info->size)
	{
		if (tmp2->info)
			tab[x] = ft_strjoin_char(tmp2->name, tmp2->info, '=');
		else
			tab[x] = ft_strjoin(tmp2->name, "=");
		tmp2 = tmp2->next;
		++x;
	}
	return (tab);
}

void	rep_element(t_lst *info, char *name, char *src)
{
	t_lst	*tmp;

	tmp = info;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			free(tmp->info);
			tmp->info = ft_strdup(src);
			return ;
		}
		tmp = tmp->next;
	}
}

char	*get_element(t_info *info, char *name, int mod)
{
	t_lst	*tmp;

	tmp = info->lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0 && tmp->info)
			return (tmp->info);
		else if (ft_strcmp(tmp->name, name) == 0 && info->av[1])
			return (info->av[1]);
		else if (ft_strcmp(tmp->name, name) == 0 && !info->av[1])
			return (NULL);
		tmp = tmp->next;
	}
	info->error = (mod == 2) ? 2 : 1;
	(mod == 3) ? info->error = 3 : 1;
	if (info->av && info->av[1])
		return (info->av[1]);
	return ("error");
}

void	creat_list(t_info *info, char **src)
{
	t_lst	*head;
	t_lst	*inf;
	char	**tmp;
	int		x;

	x = 0;
	head = NULL;
	while (src[x])
	{
		tmp = ft_strsplit(src[x], '=');
		ft_initlist(&head, &inf);
		inf->name = ft_strdup(tmp[0]);
		if ((ft_strcmp(inf->name, "SHLVL")) == 0)
		{
			info->x = ft_atoi(tmp[1]);
			info->x++;
			inf->info = ft_itoa(info->x);
		}
		else
			inf->info = (tmp[1]) ? ft_strdup(tmp[1]) : NULL;
		free_tab(tmp);
		++x;
	}
	info->size = x - 1;
	info->lst = head;
}
