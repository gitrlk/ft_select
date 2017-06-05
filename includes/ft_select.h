/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 18:13:26 by jecarol           #+#    #+#             */
/*   Updated: 2017/06/05 18:22:10 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "../libft/libft.h"
# include <curses.h>
# include <term.h>
# include <stdlib.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <signal.h>

typedef	struct			s_vals
{
	int					col_pos;
	int					lin_pos;
	size_t				max;
	int					curr;
	int					count;
	int					total;
	int					result;
}						t_vals;

t_vals					*g_vals;

typedef	struct			s_args
{
	char				*name;
	size_t				len;
	int					pos;
	int					sel;
	struct s_args		*next;
}						t_args;

t_args					*g_args;

typedef struct			s_term
{
	struct termios		attributes;
	int					to_sub_w;
	int					to_sub_h;
	int					width;
	int					height;
	int					fit;
}						t_term;

t_term					*g_term;

int						g_checker;

void					ft_arrows(t_args *arglist, int buf, t_term *setup,
						t_vals *values);
void					ft_print(t_args *arglist, t_vals *values,
						t_term *setup);
int						ft_pointchar(int c);
void					ft_set_values(t_vals *values, t_args *arglist);
void					ft_signals(void);
void					ft_resize(int i);
void					ft_sigint(int i);
void					ft_sigstp(int i);
void					ft_sigcont(int i);
void					ft_segvwtf(int i);
void					ft_freelist(t_args *lst);
void					ft_set_term(void);
void					ft_getmax(t_args *arglist, t_vals *values);
void					ft_events(t_args **arglist, int buf, t_term *setup,
						t_vals *values);
void					ft_update_pos(t_args *arglist, t_vals *values);
void					ft_end(t_args *arglist, int buf, t_term *setup,
						t_vals *values);
void					ft_select_elem(t_args *arglist, int buf, t_term *setup,
						t_vals *values);
void					ft_del_elem(t_args **arglist, int buf, t_term *setup,
						t_vals *values);
void					ft_init(char *orterm, t_term *setup, t_args *arglist);
void					ft_getargs(t_args **arglist, char *av);

#endif
