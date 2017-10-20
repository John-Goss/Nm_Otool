#include "../include/nm_tool.h"

void ft_nm(char *ptr)
{
    int	magic_number;
	
    magic_number = *(int *)ptr;
    if (magic_number == MH_MAGIC_64)
        handle_64(ptr);
    if (magic_number == MH_MAGIC)
        handle_32(ptr);
	if (magic_number == MH_DYLIB)
		;//DYLIB
	if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
		;//FAT
}

int main(int ac, char **av)
{
    int			fd;
    void		*ptr;
    struct stat	buf;

    if (ac < 2)
        av[1] = "a.out\0";
    if ((fd = open(av[1], O_RDONLY)) != -1)
    {
        if (fstat(fd, &buf) < 0)
        {
            ERROR(av[1], "fstat - The fildes argument is not a valid file descriptor.");
        }
        if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		{
			ERROR(av[1], "mmap - MAP_FAILED.");
		}
		ft_nm(ptr);
    }
    else
        ERROR(av[1], "No such file or directory.");
    return (0);
}
