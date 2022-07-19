/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:28:23 by nadesjar          #+#    #+#             */
/*   Updated: 2022/07/19 16:36:47 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*div_cmd(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	ret = ft_calloc(sizeof(char), i + 1);
	if (!str || !ret)
	{
		free(str);
		return (NULL);
	}
	i = -1;
	while (str[++i] != ' ' && str[i] != '\0')
		ret[i] = str[i];
	return (ret);
}

int	main(int argc, char **argv, char **envp)
{
	t_all	all;
	pid_t	pid;
	int		*fd;
	int		i;
	// int		fd_child;
	// int		fd_dady;

	fd = ft_calloc(sizeof(int), 5);
	if (!fd)
	{
		free(fd);
		exit(-1);
	}
	all.argc = argc;
	all.ct.turn = 0;
	all.ct.test = 0;
	all.ct.rec = 0;
	all.ct.ii = argc - 4;

	i = -1;
	if (argc >= 5)
	{
		if (pipe(fd) == -1)
		{
			free(fd);
			free_all(&all);
		}
		all.fd_child = open(argv[1], O_RDONLY, 0644);
		all.fd_dady = open(argv[all.argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (!all.fd_child && !all.fd_dady)
		{
			exit(-1);
		}
		while (++i < argc -3)
		{
			pid = fork();
			if (pid == -1)
				free_all(&all);
			if (pid == 0)
				child(&all, argv, envp, fd);
			
			usleep(1000);
			if (i >= 1)
				all.ct.turn += 2;
			all.ct.ii++;
			all.ct.test++;
		}
		close(all.fd_child);
		close(all.fd_dady);
		free_all(&all);
	}
	else
		exit (-1);
	free(fd);
	return (0);
}

char	*init_path(t_all *all, char *argv, char **envp)
{
	char	*str;
	char	*ret;
	char	*cmd;

	cmd = ft_calloc(sizeof(char), ft_strlen(argv) + 1);
	if (!cmd)
	{
		free(cmd);
		exit(-1);
	}
	// ft_printf("INIT: 01\n");
	str = div_cmd(argv);

	cmd = ft_strdup(str);
	ret = check_path(all, cmd, envp);
	dprintf(2, "str: %s\n", str);
	dprintf(2, "cmd: %s\n", cmd);
	dprintf(2, "ret: %s\n", ret);
	free(cmd);
	return (ret);
}

void	child(t_all *all, char **argv, char **envp, int *fd)
{
	char	**options;
	char	*cmd_path;
	int		error;
	
	cmd_path = init_path(all, argv[all->ct.ii], envp);
	
	options = ft_split(argv[all->ct.ii], ' ');
	int i = -1;
	while (options[++i])
		ft_printf("Options: %s\n", options[i]);
	
	if (all->ct.test == 0)
	{
		dup2(all->fd_child, STDIN_FILENO);
		dup2(fd[all->ct.turn + 1], STDOUT_FILENO);
		close(fd[0]);
		dprintf(2, "1_ct.turn: %d\n", all->ct.turn);
	}
	else if(all->ct.test == all->argc - 4)
	{
		dup2(fd[all->ct.turn], STDIN_FILENO);
		dup2(all->fd_dady, STDOUT_FILENO);
		close(fd[all->ct.turn + 2]);
		dprintf(2, "3_ct.turn: %d\n", all->ct.turn);
	}
	else
	{
		dup2(fd[all->ct.turn], STDIN_FILENO);
		dup2(fd[all->ct.turn + 3], STDOUT_FILENO);
		close(fd[all->ct.turn + 2]);
		dprintf(2, "2_ct.turn: %d\n", all->ct.turn);
	}

	dprintf(2, "RE: \n\n");
	
	error = execve(cmd_path, options, envp);
	if (error == -1)
	{
		free_ptr(options);
		free_all(all);
	}
	free_ptr(options);
}

// void	dady(t_all *all, char **argv, char **envp, int *fd)
// {
// 	int		error;
// 	char	**options;

// 	ft_printf("DAD: 01\n");
// 	all->fd_dady = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (!all->fd_dady)
// 		free_all(all);
// 	options = ft_split(argv[3], ' ');
// 	ft_printf("DAD: 02\n");
// 	dup2(fd[0], STDIN_FILENO);
// 	dup2(all->fd_dady, STDOUT_FILENO);
// 	close(fd[1]);
// 	error = execve(all->cmd_path2, options, envp);
// 	if (error == -1)
// 	{
// 		free_ptr(options);
// 		free_all(all);
// 	}
// 	free_ptr(options);
// 	close(all->fd_dady);
// }

// void child(t_all *all, char **argv, char **envp, int *fd)
// {
// 	char **options;
// 	char *cmd_path;
// 	int fd_child;
// 	int fd_dady;
// 	int error;
// 	// int		i;

// 	all->ct.rec--;
// 	if (all->ct.rec > 0)
// 		child(all, argv, envp, fd);
// 	fd_child = open(argv[1], O_RDONLY, 0644);
// 	fd_dady = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);

// 	cmd_path = init_path(all, argv[all->argc - ++all->ct.ii], envp);

// 	if (!fd_child && !fd_dady)
// 	{
// 		exit(-1);
// 	}
// 	close(fd[all->ct.i_fd]);
// 	options = ft_split(argv[2], ' ');
// 	if (all->ct.rec == 0)
// 		dup2(fd_child, STDIN_FILENO);
// 	else
// 		dup2(fd[all->ct.i_fd + 1], STDIN_FILENO);

// 	if (all->ct.rec == 1)
// 		dup2(fd_dady, STDOUT_FILENO);
// 	else
// 		dup2(fd[all->ct.i_fd + 1], STDOUT_FILENO);
// 	close(fd[all->ct.i_fd]);

// 	dprintf(2, "RE: \n");
// 	all->ct.i_fd += 2;
// 	// if (all->ct.rec > 0)
// 	// 	child(all, argv, envp, fd);

// 	error = execve(cmd_path, options, envp);
// 	if (error == -1)
// 	{
// 		free_ptr(options);
// 		free_all(all);
// 	}
// 	close(fd_child);
// 	close(fd_dady);
// 	free_ptr(options);
// }