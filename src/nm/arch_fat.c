/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_fat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:25:00 by jle-quer          #+#    #+#             */
/*   Updated: 2017/10/31 15:31:01 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

uint32_t		swap_uint32(uint32_t val)
{
	if (!g_is_big_endian)
		return (val);
	return (((val & 0xFF) << 24) | (((val >> 8) & 0xFF) << 16) |
		(((val >> 16) & 0xFF) << 8) | ((val >> 24) & 0xFF));
}

void			handle_fat(char *ptr, char *file)
{
	struct fat_header			*fat_header;
	struct fat_arch				*arch;
	uint32_t							offset;
	struct mach_header_64	*header;
	uint32_t							i;

	fat_header = (struct fat_header *)ptr;
	arch = (void *)fat_header + sizeof(*fat_header);
	offset = swap_uint32(arch->offset);
	i = 0;
	while (i < swap_uint32(fat_header->nfat_arch))
	{
		offset = swap_uint32(arch->offset);
		header = (void *)ptr + offset;
		if (swap_uint32(arch->cputype) == CPU_TYPE_X86_64)
			break ;
		arch = (void *)arch + sizeof(*arch);
		i++;
	}
	header = (void *)ptr + offset;
	return (ft_nm((void *)header, file));
}
