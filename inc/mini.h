/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 14:46:40 by amerelo           #+#    #+#             */
/*   Updated: 2016/03/04 15:23:14 by amerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H
# include "libft.h"
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <signal.h>
# define NF 5
# define RG "\e[0;32mminishell$>\e[0;55m"
# define RG2 "\n\e[0;32mminishell$>\e[0;55m"

typedef struct		s_lst
{
	char			*name;
	char			*info;
	struct s_lst	*next;
}					t_lst;

typedef struct		s_cmd
{
	int				value[2];
	struct s_piece	*next;
}					t_cmd;

typedef struct		s_info
{
	int				size;
	int				error;
	int				w;
	int				t;
	int				x;
	int				null;
	char			**env;
	char			**av;
	char			*line;
	char			**keywords;
	int				(*f[NF])(struct s_info *info);
	t_lst			*lst;
	t_cmd			*cmd;
}					t_info;

void				free_tab(char **tab);
void				print_tab(char **env);
int					fct_find(t_info *info);
int					treat_line(t_info *info);
void				signal_handler(int signo);
void				ft_exec(char *line, char **av, t_info *info);
int					check_path(t_info *info);
int					check_command(t_info *info);
void				ft_rep_av(t_info *info, char *tmp_home,
					char *oldpwd, int mod);
void				ft_initlist(t_lst **head, t_lst **inf);
void				ft_add_in_lst(t_info *info, int mod);
char				**lst_to_tab(t_info *info);
char				*get_element(t_info *info, char *name, int mod);
void				rep_element(t_lst *info, char *name, char *src);
void				creat_list(t_info *info, char **src);
int					init(t_info *info, char **av, char **env, char **keywords);
void				ft_repenv(char *name, t_info *info, char *rep);
char				**ft_getenv(char *name, char **env);
int					ft_cd(t_info *info);
int					ft_exit(t_info *info);
int					ft_setenv(t_info *info);
int					ft_unsetenv(t_info *info);
int					ft_env(t_info *info);

#endif
