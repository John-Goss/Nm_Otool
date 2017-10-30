/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 12:33:59 by jle-quer          #+#    #+#             */
/*   Updated: 2017/10/30 12:40:56 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/nm.h"

static struct nlist		*fill_array_32(struct nlist *tab, int taille)
{
	struct nlist	*tab2;
	int				i;

	tab2 = (struct nlist*)malloc(sizeof(struct nlist) * taille);
	i = 0;
	while (i < taille)
	{
		tab2[i] = tab[i];
		i++;
	}
	return (tab2);
}

static struct nlist_64	*fill_array_64(struct nlist_64 *tab, int taille)
{
	struct nlist_64	*tab2;
	int				i;

	tab2 = (struct nlist_64*)malloc(sizeof(struct nlist_64) * taille);
	i = 0;
	while (i < taille)
	{
		tab2[i] = tab[i];
		i++;
	}
	return (tab2);
}

struct nlist_64			*bubble_sort_nlist_64(char *stringtable,
		struct nlist_64 *tab, int taille)
{
	struct nlist_64	*tab2;
	struct nlist_64	temp;
	int				i;
	int				j;

	i = 0;
	tab2 = fill_array_64(tab, taille);
	while (i < taille)
	{
		j = 0;
		while (j < taille)
		{
			if (ft_strcmp(stringtable + tab2[i].n_un.n_strx,
				stringtable + tab2[j].n_un.n_strx) < 0)
			{
				temp = tab2[i];
				tab2[i] = tab2[j];
				tab2[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (tab2);
}

struct nlist			*bubble_sort_nlist_32(char *stringtable,
		struct nlist *tab, int taille)
{
	struct nlist	*tab2;
	struct nlist	temp;
	int				i;
	int				j;

	i = 0;
	tab2 = fill_array_32(tab, taille);
	while (i < taille)
	{
		j = 0;
		while (j < taille)
		{
			if (ft_strcmp(stringtable + tab2[i].n_un.n_strx,
						stringtable + tab2[j].n_un.n_strx) < 0)
			{
				temp = tab2[i];
				tab2[i] = tab2[j];
				tab2[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (tab2);
}
