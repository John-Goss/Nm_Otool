/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:31:39 by jle-quer          #+#    #+#             */
/*   Updated: 2017/10/30 14:31:46 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <otool.h>

void		set_architecture(unsigned int magic_number)
{
	g_is_big_endian = 0;
	if (magic_number == MH_CIGAM_64 || magic_number == MH_CIGAM
		|| magic_number == FAT_CIGAM)
		g_is_big_endian = 1;
}

int			search_lst(t_offlist *lst, uint32_t off)
{
	t_offlist	*cur;

	cur = lst;
	while (cur)
	{
		if (cur->off == off)
			return (1);
		cur = cur->next;
	}
	return (0);
}
