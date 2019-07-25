/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adefonta <adefonta@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 01:06:51 by adefonta          #+#    #+#             */
/*   Updated: 2019/07/13 13:06:17 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "visu.h"
#include "macro.h"
#include "visu_macro.h"

/*
** header formatting:
** - COREWAR_EXEC_MAGIC (4 bytes)
** - name (PROG_NAME_LENGTH)
** - separator (4 bytes)
** - program weight (4 bytes)
** - comment (COMMENT_LENGTH)
** - separator (4 bytes)
*/

static int		check_exec_magic(char *buff, int magic)
{
	int				i;

	i = 4;
	while (i--)
	{
		if ((unsigned char)buff[i] != (magic & 0b11111111))
			return (KO);
		magic >>= 8;
	}
	return (OK);
}

static int		get_info(t_champi *champi, char *buff)
{
	int		i;
	int		len;

	i = -1;
	len = 0;
	buff += sizeof(COREWAR_EXEC_MAGIC);
	while (ft_isprint(buff[++i]))
		len++;
	if (len > PROG_NAME_LENGTH || !(champi->name = ft_strsub(buff, 0, len)))
		return (KO);
	i = -1;
	len = 0;
	buff += PROG_NAME_LENGTH + 4;
	champi->weight = arg_read((unsigned char *)buff, 0, 4);
	buff += sizeof(champi->weight);
	while (ft_isprint(buff[++i]))
		len++;
	if (len > COMMENT_LENGTH || !(champi->cmt = ft_strsub(buff, 0, len)))
		return (KO);
	buff += COMMENT_LENGTH;
	return (OK);
}

static int		read_comment(t_champi *champi, int fd, char *curr_av)
{
	int		ret;
	char	buff[PROG_NAME_LENGTH + COMMENT_LENGTH + 16];

	if ((ret = read(fd, buff, HEADER_LENGTH)) < 0)
		return (error_source_file(curr_av));
	if (ret != HEADER_LENGTH
		|| check_exec_magic(buff, COREWAR_EXEC_MAGIC) == KO
		|| get_info(champi, buff) == KO)
		return (error_header(curr_av));
	return (OK);
}

static int		champi_getone(t_champi *champi, t_list **champi_lst, int fd,
	char *curr_av)
{
	int				ret;
	unsigned char	buff[CHAMP_MAX_SIZE + 1];
	t_list			*tmp;

	if (read_comment(champi, fd, curr_av) == KO)
		return (KO);
	if ((ret = read(fd, buff, CHAMP_MAX_SIZE + 1)) < 0)
		return (error_source_file(curr_av));
	if (!ret)
		return (error_int(ERROR_CHAMPI_EMPTY));
	if (ret != champi->weight)
		return (error_size(curr_av));
	if (champi->weight > CHAMP_MAX_SIZE)
		return (error_int(ERROR_CHAMPI_TOOBIG));
	if (!(tmp = ft_lstnew(buff, ret)))
		return (error_int(ERROR_MALLOC));
	ft_lstaddback(champi_lst, tmp);
	return (OK);
}

int				parse_champi(t_vm *vm, int ac, char **av, t_list **champi_lst)
{
	int				i;
	int				fd;
	long			number;
	t_champi		*champi;

	i = -1;
	number = NB_OK;
	while (++i + 1 < ac)
	{
		if ((number = flags_get(vm, ac, av, &i)) == NB_KO)
			return (vm_usage());
		if (i + 1 >= ac)
			break ;
		if ((fd = open(av[i + 1], O_RDONLY)) < 0)
			return (error_source_file(av[i + 1]));
		if (!(champi = champi_init(vm, vm->nb_champi, number)))
			return (KO);
		if (!(champi_getone(champi, champi_lst, fd, av[i + 1])))
			return (KO);
		close(fd);
	}
	sort_champi_by_number(vm, champi_lst);
	if (!pc_init_all(vm, champi_lst))
		return (KO);
	return (OK);
}
