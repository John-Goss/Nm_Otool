/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 12:59:32 by jle-quer          #+#    #+#             */
/*   Updated: 2017/10/30 13:03:23 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <otool.h>

static char	*catch_name(char *name)
{
	size_t	length;

	length = ft_strlen(ARFMAG);
	return (ft_strstr(name, ARFMAG) + length);
}

static void	print_ar(uint32_t off, char *ptr, char *file)
{
	int				size_fuck;
	struct ar_hdr	*arch;
	char			*name;

	arch = (void*)ptr + off;
	name = catch_name(arch->ar_name);
	size_fuck = catch_size(arch->ar_name);
	ft_printf("%s(%s):\n", file, name);
	ft_otool((void*)arch + sizeof(*arch) + size_fuck, file, 0);
}

int			search_duplicate_in_lst(t_offlist *lst, uint32_t off)
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

t_offlist	*add_off(t_offlist *lst, uint32_t off, uint32_t strx)
{
	t_offlist	*tmp;
	t_offlist	*tmp2;

	tmp = (t_offlist*)malloc(sizeof(t_offlist));
	tmp->off = off;
	tmp->strx = strx;
	tmp->next = NULL;
	if (!lst)
		return (tmp);
	tmp2 = lst;
	while (tmp2->next)
		tmp2 = tmp2->next;
	if (search_duplicate_in_lst(lst, off))
		return (lst);
	tmp2->next = tmp;
	return (lst);
}

void		browse_ar(t_offlist *lst, char *ptr, char *name)
{
	t_offlist	*tmp;

	tmp = lst;
	while (tmp)
	{
		print_ar(tmp->off, ptr, name);
		tmp = tmp->next;
	}
}
