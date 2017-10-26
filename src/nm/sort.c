#include "../include/nm.h"

static struct nlist		*fill_array_32(struct nlist *tab, int taille)
{
	struct nlist *tab2;
	int             i;
	
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
    struct nlist_64 *tab2;
    int             i;

    tab2 = (struct nlist_64*)malloc(sizeof(struct nlist_64) * taille);
    i = 0;
    while (i < taille)
    {
        tab2[i] = tab[i];
        i++;
    }
    return (tab2);
}

struct nlist_64			*bubble_sort_nlist_64(char *stringtable, struct nlist_64 *tab, int taille)
{
    struct nlist_64 *tab2;
    struct nlist_64 temp;
    int i;
    int j;

    i = 0;
    tab2 = fill_array_64(tab, taille);
    while (i < taille)
    {
        j = 0;
        while(j < taille)
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

struct nlist			*bubble_sort_nlist_32(char *stringtable, struct nlist *tab, int taille)
{
	struct nlist *tab2;
	struct nlist temp;
	int i;
	int j;
	
	i = 0;
	tab2 = fill_array_32(tab, taille);
	while (i < taille)
	{
		j = 0;
		while(j < taille)
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

void	sort_duplicate_strx_by_value_32(struct nlist *array, char *stringtable, struct load_command *lc, uint32_t size)
{
	uint32_t		tmp_value;
	int				sorted;
	int				increment;
	
	sorted = 0;
	tmp_value = 0;
	increment = 0;
	while (!sorted)
	{
		sorted = 1;
		increment = 0;
		while (increment < size - 1)
		{
			if (ft_strcmp(stringtable + array[increment].n_un.n_strx, stringtable + array[increment + 1].n_un.n_strx) == 0)
			{
				if (array[increment].n_value > array[increment + 1].n_value)
				{
					tmp_value = array[increment + 1].n_value;
					array[increment + 1].n_value = array[increment].n_value;
					array[increment].n_value = tmp_value;
					sorted = 0;
				}
			}
			++increment;
		}
	}
}

void	sort_duplicate_strx_by_value_64(struct nlist_64 *array, char *stringtable, struct load_command *lc, uint32_t size)
{
	uint64_t		tmp_value;
	int				sorted;
	int				increment;
	
	sorted = 0;
	tmp_value = 0;
	increment = 0;
	while (!sorted)
	{
		sorted = 1;
		increment = 0;
		while (increment < size - 1)
		{
			if (ft_strcmp(stringtable + array[increment].n_un.n_strx, stringtable + array[increment + 1].n_un.n_strx) == 0)
			{
				if (array[increment].n_value > array[increment + 1].n_value)
				{
					tmp_value = array[increment + 1].n_value;
					array[increment + 1].n_value = array[increment].n_value;
					array[increment].n_value = tmp_value;
					sorted = 0;
				}
			}
			++increment;
		}
	}
}
