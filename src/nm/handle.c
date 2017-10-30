/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 12:26:15 by jle-quer          #+#    #+#             */
/*   Updated: 2017/10/30 12:33:40 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/nm.h"

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
			break ;
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
			break ;
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
	int				cout[3];

	cout[0] = 0;
	arch = (void*)ptr + SARMAG;
	cout[1] = catch_size(arch->ar_name);
	test = (void*)ptr + sizeof(*arch) + SARMAG + cout[1];
	ran = (void*)ptr + sizeof(*arch) + SARMAG + cout[1] + 4;
	cout[2] = *((int *)test);
	lst = NULL;
	cout[2] = cout[2] / sizeof(struct ranlib);
	while (cout[0] < cout[2])
	{
		lst = add_off(lst, ran[cout[0]].ran_off, ran[cout[0]].ran_un.ran_strx);
		cout[0]++;
	}
	browse_ar(lst, ptr, name);
}

void	handle_fat(char *ptr, int is_little_endian)
{
	struct fat_header	*fat;
	struct fat_arch		*arch;
	uint32_t			x;
	uint32_t			offset;

	offset = 0;
	fat = (void*)ptr;
	x = swap_uint32(fat->nfat_arch, is_little_endian);
	arch = (void*)ptr + sizeof(fat);
	while (x)
	{
		if (swap_uint32(arch->cputype, is_little_endian) == CPU_TYPE_X86_64)
			offset = arch->offset;
		arch += sizeof(arch) / sizeof(void*);
		x--;
	}
	ft_nm(ptr + swap_uint32(offset, is_little_endian), NULL);
}
