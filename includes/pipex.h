/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:27:18 by nadesjar          #+#    #+#             */
/*   Updated: 2022/07/19 13:20:23 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../ft_printf/ft_printf.h"

# define BUFFER_SIZE 4096

typedef struct s_ct {
	int		i;
	int		k;
	int		ii;
	int		turn;
	int		test;
	int		rec;
}	t_ct;

typedef struct s_len {
	int		len;
}	t_len;

typedef struct s_all {
	char	*envp_path;
	char	**cmd;
	int		argc;
	int		*fd;
	t_len	len;
	t_ct	ct;
}	t_all;

/********************* Fonctions *********************/

char	*find_good_path(char **paths, char *cmd_path, char *cmd, t_all *all);
char	*check_path(t_all *all, char *cmd, char **envp);
char	*find_path(t_all *all);
void	child(t_all *all, char **argv, char **envp, int *fd);
// void	dady(t_all *all, char **argv, char **envp, int *fd);

/* lib */
char	*ft_substr(char const *src, unsigned int start, size_t len);
char	*ft_strnstr(const char *str, const char *to_find, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *str, int c);
char	**ft_split(char const *s, char c);
char	*ft_strdup(char *src);

void	free_ptr(char **tab);
void	free_all(t_all *all);

char	*get_next_line(int fd);

size_t	ft_strlen(const char *str);

/* Bonus */
// void	multi_pipes(t_all *all, int argc, char **argv, char **envp);
// void	init_var_b(t_all *all, int argc, char **argv, char **envp);

#endif
