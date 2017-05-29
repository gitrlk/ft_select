/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 18:13:26 by jecarol           #+#    #+#             */
/*   Updated: 2017/05/27 19:25:12 by rlkcmptr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <curses.h>
# include <term.h>
# include <stdlib.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <sys/ioctl.h>

typedef	struct			s_vals
{
	int					col_pos;
	int					lin_pos;
	size_t				max;
	int					curr;
	int					count;
}						t_vals;

typedef	struct			s_args
{
	char				*name;
	size_t				len;
	int					pos;
	int					sel;
	struct s_args		*next;
}						t_args;

typedef struct			s_term
{
	struct termios		attributes;
	int					width;
	int					to_sub;
	int					height;
}						t_term;

#endif
