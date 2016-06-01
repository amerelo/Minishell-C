/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:22:43 by amerelo           #+#    #+#             */
/*   Updated: 2016/03/22 15:29:53 by amerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	print_lst(t_lst *info)
{
	ft_putstr(info->name);
	ft_putstr("=");
	if (info->info)
		ft_putstr(info->info);
	ft_putchar('\n');
}

void	signal_handler(int signo)
{
	signo = 0;
	ft_putstr(RG2);
}

int		check_command(t_info *info)
{
	char	*i;

	if (check_path(info) == 1)
		return (-1);
	i = ft_strchr(info->line, '/');
	if (i && (access(info->line, X_OK | F_OK)) == 0)
		return (1);
	else if (info->line[0])
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd(info->line, 2);
		ft_putstr_fd("\n", 2);
	}
	return (-1);
}

int		ft_exit(t_info *info)
{
	if (info->av[1] && info->av[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (-1);
	}
	return (1);
}

int		ft_env(t_info *info)
{
	t_lst	*tmp;

	tmp = info->lst;
	while (tmp && !(info->av[1]))
	{
		print_lst(tmp);
		tmp = tmp->next;
	}
	if (info->av[1])
	{
		info->null = (ft_strcmp(info->av[1], "-i") == 0) ? 1 : 0;
		info->av += (ft_strcmp(info->av[1], "-i") == 0) ? 2 : 1;
		if (info->av[0] != '\0')
		{
			free(info->line);
			info->line = ft_strdup(info->av[0]);
			if (check_command(info) > 0)
				ft_exec(info->line, info->av, info);
		}
		info->av--;
		info->av -= (ft_strcmp(info->av[0], "-i") == 0) ? 1 : 0;
	}
	return (-1);
}
