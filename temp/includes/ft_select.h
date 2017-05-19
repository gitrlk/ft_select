/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 18:13:26 by jecarol           #+#    #+#             */
/*   Updated: 2017/05/19 22:25:04 by jecarol          ###   ########.fr       */
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
	size_t				max;
	size_t				cmp1;
	size_t				cmp2;
}						t_vals;

typedef struct			s_term
{
	struct termios		attributes;
	int					width;
	int					to_sub;
	int					height;
}						t_term;

#endif
