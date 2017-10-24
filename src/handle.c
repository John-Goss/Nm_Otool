#include "../include/nm_tool.h"

void	handle_64(char *ptr)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	int						ncmds;
	int						i;
	
	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	i = -1;
	lc = (void *)ptr + sizeof(*header);
	while (++i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			print_output_64(sym, ptr, header);
			break;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}

void	handle_32(char *ptr)
{
	struct mach_header		*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	int						ncmds;
	int						i;
	
	header = (struct mach_header *)ptr;
	ncmds = header->ncmds;
	i = -1;
	lc = (void *)ptr + sizeof(*header);
	while (++i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			print_output_32(sym, ptr, header);
			break;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}

void	handle_dynamic_lib(char *ptr, char *name)
{
	struct ar_hdr	*arch;
	struct ranlib	*ran;
	t_offlist		*lst;
	char			*test;
	int				i;
	int				size;
	int				name_size;
	
	i = 0;
	arch = (void*)ptr + SARMAG;
	name_size = catch_size(arch->ar_name);
	test = (void*)ptr + sizeof(*arch) + SARMAG + name_size;
	ran = (void*)ptr + sizeof(*arch) + SARMAG + name_size + 4;
	size = *((int *)test);
	lst = NULL;
	size = size / sizeof(struct ranlib);
	while (i < size)
	{
		lst = add_off(lst, ran[i].ran_off, ran[i].ran_un.ran_strx);
		i++;
	}
	browse_ar(lst, ptr, name);
}
