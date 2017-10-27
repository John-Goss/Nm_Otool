#include <otool.h>

void		print_output_32(struct section *section, void *ptr, char *name, int should_display_infos)
{
	unsigned char	*p;
	unsigned int	i;
	int				j;
	
	if (should_display_infos)
		ft_printf("%s:\nContents of (%s,%s) section\n", name, section->segname,
			  section->sectname);
	else
		ft_printf("Contents of (%s,%s) section\n", section->segname,
				  section->sectname);
	p = (void *)ptr + section->offset;
	i = 0;
	while (i < section->size)
	{
		ft_printf("%08llx", (unsigned long long)section->addr + i);
		ft_printf("\t");
		j = 17;
		while (i < section->size && --j)
			ft_printf("%02hhx ", p[i++]);
		ft_printf("\n");
	}
}

void		print_output_64(struct section_64 *section, void *ptr, char *name, int should_display_infos)
{
	unsigned char	*p;
	unsigned int	i;
	int				j;
	
	if (should_display_infos)
		ft_printf("%s:\nContents of (%s,%s) section\n", name, section->segname,
				  section->sectname);
	else
		ft_printf("Contents of (%s,%s) section\n", section->segname,
				  section->sectname);
	p = (void *)ptr + section->offset;
	i = 0;
	while (i < section->size)
	{
		ft_printf("%016llx", (unsigned long long)section->addr + i);
		ft_printf("\t");
		j = 17;
		while (i < section->size && --j)
			ft_printf("%02hhx ", p[i++]);
		ft_printf("\n");
	}
}

uint32_t	swap_uint32(uint32_t val, int is_little_endian)
{
	if (is_little_endian)
		return (val);
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return (val << 16) | (val >> 16);
}
