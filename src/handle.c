#include "../include/nm_tool.h"

void handle_64(char *ptr)
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

void handle_32(char *ptr)
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
