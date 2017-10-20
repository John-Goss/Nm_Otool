#include "../include/nm_tool.h"

void nm(char *ptr)
{
    int	magic_number;
	
    magic_number = *(int *)ptr;
    if (magic_number == MH_MAGIC_64)
        handle_64(ptr);
    if (magic_number == MH_MAGIC)
        handle_32(ptr);
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
            ERROR("");
        }
        if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		{
			ERROR("ok");
		}
		nm(ptr);
    }
    else
        ERROR(av[1]);
    return (0);
}
