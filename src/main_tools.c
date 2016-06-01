/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 19:08:21 by amerelo           #+#    #+#             */
/*   Updated: 2016/03/12 19:08:22 by amerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	free_tab(char **tab)
{
	int x;

	x = 0;
	while (tab[x] && tab[x][0])
	{
		free(tab[x]);
		++x;
	}
	free(tab);
}

void	print_tab(char **env)
{
	int y;

	y = 0;
	while (env[y])
	{
		ft_putstr(env[y]);
		ft_putstr("\n");
		++y;
	}
}

int		init(t_info *info, char **av, char **env, char **keywords)
{
	if (av[1])
	{
		ft_putstr_fd("minishell: can't open input file ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	creat_list(info, env);
	info->null = 0;
	info->av = NULL;
	info->line = NULL;
	info->keywords = keywords;
	info->f[0] = ft_exit;
	info->f[1] = ft_cd;
	info->f[2] = ft_setenv;
	info->f[3] = ft_env;
	info->f[4] = ft_unsetenv;
	return (1);
}

int		fct_find(t_info *info)
{
	int	i;

	i = -1;
	while (++i < NF)
	{
		if (!ft_strcmp(info->line, info->keywords[i]))
			return (i);
	}
	return (NF);
}

int		treat_line(t_info *info)
{
	int f;

	f = fct_find(info);
	if (f == NF)
		return (1);
	info->t = 1;
	if ((info->f[f](info)) == -1)
		return (1);
	else
		return (-1);
	return (1);
}
