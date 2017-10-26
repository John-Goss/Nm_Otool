#ifndef NM_H
# define NM_H

# include <fcntl.h>
# include <stdio.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <mach-o/ranlib.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <ar.h>
# include "../libft/INCLUDES/libft.h"

/*
 * # define DBG ft_putstr(__func__); ft_putstr(" in "); \
 * ft_putstr(__FILE__); ft_putstr(" at line : "); \
 * ft_putnbr(__LINE__); ft_putchar('\n')
 */

# define ERROR(name, errmsg) ft_printf("nm: %s: %s\n", name, errmsg); return (-1)

typedef struct			s_offlist
{
	uint32_t			off;
	uint32_t			strx;
	struct s_offlist	*next;
}						t_offlist;

typedef struct          s_symbol_value
{
	int data;
	int bss;
	int text;
	int ns;
}                       t_symbol_value;

#endif
