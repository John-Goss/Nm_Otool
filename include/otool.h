/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:40:06 by jle-quer          #+#    #+#             */
/*   Updated: 2017/10/31 15:32:40 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <fcntl.h>
# include <ar.h>
# include <mach-o/ranlib.h>
# include <mach-o/fat.h>
# include <sys/stat.h>
# include <stdlib.h>
# include "../libft/INCLUDES/libft.h"

int						g_bonus_otool;
int						g_is_big_endian;

typedef struct			s_offlist
{
	uint32_t			off;
	uint32_t			strx;
	struct s_offlist	*next;
}						t_offlist;

int						ft_printf(const char *str, ...);

/*
** FT_OTOOL
*/

int						print_error(char *av, char *str);
int						ft_otool(char *ptr, char *str, int display);
int						loop_arg_otool(char *av);

/*
** DISPLAY
*/

void					print_section(long unsigned int addr, unsigned int size,
	char *ptr, char *section);
void					print_section_64(long unsigned int addr,
		unsigned int size, char *ptr, char *section);

/*
** SORT
*/

t_offlist				*order_off(t_offlist *lst);
struct nlist			*fill_array(struct nlist *tab, int nsyms);
struct nlist			*bubble_sort(char *stringtable, struct nlist *tab,
	int nsyms);
struct nlist_64			*fill_array_64(struct nlist_64 *tab, int nsyms);
struct nlist_64			*bubble_sort_64(char *stringtable, struct nlist_64 *tab,
	int nsyms);

/*
** ARCH_64
*/

void					symtab_building_64(struct mach_header_64 *header,
	struct load_command *lc);
void					print_output_64(struct symtab_command *sym,
	struct mach_header_64 *header, char *ptr);
void					handle_64(char *ptr, char *file, int display);

/*
** ARCH_32
*/

void					symtab_building(struct mach_header *header,
	struct load_command *lc);
void					print_output(struct symtab_command *sym,
	struct mach_header *header, char *ptr);
void					handle_32(char *ptr, char *file, int display);

/*
** ARCH_LIB
*/

int						get_size(char *name);
char					*get_name(char *name);
t_offlist				*add_off(t_offlist *lst, uint32_t off, uint32_t strx);
void					print_ar(t_offlist *lst, char *ptr, char *file);
void					handle_lib(char *ptr, char *name);

/*
** ARCH_FAT
*/

uint32_t				swap_uint32(uint32_t val);
void					handle_fat(char *ptr, char *file);

/*
** UTILS
*/

void					set_architecture(unsigned int magic_number);
int						search_lst(t_offlist *lst, uint32_t off);

#endif
