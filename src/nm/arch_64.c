/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:24:38 by jle-quer          #+#    #+#             */
/*   Updated: 2017/11/01 17:10:17 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

static void		symtab_building_bis_64(t_symtab *symt,
	struct segment_command_64 *seg, struct section_64 *sect)
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

void			symtab_building_64(t_symtab *symt,
	struct mach_header_64 *header, struct load_command *lc)
{
	uint32_t					i;
	struct segment_command_64	*seg;
	struct section_64			*sect;

	i = 0;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)lc;
			sect = (struct section_64 *)((void *)seg + sizeof(*seg));
			symtab_building_bis_64(symt, seg, sect);
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}

static void		sort_duplicate_strx_by_value_64(struct nlist_64 *array,
	char *stringtable, uint32_t size)
{
	struct nlist_64	tmp;
	int				sorted;
	uint32_t		i;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = 0;
		while (i < size - 1)
		{
			if (ft_strcmp(stringtable + array[i].n_un.n_strx,
				stringtable + array[i + 1].n_un.n_strx) == 0 &&
				(array[i].n_value != 0 || array[i + 1].n_value != 0))
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

void			print_output_64(struct symtab_command *sym,
	struct mach_header_64 *header, char *ptr)
{
	uint32_t			i;
	struct load_command	*lc;
	char				*stringtable;
	struct nlist_64		*array;
	t_symtab			symt;

	symt = init_symtab();
	i = 0;
	lc = (void *)ptr + sizeof(*header);
	array = (void *)ptr + sym->symoff;
	stringtable = (void *)ptr + sym->stroff;
	if (g_bonus_nm == 1)
		array = fill_array_64(array, sym->nsyms);
	else
		array = bubble_sort_64(stringtable, array, sym->nsyms);
	sort_duplicate_strx_by_value_64(array, stringtable, sym->nsyms);
	symtab_building_64(&symt, header, lc);
	display_loop_64(array, stringtable, symt, sym);
}

void			handle_64(char *ptr)
{
	int						i;
	int						ncmds;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	i = -1;
	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	while (++i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			print_output_64(sym, header, ptr);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}
