#include "../../include/nm.h"

static void    symbol_fill_32(t_symbol_value *symt, struct segment_command *seg, struct section *sect)
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
		++i;
	}
}

static void    symbol_fill_64(t_symbol_value *symt, struct segment_command_64 *seg, struct section_64 *sect)
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
		++i;
	}
}

void    symbol_build_32(t_symbol_value *symt, struct mach_header *header,\
						struct load_command *lc)
{
	struct segment_command	*seg;
	struct section			*sect;
	uint32_t				i;
	
	i = 0;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
		{
			seg = (struct segment_command *)lc;
			sect = (struct section *)((void *)seg + sizeof(*seg));
			symbol_fill_32(symt, seg, sect);
		}
		lc = (void *)lc + lc->cmdsize;
		++i;
	}
}

void    symbol_build_64(t_symbol_value *symt, struct mach_header_64 *header,\
						struct load_command *lc)
{
	struct segment_command_64	*seg;
	struct section_64			*sect;
	uint32_t					i;
	
	i = 0;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)lc;
			sect = (struct section_64 *)((void *)seg + sizeof(*seg));
			symbol_fill_64(symt, seg, sect);
		}
		lc = (void *)lc + lc->cmdsize;
		++i;
	}
}
