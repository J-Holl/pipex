/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 22:27:53 by jholl             #+#    #+#             */
/*   Updated: 2021/10/22 19:03:20 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_command(t_data *data, char **av, char **envp)
{
	int	new_fd;

	close(data->fd_pipe[0]);
	new_fd = open(av[1], O_RDONLY);
	if (new_fd < 0)
		exit_error_str(data, av[1]);
	access_command(data, av, envp, 2);
	dup2(new_fd, STDIN_FILENO);
	dup2(data->fd_pipe[1], STDOUT_FILENO);
	close(data->fd_pipe[1]);
	close(new_fd);
	if (execve(data->path, data->command_split, envp) < 0)
		exit_error(data, "execve function failed:");
}

void	second_command(t_data *data, char **av, char **envp)
{
	int	new_fd;

	close(data->fd_pipe[1]);
	new_fd = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (new_fd < 0)
		exit_error_str(data, av[4]);
	access_command(data, av, envp, 3);
	dup2(data->fd_pipe[0], STDIN_FILENO);
	close(data->fd_pipe[0]);
	dup2(new_fd, STDOUT_FILENO);
	close(new_fd);
	if (execve(data->path, data->command_split, envp) < 0)
		exit_error(data, "execve function failed:");
}

int	end_program(t_data *data, int pid, int pid1)
{
	int		w_statu;

	close(data->fd_pipe[1]);
	close(data->fd_pipe[0]);
	w_statu = 0;
	if (waitpid(pid, &w_statu, 0) < 0)
		exit_error(data, "waitpid function failed:");
	if (waitpid(pid1, &w_statu, 0) < 0)
		exit_error(data, "waitpid function failed:");
	free_before_leave(data);
	if (w_statu)
		return (WEXITSTATUS(w_statu));
	if (errno)
		return (errno);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	int		pid;
	int		pid1;
	t_data	data;

	init_data(&data);
	if (ac != 5)
		exit_error(&data, "format is 5 args: ./pipex file1 cmd1 cmd2 file2");
	if (pipe(data.fd_pipe) == -1)
		exit_error(&data, "pipe function failed:");
	pid = fork();
	if (pid < 0)
		exit_error(&data, "fork function failed:");
	if (!pid)
		first_command(&data, av, envp);
	pid1 = fork();
	if (pid1 < 0)
		exit_error(&data, "fork function failed:");
	if (!pid1)
		second_command(&data, av, envp);
	return (end_program(&data, pid, pid1));
}
