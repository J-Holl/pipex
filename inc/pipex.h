/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 21:17:58 by jholl             #+#    #+#             */
/*   Updated: 2021/10/22 17:07:20 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_data
{
	int		fd_pipe[2];
	char	**command_split;
	char	**path_split;
	char	*path;

}				t_data;

//utils
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	free_double_str(char ***str);
void	free_str(char **str);
void	free_before_leave(t_data *data);
void	ft_putstr_fd(char *s, int fd);

//exit
void	exit_error(t_data *data, char *str);
void	exit_error_str(t_data *data, char *str);
void	exit_error_no_err(t_data *data, char *str, char *str1);

//init
void	init_data(t_data *data);

//pipex
void	access_command(t_data *data, char **av, char **envp, int ac_com);

#endif
