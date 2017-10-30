/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 12:23:43 by jle-quer          #+#    #+#             */
/*   Updated: 2017/10/30 12:26:05 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/nm.h"

int	ft_nm(void *ptr, char *object)
{
	uint32_t	magic_number;

	magic_number = *(uint32_t *)ptr;
	if (magic_number == MH_MAGIC_64)
		handle_64(ptr);
	else if (magic_number == MH_MAGIC)
		handle_32(ptr);
	else if (ft_strncmp(ptr, ARMAG, SARMAG) == 0)
		handle_dynamic_lib(ptr, object);
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
		handle_fat(ptr, magic_number == FAT_MAGIC ? 1 : 0);
	else
		ERROR(object, "The file was not recognized as a valid object file.");
	return (1);
}

int	main(int ac, char **av)
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
			ERROR(av[1], "fstat - The fildes argument is not a valid file \
					descriptor.");
		}
		if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
				== MAP_FAILED)
		{
			ERROR(av[1], "mmap - MAP_FAILED.");
		}
		ft_nm(ptr, av[1]);
	}
	else
		ERROR(av[1], "No such file or directory.");
	close(fd);
	return (0);
}
