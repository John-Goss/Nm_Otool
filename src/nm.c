#include <stdio.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "./libft/INCLUDES/libft.h"

void	print_output(int nsyms, int symoff, int stroff, char *ptr)
{
	int				i;
	char			*stringtable;
	struct nlist_64	*array;

	array = (void *)ptr + symoff;
	stringtable = (void *)ptr + stroff;
	for (i = 0; i < nsyms; ++i)
	{
		ft_printf("%s\n", stringtable + array[i].n_un.n_strx);
	}
}

void	handle_64(char *ptr)
{
	int						i;
	int						ncmds;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	i = 0;
	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	for (i = 0; i < ncmds; ++i)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *) lc;
			print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
			break;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}

void	nm(char *ptr)
{
	int	magic_number;

	// First 4 Bytes in Little Endian (reverse)
	magic_number = *(int *) ptr;
	if (magic_number == MH_MAGIC_64)
	{
		handle_64(ptr);
	}
}

int	main(int ac, char **av)
{
	int			fd;
	char		*ptr;
	struct stat	buf;

	if (ac < 2)
		return (1);
	if ((fd = open (av[1], O_RDONLY)) < 0)
		return (1);
	if (fstat(fd, &buf) < 0)
		return (1);
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (1);
	nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
		return (1);
	close(fd);
	return (0);
}
