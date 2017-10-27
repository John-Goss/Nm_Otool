#ifndef OTOOL_H
# define OTOOL_H

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


  # define DBG ft_putstr(__func__); ft_putstr(" in "); \
  ft_putstr(__FILE__); ft_putstr(" at line : "); \
  ft_putnbr(__LINE__); ft_putchar('\n')


# define ERROR(name, errmsg) ft_printf("error: %s: %s\n", name, errmsg); return (1)

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

/*
 * x64 ARCH
 */

void		handle_64(char *ptr, char *name, int should_display_infos);
void		print_output_64(struct section_64 *section, void *ptr, char *name, int should_display_infos);

/*
 * x86 ARCH
 */

void		handle_32(char *ptr, char *name, int should_display_infos);
void		print_output_32(struct section *section, void *ptr, char *name, int should_display_infos);

/*
 * Archive Type
 */

void		handle_dynamic_lib(char *ptr, char *name);
t_offlist	*add_off(t_offlist *lst, uint32_t off, uint32_t strx);
int			catch_size(char *name);
void		browse_ar(t_offlist *lst, char *ptr, char *name);

/*
 * OTHER
 */

int			ft_otool(char *ptr, char *name, int should_display_infos);
int			handle_fat(char *ptr, char *name, int is_little_endian);
uint32_t	swap_uint32(uint32_t val, int is_little_endian);
int			search_duplicate_in_lst(t_offlist *lst, uint32_t off);

#endif
