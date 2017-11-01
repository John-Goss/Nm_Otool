/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:23:54 by jle-quer          #+#    #+#             */
/*   Updated: 2017/11/01 15:11:26 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

static void		symtab_building_bis(t_symtab *symt,
	struct segment_command *seg, struct section *sect)
{
	uint32_t	i;

	i = 0;
	while (i < seg->nsects)
	{
		if (ft_strcmp(sect->sectname, SECT_TEXT) == 0 &&
		ft_strcmp(sect->segname, SEG_TEXT) == 0)
			symt->text = symt->ns;
		else if (ft_strcmp(sect->sectname, SECT_DATA) == 0 &&
		ft_strcmp(sect->segname, SEG_DATA) == 0)
			symt->data = symt->ns;
		else if (ft_strcmp(sect->sectname, SECT_BSS) == 0 &&
		ft_strcmp(sect->segname, SEG_DATA) == 0)
			symt->bss = symt->ns;
		sect = (void *)sect + sizeof(*sect);
		symt->ns++;
		i++;
	}
}

void			symtab_building(t_symtab *symt,
	struct mach_header *header, struct load_command *lc)
{
	uint32_t				i;
	struct segment_command	*seg;
	struct section			*sect;

	i = 0;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
		{
			seg = (struct segment_command *)lc;
			sect = (struct section *)((void *)seg + sizeof(*seg));
			symtab_building_bis(symt, seg, sect);
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}

static void		sort_duplicate_strx_by_value(struct nlist *array,
	char *stringtable, uint32_t size)
{
	struct nlist	tmp;
	int				sorted;
	uint32_t		i;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = 0;
		while (i < size - 1)
		{
			if (ft_strcmp(stringtable + array[i].n_un.n_strx, stringtable +
						array[i + 1].n_un.n_strx) == 0 && array[i].n_value != 0
					&& array[i + 1].n_value != 0)
				if (array[i].n_value > array[i + 1].n_value)
				{
					tmp = array[i + 1];
					array[i + 1] = array[i];
					array[i] = tmp;
					sorted = 0;
				}
			++i;
		}
	}
}

void			print_output(struct symtab_command *sym,
	struct mach_header *header, char *ptr)
{
	uint32_t			i;
	struct load_command	*lc;
	char				*stringtable;
	struct nlist		*array;
	t_symtab			symt;

	symt = init_symtab();
	i = 0;
	lc = (void *)ptr + sizeof(*header);
	array = (void *)ptr + sym->symoff;
	stringtable = (void *)ptr + sym->stroff;
	if (g_bonus_nm == 1)
		array = fill_array(array, sym->nsyms);
	else
		array = bubble_sort(stringtable, array, sym->nsyms);
	sort_duplicate_strx_by_value(array, stringtable, sym->nsyms);
	symtab_building(&symt, header, lc);
	display_loop(array, stringtable, symt, sym);
}

void			handle_32(char *ptr)
{
	int						i;
	int						ncmds;
	struct mach_header		*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	i = -1;
	header = (struct mach_header *)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	while (++i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			print_output(sym, header, ptr);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}
