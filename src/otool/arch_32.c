/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:29:37 by jle-quer          #+#    #+#             */
/*   Updated: 2017/11/01 17:10:45 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <otool.h>

static void		symtab_building_bis(struct segment_command *seg,
	struct section *sect, struct mach_header *header)
{
	uint32_t	i;

	i = 0;
	while (i < seg->nsects)
	{
		if (g_bonus_otool == 0)
		{
			if (ft_strcmp(sect->sectname, SECT_TEXT) == 0 &&
			ft_strcmp(sect->segname, SEG_TEXT) == 0)
			{
				print_section(sect->addr, sect->size,
					(char *)header + sect->offset,
					"Contents of (__TEXT,__text) section");
			}
		}
		else if (ft_strcmp(sect->sectname, SECT_DATA) == 0 &&
		ft_strcmp(sect->segname, SEG_DATA) == 0)
		{
			print_section(sect->addr, sect->size,
				(char *)header + sect->offset,
				"Contents of (__DATA,__data) section");
		}
		sect = (void *)sect + sizeof(*sect);
		i++;
	}
}

void			symtab_building(struct mach_header *header,
	struct load_command *lc)
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
			symtab_building_bis(seg, sect, header);
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}

static void		sort_duplicate_strx_by_value(struct nlist *array,
	char *stringtable, uint32_t size)
{
	int				sorted;
	struct nlist	tmp;
	uint32_t		i;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = 0;
		while (i < size - 1)
		{
			if (ft_strcmp(stringtable + array[i].n_un.n_strx, stringtable +
						array[i + 1].n_un.n_strx) == 0 && (array[i].n_value != 0
					|| array[i + 1].n_value != 0))
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

	i = 0;
	lc = (void *)ptr + sizeof(*header);
	array = (void *)ptr + sym->symoff;
	stringtable = (void *)ptr + sym->stroff;
	array = bubble_sort(stringtable, array, sym->nsyms);
	sort_duplicate_strx_by_value(array, stringtable, sym->nsyms);
	symtab_building(header, lc);
}

void			handle_32(char *ptr, char *file, int display)
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
			if (display)
				ft_printf("%s:\n", file);
			print_output(sym, header, ptr);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}
