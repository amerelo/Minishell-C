/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 15:14:43 by amerelo           #+#    #+#             */
/*   Updated: 2016/03/07 15:14:44 by amerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_rep_av(t_info *i, char *tmp_home, char *oldpwd, int mod)
{
	char	*c;
	char	*tmp;

	(i->x < 1) ? i->x = 0 : 1;
	i->w = 1;
	if (mod == 1)
	{
		free(i->av[1]);
		i->av[1] = ft_strdup(oldpwd);
	}
	else
	{
		if (i->av[i->x][1] == '\0')
		{
			free(i->av[i->x]);
			i->av[i->x] = ft_strdup(tmp_home);
		}
		else if ((c = i->av[i->x]))
		{
			tmp = ft_strjoin(tmp_home, ++c);
			free(i->av[i->x]);
			i->av[i->x] = ft_strdup(tmp);
			free(tmp);
		}
	}
}

void	ft_cd_error(t_info *info, int error)
{
	if (error == 1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(info->av[1], 2);
		ft_putstr_fd("\n", 2);
	}
	else if (error == 2)
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	else if (error == 3)
	{
		ft_putstr_fd("cd: permission denied: ", 2);
		ft_putstr_fd(info->av[1], 2);
		ft_putstr_fd("\n", 2);
	}
	else if (error == 4)
		ft_putstr_fd("cd: permission denied: ", 2);
}

void	ft_path(t_info *info)
{
	char	*tmp;
	char	*pwd_tmp;

	info->error = 0;
	if (!(pwd_tmp = getcwd(NULL, 0)))
	{
		if (info->w == 0 && ft_strcmp(info->av[1], "..") == 0)
		{
			ft_cd_error(info, 1);
			return ;
		}
		else
			pwd_tmp = ft_strdup(get_element(info, "PWD", 1));
	}
	if ((chdir(info->av[1])) != 0)
		(access(info->av[1], F_OK)) ? ft_cd_error(info, 1) :
		ft_cd_error(info, 3);
	else
	{
		rep_element(info->lst, "OLDPWD", pwd_tmp);
		tmp = getcwd(NULL, 0);
		rep_element(info->lst, "PWD", tmp);
		free(tmp);
	}
	free(pwd_tmp);
}

void	ft_cd_plus(t_info *info, char *home)
{
	if (chdir(home) != 0 && info->error == 2)
	{
		ft_cd_error(info, 4);
		ft_putstr_fd(home, 2);
		ft_putstr_fd("\n", 2);
	}
	(info->error != 2 && info->error != 0) ? ft_cd_error(info, 2) : 1;
	if (info->error == 0)
	{
		rep_element(info->lst, "OLDPWD", get_element(info, "PWD", 1));
		rep_element(info->lst, "PWD", home);
	}
}

int		ft_cd(t_info *info)
{
	char	*home;
	char	*oldpwd;

	info->w = 0;
	info->error = 0;
	if (info->av[1] && info->av[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (-1);
	}
	home = ft_strdup(get_element(info, "HOME", 2));
	oldpwd = ft_strdup(get_element(info, "OLDPWD", 3));
	if (info->error <= 2 && info->av[1] && ft_strcmp(info->av[1], "-") == 0)
		ft_rep_av(info, home, oldpwd, 1);
	if (info->error <= 1 && info->av[1] && info->av[1][0] == '~')
		ft_rep_av(info, home, oldpwd, 2);
	if (info->av && !info->av[1])
		ft_cd_plus(info, home);
	if (info->av && info->av[1])
		ft_path(info);
	free(oldpwd);
	free(home);
	return (-1);
}
