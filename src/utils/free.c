/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 21:14:27 by jholl             #+#    #+#             */
/*   Updated: 2021/10/22 18:58:56 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_str(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

void	free_double_str(char ***str)
{
	int		i;
	char	**str_to_free;

	str_to_free = *str;
	if (!str_to_free)
		return ;
	i = 0;
	while (str_to_free[i])
	{
		free_str(&str_to_free[i]);
		i++;
	}
	free(str_to_free);
	*str = NULL;
}
