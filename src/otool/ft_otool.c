/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 13:06:22 by jle-quer          #+#    #+#             */
/*   Updated: 2017/10/30 13:13:07 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <otool.h>

int	ft_otool(char *ptr, char *name, int should_display_infos)
{
	uint32_t	magic_number;

	magic_number = *(uint32_t *)ptr;
	if (magic_number == MH_MAGIC_64)
		handle_64(ptr, name, should_display_infos);
	else if (magic_number == MH_MAGIC)
		handle_32(ptr, name, should_display_infos);
	else if (ft_strncmp(ptr, ARMAG, SARMAG) == 0)
		handle_dynamic_lib(ptr, name);
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
		handle_fat(ptr, name, (magic_number == FAT_MAGIC));
	else
		ERROR(name, "The file was not recognized as a valid object file.\n");
}

int	main(int ac, char **av)
{
	int			fd;
	void		*ptr;
	struct stat	buf;

	if (ac < 2)
		ERROR(av[0], "at least one file must be specified");
	else if ((fd = open(av[1], O_RDONLY)) != -1)
	{
		if (fstat(fd, &buf) < 0)
			return (ERROR(av[1], "The fildes argument is not a valid FD"));
		if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
				== MAP_FAILED)
			return (ERROR(av[1], "mmap - MAP_FAILED."));
		ft_otool(ptr, av[1], 1);
	}
	else
		return (ERROR(av[1], "No such file or directory."));
	if (munmap(ptr, buf.st_size) < 0)
		return (ERROR(av[1], "Unable to unmap file."));
	close(fd);
	return (0);
}
