/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setupf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 15:15:38 by jecarol           #+#    #+#             */
/*   Updated: 2017/05/19 21:29:35 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "ft_select.h"
//
// void					ft_freelist(t_args *lst)
// {
// 	t_args				*tmp;
//
// 	tmp = lst;
// 	if (!tmp)
// 		return ;
// 	while (lst)
// 	{
// 		tmp = lst;
// 		lst = lst->next;
// 		ft_strdel(&tmp->name);
// 		free(tmp);
// 	}
// }
//
// t_args					*ft_addarg(char *av)
// {
// 	t_args				*tmp;
//
// 	if (!(tmp = ft_memalloc(sizeof(t_args))))
// 		return (NULL);
// 	tmp->next = NULL;
// 	if (!av)
// 		tmp->name = NULL;
// 	else
// 		tmp->name = ft_strdup(av);
// 	return (tmp);
// }
//
// void					ft_getargs(t_args **arglist, char *av)
// {
// 	t_args				*tmp;
//
// 	tmp = *arglist;
// 	if (!tmp)
// 		*arglist = ft_addarg(av);
// 	else
// 	{
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = ft_addarg(av);
// 	}
// }
