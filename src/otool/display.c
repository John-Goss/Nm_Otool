/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:30:56 by jle-quer          #+#    #+#             */
/*   Updated: 2017/10/31 15:31:57 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <otool.h>

void			print_section(long unsigned int addr, unsigned int size,
		char *ptr, char *section)
{
	unsigned int	i;
	char			*str;

	i = 0;
	ft_printf("%s\n", section);
	while (i < size)
	{
		if (i == 0 || i % 16 == 0)
		{
			if (i != 0)
				addr += 16;
			ft_printf("%08llx\t", addr);
		}
		str = ft_itoa_base_sub(ptr[i], 16, 2);
		str = ft_strsub(str, ft_strlen(str) - 2, 2);
		ft_printf("%s ", str ? str : "00");
		free(str);
		if ((i + 1) % 16 == 0 && i + 1 < size)
			write(1, "\n", 1);
		i++;
	}
	write(1, "\n", 1);
}

void			print_section_64(long unsigned int addr, unsigned int size,
	char *ptr, char *section)
{
	unsigned int	i;
	char			*str;

	i = 0;
	ft_printf("%s\n", section);
	while (i < size)
	{
		if (i == 0 || i % 16 == 0)
		{
			if (i != 0)
				addr += 16;
			ft_printf("%016llx\t", addr);
		}
		str = ft_itoa_base_sub(ptr[i], 16, 2);
		str = ft_strsub(str, ft_strlen(str) - 2, 2);
		ft_printf("%s ", str ? str : "00");
		free(str);
		if ((i + 1) % 16 == 0 && i + 1 < size)
			write(1, "\n", 1);
		i++;
	}
	write(1, "\n", 1);
}
