/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:26:34 by jle-quer          #+#    #+#             */
/*   Updated: 2017/10/31 17:58:02 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

void		set_architecture(unsigned int magic_number)
{
	g_is_big_endian = 0;
	if (magic_number == MH_CIGAM_64 || magic_number == MH_CIGAM
		|| magic_number == FAT_CIGAM)
		g_is_big_endian = 1;
}

char		type_n_sect(unsigned int n_sect, t_symtab *symt)
{
	if (n_sect == symt->text)
		return ('T');
	if (n_sect == symt->data)
		return ('D');
	if (n_sect == symt->bss)
		return ('B');
	return ('S');
}

char		get_type(uint32_t type, uint32_t n_sect, int value,
	t_symtab *symt)
{
	char		c;

	c = type;
	if (c & N_STAB)
		return ('-');
	c = c & N_TYPE;
	if (c == N_UNDF && value != 0)
		c = 'C';
	else if ((c == N_UNDF && value == 0) || c == N_PBUD)
		c = 'U';
	else if (c == N_ABS)
		c = 'A';
	else if (c == N_SECT)
		c = type_n_sect(n_sect, symt);
	else
		c = (c == N_INDR ? 'I' : '?');
	if (!(type & N_EXT))
		c = ft_tolower(c);
	return (c);
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

/*
** p = Don't sort; display in symbol-table order.
** r = Sort in reverse order.
** u = Display only undefined symbols.
** U = Don't display undefined symbols.
** j = Just display the symbol names (no value or type).
*/

void		check_bonus(char *bonus)
{
	if (ft_strcmp(bonus, "-p") == 0)
		g_bonus_nm = 1;
	else if (ft_strcmp(bonus, "-r") == 0)
		g_bonus_nm = 2;
	else if (ft_strcmp(bonus, "-u") == 0)
		g_bonus_nm = 3;
	else if (ft_strcmp(bonus, "-U") == 0)
		g_bonus_nm = 4;
	else if (ft_strcmp(bonus, "-j") == 0)
		g_bonus_nm = 5;
	else if (bonus[0] == '-')
	{
		ft_printf("ft_nm: Unknown command line argument '%s'\n\n", bonus);
		g_bonus_nm = 6;
	}
	else
		g_bonus_nm = 0;
}
