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

# define ERROR(name, errmsg) ft_printf("nm: %s: %s\n", name, errmsg); return (1)

typedef struct			s_offlist
{
	uint32_t			off;
	uint32_t			strx;
	struct s_offlist	*next;
}						t_offlist;

typedef struct          s_symbol_value
{
    uint32_t	data;
    uint32_t	bss;
    uint32_t	text;
    int			ns;
}                       t_symbol_value;

/*
 * x64 ARCH
*/
 
struct nlist_64		*bubble_sort_nlist_64(char *stringtable, struct nlist_64 *tab, int taille);
void				sort_duplicate_strx_by_value_64(struct nlist_64 *array, char *stringtable, uint32_t size);
void				symbol_build_64(t_symbol_value *symt, struct mach_header_64 *header, struct load_command *lc);
void				handle_64(char *ptr);
void				print_output_64(struct symtab_command *sym, char *ptr, struct mach_header_64 *header);
char				type_element_64(struct nlist_64 list, t_symbol_value symt);

/*
 * x86 ARCH
*/

struct nlist		*bubble_sort_nlist_32(char *stringtable, struct nlist *tab, int taille);
void				sort_duplicate_strx_by_value_32(struct nlist *array, char *stringtable, uint32_t size);
void				symbol_build_32(t_symbol_value *symt, struct mach_header *header, struct load_command *lc);
void				handle_32(char *ptr);
void				print_output_32(struct symtab_command *sym, char *ptr, struct mach_header *header);
char				type_element_32(struct nlist list, t_symbol_value symt);

/*
 * Archive Type
 */

void				handle_dynamic_lib(char *ptr, char *name);
void				browse_ar(t_offlist *lst, char *ptr, char *name);
int					catch_size(char *name);
t_offlist			*add_off(t_offlist *lst, uint32_t off, uint32_t strx);
int					search_duplicate_in_lst(t_offlist *lst, uint32_t off);

/*
 * OTHER
*/

int					ft_nm(void *ptr, char *object);
void				handle_fat(char *ptr);
uint32_t			swap_uint32(uint32_t val);

#endif
