/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 15:47:48 by skadogam          #+#    #+#             */
/*   Updated: 2018/08/22 14:05:01 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		ft_eol(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static t_list	*ft_find_fd(t_list **lst, size_t fd)
{
	t_list	*new;
	t_list	*tmp;

	tmp = *lst;
	if (!(*lst)->next && !(*lst)->content)
	{
		(*lst)->content_size = fd;
		return (*lst);
	}
	while (tmp)
	{
		if (tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	new = ft_lstnew(NULL, 0);
	new->content_size = fd;
	ft_lstadd(lst, new);
	*lst = new;
	return (new);
}

static int		ft_read_n_sub(const int fd, char **line, t_list *lo, int eol)
{
	int		ret;
	char	buff[BUFF_SIZE + 1];
	char	*tmp;

	while (eol == -1 && (ret = read(fd, buff, BUFF_SIZE)))
	{
		if (ret < 0)
			return (-1);
		buff[ret] = '\0';
		tmp = lo->content;
		lo->content = tmp ? ft_strjoin(tmp, buff) : ft_strdup(buff);
		ft_strdel(&tmp);
		eol = ft_eol((char*)lo->content);
	}
	if (ret == 0 && (!lo->content || !*((char*)lo->content)))
		return (0);
	else if (eol == -1)
		eol = ft_strlen((char*)lo->content);
	*line = ft_strsub(lo->content, 0, eol);
	tmp = lo->content;
	lo->content = !tmp[eol++] ? ft_strnew(0) :
	ft_strsub(tmp, eol, ft_strlen(&tmp[eol]));
	ft_strdel(&tmp);
	return (1);
}

static void		ft_free_this_shit(t_list **leftover, t_list *curr, t_list *next,
				const int fd)
{
	t_list	*previous;

	previous = *leftover;
	if (curr == *leftover)
	{
		free((*leftover)->content);
		(*leftover)->content = NULL;
		free(*leftover);
		*leftover = NULL;
		*leftover = next;
	}
	else
	{
		while (previous->next && (int)previous->next->content_size != fd)
			previous = previous->next;
		free(curr->content);
		curr->content = NULL;
		free(curr);
		curr = NULL;
		previous->next = next;
	}
}

int				get_next_line(const int fd, char **line)
{
	int				res;
	t_list			*tmp;
	t_list			*next;
	static t_list	*leftover;

	if (fd < 0 || !line || BUFF_SIZE < 1 || read(fd, *line, 0))
		return (-1);
	else if (leftover)
		tmp = ft_find_fd(&leftover, fd);
	else
	{
		leftover = ft_lstnew(NULL, 0);
		leftover->content_size = fd;
		tmp = leftover;
	}
	res = ft_read_n_sub(fd, line, tmp, ft_eol((char*)tmp->content));
	if (res == 1)
		return (1);
	else
	{
		next = tmp->next;
		ft_free_this_shit(&leftover, tmp, next, fd);
		return (res);
	}
}
