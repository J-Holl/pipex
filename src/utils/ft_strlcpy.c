/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 23:07:06 by jholl             #+#    #+#             */
/*   Updated: 2021/10/12 22:20:24 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (!dst || !src)
		return (0);
	i = 0;
	while (src[i] && (i + 1) < size)
	{
		dst[i] = src[i];
		i++;
	}
	if (size)
		dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}
