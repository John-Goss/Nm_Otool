#ifndef NM_TOOL_H
# define NM_TOOL_H

# include <fcntl.h>
# include <stdio.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <sys/stat.h>
# include <stdlib.h>
# include "../libft/INCLUDES/libft.h"

/*
 * # define DBG ft_putstr(__func__); ft_putstr(" in "); \
 * ft_putstr(__FILE__); ft_putstr(" at line : "); \
 * ft_putnbr(__LINE__); ft_putchar('\n')
*/

# define ERROR(name, errmsg) ft_printf("nm: %s: %s\n", name, errmsg); return (-1)

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
 
struct nlist_64		*bubble_sort_nlist_64(char *stringtable, struct nlist_64 *tab, int taille);
void				symbol_build_64(t_symbol_value *symt, struct mach_header_64 *header, struct load_command *lc);
void				handle_64(char *ptr);
void				print_output_64(struct symtab_command *sym, char *ptr, struct mach_header_64 *header);
char				type_element_64(struct nlist_64 list, struct load_command *lc, t_symbol_value symt);

/*
 * x86 ARCH
*/

struct nlist		*bubble_sort_nlist_32(char *stringtable, struct nlist *tab, int taille);
void				symbol_build_32(t_symbol_value *symt, struct mach_header *header, struct load_command *lc);
void				handle_32(char *ptr);
void				print_output_32(struct symtab_command *sym, char *ptr, struct mach_header *header);
char				type_element_32(struct nlist list, struct load_command *lc, t_symbol_value symt);

/*
 * OTHER
*/

void				ft_nm(char *ptr);

#endif
