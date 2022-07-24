/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:28:23 by nadesjar          #+#    #+#             */
/*   Updated: 2022/07/22 11:18:43 by nadesjar         ###   ########.fr       */
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
	// int		i;
	int		exit_code;
	
	init_var(&all, argc);

	// i = -1;
	if (argc >= 5)
	{
		exit_code = pipex(&all, argv, envp);
	}
	else
	{
		free(all.fd);
		free(all.pid);
		free(all.pipe);
		exit (-1);
	}
	free(all.pid);
	free(all.pipe);
	free(all.fd);
	return (exit_code);
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



int	dady(t_all *all)
{
	pid_t	wait_pid;
	int		status;
	int		nbr;
	int		ret;

	ret = 1;
	nbr = all->nbr_cmd;
	ft_printf("DAD: 01\n");
	while(nbr > 0)
	{
		wait_pid = waitpid(all->pid[nbr], &status, 0);
		if (wait_pid == -1)
			ret = 0;
		nbr--;
	}
	ft_printf("DAD: 02\n");
	return (ret);
}

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