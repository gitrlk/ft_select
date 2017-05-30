/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 18:13:26 by jecarol           #+#    #+#             */
/*   Updated: 2017/05/30 15:23:58 by rlkcmptr         ###   ########.fr       */
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
	int					to_sub_w;
	int					to_sub_h;
	int					width;
	int					height;
}						t_term;

#endif
