#include <otool.h>

void	handle_32(char *ptr, char *name, int should_display_infos)
{
	unsigned int			i;
	struct segment_command	*seg;
	struct section			*sect;
	struct load_command		*lc;
	
	i = 0;
	lc = (void *)ptr + sizeof(struct mach_header);
	while (++i < ((struct mach_header *)ptr)->ncmds)
		if (lc->cmd == LC_SEGMENT)
		{
			seg = (struct segment_command *)lc;
			sect = (void *)seg + sizeof(struct segment_command);
			while (++i < seg->nsects)
			{
				if (!ft_strcmp(sect->sectname, SECT_TEXT))
					return (print_output_32(sect, ptr, name, should_display_infos));
				sect = (void *)sect + sizeof(*sect);
			}
			lc = (void *)lc + lc->cmdsize;
		}
}

void	handle_64(char *ptr, char *name, int should_display_infos)
{
	unsigned int				i;
	unsigned int				j;
	struct segment_command_64	*seg;
	struct section_64			*sect;
	struct load_command			*lc;
	
	i = 0;
	j = 0;
	lc = (void *)ptr + sizeof(struct mach_header_64);
	while (++i < ((struct mach_header_64 *)ptr)->ncmds)
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)lc;
			sect = (void *)seg + sizeof(struct segment_command_64);
			while (j++ < seg->nsects)
			{
				if (!ft_strcmp(sect->sectname, SECT_TEXT))
					return (print_output_64(sect, ptr, name, should_display_infos));
				sect = (void *)sect + sizeof(*sect);
			}
			lc = (void *)lc + lc->cmdsize;
		}
}

int		handle_fat(char *ptr, char *name, int is_little_endian)
{
	struct fat_header		*h;
	struct fat_arch			*arch;
	uint32_t				offset;
	struct mach_header_64	*header;
	size_t					i;
	
	h = (struct fat_header *)ptr;
	arch = (void *)h + sizeof(*h);
	offset = swap_uint32(arch->offset, is_little_endian);
	i = 0;
	while (i < swap_uint32(h->nfat_arch, is_little_endian))
	{
		offset = swap_uint32(arch->offset, is_little_endian);
		header = (void *)ptr + offset;
		if (swap_uint32(arch->cputype, is_little_endian) == CPU_TYPE_X86_64)
			break ;
		arch = (void *)arch + sizeof(*arch);
		i++;
	}
	header = (void *)ptr + offset;
	ft_otool((void *)header, name, 1);
	return (0);
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
	ft_printf("Archive : %s\n", name);
	while (i < size)
	{
		lst = add_off(lst, ran[i].ran_off, ran[i].ran_un.ran_strx);
		i++;
	}
	browse_ar(lst, ptr, name);
}
