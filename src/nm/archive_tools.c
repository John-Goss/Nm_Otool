#include "../../include/nm.h"

static char	*catch_name(char *name)
{
	size_t		length;
	
	length = ft_strlen(ARFMAG);
	return (ft_strstr(name, ARFMAG) + length);
}

static void	print_ar(uint32_t off, char *ptr, char *file)
{
	int				size_fuck;
	struct ar_hdr	*arch;
	char			*name;
	
	arch = (void*)ptr + off;
	name = catch_name(arch->ar_name);
	size_fuck = catch_size(arch->ar_name);
	ft_printf("\n%s(%s):\n", file, name);
	ft_nm((void*)arch + sizeof(*arch) + size_fuck, file);
}

t_offlist	*add_off(t_offlist *lst, uint32_t off, uint32_t strx)
{
	t_offlist	*tmp;
	t_offlist	*tmp2;
	
	tmp = (t_offlist*)malloc(sizeof(t_offlist));
	tmp->off = off;
	tmp->strx = strx;
	tmp->next = NULL;
	if (!lst)
		return (tmp);
	tmp2 = lst;
	while (tmp2->next)
		tmp2 = tmp2->next;
	if (search_duplicate_in_lst(lst, off))
		return (lst);
	tmp2->next = tmp;
	return (lst);
}

int			catch_size(char *name)
{
	int		x;
	char	*word;
	
	word = ft_strchr(name, '/') + 1;
	x = ft_atoi(word);
	return (x);
}

void		browse_ar(t_offlist *lst, char *ptr, char *name)
{
	t_offlist	*tmp;
	
	tmp = lst;
	while (tmp)
	{
		print_ar(tmp->off, ptr, name);
		tmp = tmp->next;
	}
}
