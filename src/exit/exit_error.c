/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 21:41:05 by jholl             #+#    #+#             */
/*   Updated: 2021/10/22 18:22:51 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_error(t_data *data, char *str)
{
	if (data->command_split)
		free_double_str(&data->command_split);
	if (data->path_split)
		free_double_str(&data->path_split);
	if (data->path)
		free_str(&data->path);
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(str, 2);
	if (errno)
		perror(NULL);
	if (errno)
		exit(errno);
	exit(1);
}

void	exit_error_str(t_data *data, char *str)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	if (errno)
		perror(NULL);
	if (data->command_split)
		free_double_str(&data->command_split);
	if (data->path_split)
		free_double_str(&data->path_split);
	if (data->path)
		free_str(&data->path);
	if (errno)
		exit(errno);
	exit(1);
}

void	exit_error_no_err(t_data *data, char *str, char *str1)
{
	ft_putstr_fd(str, 2);
	if (str1)
		ft_putstr_fd(str1, 2);
	ft_putstr_fd("\n", 2);
	if (data->command_split)
		free_double_str(&data->command_split);
	if (data->path_split)
		free_double_str(&data->path_split);
	if (data->path)
		free_str(&data->path);
	exit(127);
}

void	free_before_leave(t_data *data)
{
	if (data->command_split)
		free_double_str(&data->command_split);
	if (data->path_split)
		free_double_str(&data->path_split);
	if (data->path)
		free_str(&data->path);
}
