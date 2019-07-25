/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adefonta <adefonta@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:25:04 by adefonta          #+#    #+#             */
/*   Updated: 2019/03/12 10:31:13 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

#ifndef MACRO_H
# define MACRO_H

# define OK						1
# define KO						0
# define NB_OK					LONG_MAX
# define NB_KO					LONG_MIN

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_PLAYERS			6
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16
# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10
# define NB_REGISTRE			16

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3
# define HEADER_LENGTH			(2192)

# define F_V8 "Process %d is dead. (CTD %d)\n"
# define F_V2 "Cycle to die is now %d\n"

/*
** ERRORS
*/

# define ERROR_CHAMPI_NULL "ERROR_CHAMPI_NULL"
# define ERROR_CHAMPI_EMPTY "The champion has no code"
# define ERROR_CHAMPI_TOOBIG "The champion is too fat"
# define ERROR_CHAMPI_TOOMANY "Too many champions"
# define ERROR_PC_NULL "ERROR_PC_NULL"
# define ERROR_MALLOC "Error: malloc() failed to allocate memory"
# define ERROR_VISU "Error: a failure occured in the GUI"

#endif
