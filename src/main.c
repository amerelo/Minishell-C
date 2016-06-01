/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 14:51:08 by amerelo           #+#    #+#             */
/*   Updated: 2016/03/22 15:29:41 by amerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_exec(char *line, char **av, t_info *info)
{
	int		status;
	int		pid_c;

	info->env = lst_to_tab(info);
	pid_c = fork();
	if (pid_c == 0)
	{
		if (info->null == 0)
			execve(line, av, info->env);
		else
			execve(line, av, NULL);
	}
	else
		waitpid(pid_c, &status, 0);
	info->null = 0;
	free_tab(info->env);
}

void	ft_check_av_plus(t_info *i)
{
	char	*tmp_home;
	int		y;
	int		t;

	y = -1;
	t = -1;
	if (i->lst == NULL)
		return ;
	tmp_home = ft_strdup(get_element(i, "HOME", 2));
	while (i->av[i->x] && i->av[i->x][0] == '-')
		i->x++;
	while (i->av[i->x + ++y])
	{
		while (i->av[i->x + y][++t])
		{
			if (i->av[i->x + y] && ((ft_isprint(i->av[i->x + y][t])) == 0))
				return ;
		}
	}
	while (i->av[i->x])
	{
		(i->av[i->x][0] == '~') ? ft_rep_av(i, tmp_home, NULL, 2) : 1;
		i->x++;
	}
	free(tmp_home);
}

void	ft_check_av(t_info *info)
{
	char	*tmp;
	char	*tmp_line;

	tmp_line = ft_strdup(info->line);
	tmp = NULL;
	info->x = 1;
	while ((tmp = ft_strchr(tmp_line, '\t')))
	{
		*tmp = ' ';
		tmp = NULL;
	}
	tmp = ft_strchr(tmp_line, ' ');
	if (info->av != NULL)
		free_tab(info->av);
	info->av = ft_strsplit(tmp_line, ' ');
	if (tmp != NULL)
		*tmp = '\0';
	free(info->line);
	info->line = ft_strdup(tmp_line);
	free(tmp_line);
	ft_check_av_plus(info);
}

int		check_path(t_info *info)
{
	int		x;
	char	*path;
	char	**tmp_path;

	x = 0;
	path = get_element(info, "PATH", 1);
	if (!(tmp_path = ft_strsplit(path, ':')))
		return (-1);
	while (tmp_path[x] && info->line[0])
	{
		path = ft_strjoin_char(tmp_path[x], info->line, '/');
		if ((access(path, X_OK | F_OK)) == 0)
		{
			ft_exec(path, info->av, info);
			free_tab(tmp_path);
			free(path);
			return (1);
		}
		++x;
		free(path);
	}
	free_tab(tmp_path);
	return (-1);
}

int		main(int ac, char **av, char **env)
{
	char			*line;
	t_info			info;
	static char		*keywords[5] = {"exit", "cd", "setenv", "env", "unsetenv"};

	(void)ac;
	if ((init(&info, av, env, keywords)) != 1)
		return (-1);
	while (1)
	{
		signal(SIGINT, signal_handler);
		ft_putstr(RG);
		info.t = 0;
		if (get_next_line(0, &line) <= 0)
			return (1);
		info.line = ft_strtrim(line);
		(info.line[0]) ? ft_check_av(&info) : 1;
		free(line);
		if (treat_line(&info) == -1)
			return (ft_atoi(info.av[1]));
		else if (info.t == 0 && check_command(&info) > 0)
			ft_exec(info.line, info.av, &info);
		free(info.line);
	}
	return (1);
}
