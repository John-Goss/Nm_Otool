/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:26:18 by jle-quer          #+#    #+#             */
/*   Updated: 2017/10/30 14:26:25 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

t_offlist			*order_off(t_offlist *lst)
{
	t_offlist	*cur;
	uint32_t	tmp;
	int			stop;

	cur = lst;
	stop = 1;
	while (cur && stop)
	{
		stop = 0;
		cur = lst;
		while (cur->next)
		{
			if (cur->off > cur->next->off)
			{
				stop = 1;
				tmp = cur->off;
				cur->off = cur->next->off;
				cur->next->off = tmp;
			}
			cur = cur->next;
		}
	}
	return (lst);
}

struct nlist		*fill_array(struct nlist *tab, int nsyms)
{
	int				i;
	struct nlist	*tab2;

	tab2 = (struct nlist*)malloc(sizeof(struct nlist) * nsyms);
	i = -1;
	if (tab2 == NULL)
		return (NULL);
	while (++i < nsyms)
		tab2[i] = tab[i];
	return (tab2);
}

struct nlist		*bubble_sort(char *stringtable, struct nlist *tab,
	int nsyms)
{
	int				i;
	int				j;
	struct nlist	*new_tab;
	struct nlist	temp;

	i = 0;
	new_tab = fill_array(tab, nsyms);
	while (i < nsyms)
	{
		j = 0;
		while (j < nsyms)
		{
			if (ft_strcmp(stringtable + new_tab[i].n_un.n_strx,
				stringtable + new_tab[j].n_un.n_strx) < 0)
			{
				temp = new_tab[i];
				new_tab[i] = new_tab[j];
				new_tab[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (new_tab);
}

struct nlist_64		*fill_array_64(struct nlist_64 *tab, int nsyms)
{
	int				i;
	struct nlist_64	*tab2;

	tab2 = (struct nlist_64*)malloc(sizeof(struct nlist_64) * nsyms);
	if (tab2 == NULL)
		return (NULL);
	i = -1;
	while (++i < nsyms)
		tab2[i] = tab[i];
	return (tab2);
}

struct nlist_64		*bubble_sort_64(char *stringtable, struct nlist_64 *tab,
	int nsyms)
{
	int				i;
	int				j;
	struct nlist_64	*new_tab;
	struct nlist_64	temp;

	i = 0;
	new_tab = fill_array_64(tab, nsyms);
	while (i < nsyms)
	{
		j = 0;
		while (j < nsyms)
		{
			if (ft_strcmp(stringtable + new_tab[i].n_un.n_strx,
					stringtable + new_tab[j].n_un.n_strx) < 0)
			{
				temp = new_tab[i];
				new_tab[i] = new_tab[j];
				new_tab[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (new_tab);
}
