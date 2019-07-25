/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_v2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <skadogam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 11:45:03 by skadogam          #+#    #+#             */
/*   Updated: 2019/02/26 12:18:13 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		eol(t_line *leftover, t_dlist *buff)
{
	char	*s;

	if (!leftover || !buff)
		return (0);
	leftover->eol = 0;
	s = (char*)buff->content + leftover->save;
	if (!*s)
	{
		ft_dlstdelone(&leftover->buff);
		leftover->save = 0;
		buff = leftover->buff;
		if (!buff || !(s = (char*)buff->content))
			return (0);
	}
	while (*s)
	{
		if (*s++ == '\n')
			return (1);
		leftover->eol += 1;
		if (!*s && buff->next != leftover->buff && (buff = buff->next))
			s = (char*)buff->content;
	}
	return (0);
}

static int		save_line(char **line, t_line *leftover)
{
	char	*s;
	char	*tmp;

	if (!(*line = ft_strnew(leftover->eol + 1)))
		return (0);
	s = (char*)leftover->buff->content + leftover->save;
	tmp = *line;
	while (leftover->eol)
	{
		*tmp++ = *s++;
		leftover->save += 1;
		leftover->eol -= 1;
		if (!*s)
		{
			ft_dlstdelone(&leftover->buff);
			leftover->save = 0;
			if (leftover->buff)
				s = (char*)leftover->buff->content;
		}
	}
	if (*s == '\n')
		leftover->save += 1;
	return (1);
}

static int		read_n_save(const int fd, char **line, t_line *leftover,
				int print)
{
	int		ret;
	char	buff[BUFF_SIZE];
	t_dlist	*new;

	ret = 0;
	while (!eol(leftover, leftover->buff)
			&& (ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		new = ft_dlstnew();
		new->content = ft_strnew(ret);
		ft_memcpy(new->content, buff, ret);
		ft_dlstaddback(&leftover->buff, new);
		if (print)
			write(1, buff, ret);
	}
	if (ret == -1 || (ret == 0 && !leftover->buff))
		return (ret);
	if (!save_line(line, leftover))
		return (-1);
	return (1);
}

static t_line	*find_fd(t_line **leftover, const int fd)
{
	t_line	*tmp;

	tmp = *leftover;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = (t_line*)malloc(sizeof(*tmp));
	tmp->fd = fd;
	tmp->buff = NULL;
	tmp->eol = 0;
	tmp->save = 0;
	tmp->prev = NULL;
	tmp->next = *leftover;
	*leftover = tmp;
	return (tmp);
}

int				get_next_line_v2(const int fd, char **line, int print)
{
	int				res;
	t_line			*curr_fd;
	static t_line	*leftover;

	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	curr_fd = find_fd(&leftover, fd);
	if ((res = read_n_save(fd, line, curr_fd, print)) != 1)
	{
		if (curr_fd->prev)
			curr_fd->prev->next = curr_fd->next;
		if (curr_fd->next)
			curr_fd->next->prev = curr_fd->prev;
		if (curr_fd == leftover)
			leftover = leftover->next;
		ft_dlstdel(&curr_fd->buff);
		free(curr_fd);
		curr_fd = NULL;
	}
	return (res);
}
