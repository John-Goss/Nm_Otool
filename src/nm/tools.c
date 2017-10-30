/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 12:09:18 by jle-quer          #+#    #+#             */
/*   Updated: 2017/10/30 12:45:36 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/nm.h"

uint32_t		swap_uint32(uint32_t val, int is_little_endian)
{
	if (is_little_endian)
		return (val);
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return (val << 16) | (val >> 16);
}

int				search_duplicate_in_lst(t_offlist *lst, uint32_t off)
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

t_symbol_value	init_symtab(void)
{
	t_symbol_value	symt;

	symt.data = 0;
	symt.bss = 0;
	symt.text = 0;
	symt.ns = 1;
	return (symt);
}

void			sort_duplicate_strx_by_value_32(struct nlist *array,
		char *stringtable, uint32_t size)
{
	uint32_t		tmp_value;
	int				sorted;
	uint32_t		increment;

	sorted = 0;
	tmp_value = 0;
	increment = 0;
	while (!sorted)
	{
		sorted = 1;
		increment = 0;
		while (increment < size - 1)
		{
			if (ft_strcmp(stringtable + array[increment].n_un.n_strx,
						stringtable + array[increment + 1].n_un.n_strx) == 0)
				if (array[increment].n_value > array[increment + 1].n_value)
				{
					tmp_value = array[increment + 1].n_value;
					array[increment + 1].n_value = array[increment].n_value;
					array[increment].n_value = tmp_value;
					sorted = 0;
				}
			++increment;
		}
	}
}

void			sort_duplicate_strx_by_value_64(struct nlist_64 *array,
		char *stringtable, uint32_t size)
{
	uint64_t	tmp_value;
	int			sorted;
	uint32_t	increment;

	sorted = 0;
	tmp_value = 0;
	increment = 0;
	while (!sorted)
	{
		sorted = 1;
		increment = 0;
		while (increment < size - 1)
		{
			if (ft_strcmp(stringtable + array[increment].n_un.n_strx,
						stringtable + array[increment + 1].n_un.n_strx) == 0)
				if (array[increment].n_value > array[increment + 1].n_value)
				{
					tmp_value = array[increment + 1].n_value;
					array[increment + 1].n_value = array[increment].n_value;
					array[increment].n_value = tmp_value;
					sorted = 0;
				}
			++increment;
		}
	}
}
