/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adefonta <adefonta@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 17:01:33 by adefonta          #+#    #+#             */
/*   Updated: 2019/03/06 15:48:51 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	*error_null(char *error)
{
	ft_putendl_fd(error, 2);
	return (NULL);
}

int		error_int(char *error)
{
	ft_putendl_fd(error, 2);
	return (0);
}

int		error_source_file(char *name)
{
	ft_dprintf(2, "Can't read source file %s\n", name);
	return (0);
}

int		error_header(char *name)
{
	ft_dprintf(2, "Error: File %s has an invalid header\n", name);
	return (0);
}

int		error_size(char *name)
{
	ft_dprintf(2, "Error: File %s has a code size that differ from what \
its header says\n", name);
	return (0);
}
