#include "../../include/nm.h"

void	display_out_32(uint32_t value, char *str, char type)
{
	if (type != 'U' && type != 'u')
		ft_printf("%016llx ", value);
	else
		ft_putstr("                 ");
	ft_printf("%c ", type);
	ft_printf("%s\n", str);
}

void	display_out_64(uint64_t value, char *str, char type)
{
	if (type != 'U' && type != 'u')
		ft_printf("%016llx ", value);
	else
		ft_putstr("                 ");
	ft_printf("%c ", type);
	ft_printf("%s\n", str);
}

void	print_output_32(struct symtab_command *sym, char *ptr, struct mach_header *header)
{
	struct load_command	*lc;
	char				*stringtable;
	struct nlist		*array;
	uint32_t			i;
	t_symbol_value		symt = {0, 0, 0, 1};
	
	i = 0;
	array = (void *)ptr + sym->symoff;
	stringtable = (void *)ptr + sym->stroff;
	lc = (void *)ptr + sizeof(*header);
	array = bubble_sort_nlist_32(stringtable, array, sym->nsyms);
	sort_duplicate_strx_by_value_32(array, stringtable, sym->nsyms);
	symbol_build_32(&symt, header, lc);
	while (i < sym->nsyms)
	{
		display_out_32(array[i].n_value, stringtable + \
					array[i].n_un.n_strx, type_element_32(array[i], symt));
		++i;
	}
}

void	print_output_64(struct symtab_command *sym, char *ptr, struct mach_header_64 *header)
{
	struct load_command	*lc;
	char				*stringtable;
	struct nlist_64		*array;
	uint32_t			i;
	t_symbol_value		symt = {0, 0, 0, 1};
	
	i = 0;
	array = (void *)ptr + sym->symoff;
	stringtable = (void *)ptr + sym->stroff;
	lc = (void *)ptr + sizeof(*header);
	array = bubble_sort_nlist_64(stringtable, array, sym->nsyms);
	sort_duplicate_strx_by_value_64(array, stringtable, sym->nsyms);
	symbol_build_64(&symt, header, lc);
	while (i < sym->nsyms)
	{
		display_out_64(array[i].n_value, stringtable + \
					array[i].n_un.n_strx, type_element_64(array[i], symt));
		++i;
	}
}
