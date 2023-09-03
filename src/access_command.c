/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 20:23:33 by jholl             #+#    #+#             */
/*   Updated: 2021/10/22 17:23:43 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_env_path_line(char *env)
{
	int	i;

	i = 0;
	if (ft_strlen(env) >= 5)
	{
		if (env[0] == 'P' && env[1] == 'A' && env[2] == 'T' && env[3] == 'H'
			&& env[4] == '=')
			return (1);
		else
			return (0);
	}
	return (0);
}

char	*lf_path_in_env(char **envp)
{
	int	i;
	int	stop;

	i = 0;
	stop = 0;
	while (envp[i] && !stop)
	{
		if (is_env_path_line(envp[i]) == 1)
			stop = 1;
		else
			i++;
	}
	if (envp[i])
		return (envp[i]);
	return (NULL);
}

char	*try_access_path(t_data *data, char **av, int ac_com)
{
	int		i;
	char	*test_path;
	char	*path;

	data->command_split = ft_split(av[ac_com], ' ');
	if (!data->command_split)
		exit_error(data, "ft_strjoin function failed: ");
	if (access(data->command_split[0], X_OK) == 0)
		return (data->command_split[0]);
	i = 0;
	while (data->path_split[i])
	{
		path = ft_strjoin(data->path_split[i], "/");
		if (!path)
			exit_error(data, "ft_strjoin function failed: ");
		test_path = ft_strjoin(path, data->command_split[0]);
		free_str(&path);
		if (!test_path)
			exit_error(data, "ft_strjoin function failed: ");
		if (access(test_path, X_OK) == 0)
			return (test_path);
		free_str(&test_path);
		i++;
	}
	return (NULL);
}

void	access_command(t_data *data, char **av, char **envp, int ac_com)
{
	char	*path_env;

	path_env = lf_path_in_env(envp);
	if (!path_env)
		exit_error(data, "$PATH not found in env.");
	data->path_split = ft_split(path_env + 5, ':');
	if (!data->path_split)
		exit_error(data, "ft_split function failed: ");
	data->path = try_access_path(data, av, ac_com);
	if (!data->path)
		exit_error_no_err(data, data->command_split[0], ": command not found");
	if (data->path_split)
		free_double_str(&data->path_split);
}
