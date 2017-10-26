#include "../../include/nm.h"

char type_n_sect(uint32_t n_sect, t_symbol_value symt)
{
	if (n_sect == symt.text)
		return ('T');
	if (n_sect == symt.data)
		return ('D');
	if (n_sect == symt.bss)
		return ('B');
	return ('S');
}

char type_element_32(struct nlist list, t_symbol_value symt)
{
	char car;
	
	car = '?';
	if ((list.n_type & N_TYPE) == N_UNDF)
	{
		if (list.n_value)
			car = 'C';
		else
			car = 'U';
	}
	else if ((list.n_type & N_TYPE) == N_ABS)
		car = 'A';
	else if ((list.n_type & N_TYPE) == N_PBUD)
		car = 'U';
	else if ((list.n_type & N_TYPE) == N_SECT)
		car = type_n_sect(list.n_sect, symt);
	else if ((list.n_type & N_TYPE) == N_INDR)
		car = 'I';
	if (!(list.n_type & N_EXT) && car != '?')
		car = ft_tolower(car);
	return (car);
}

char type_element_64(struct nlist_64 list, t_symbol_value symt)
{
	char car;
	
	car = '?';
	if ((list.n_type & N_TYPE) == N_UNDF)
	{
		if (list.n_value)
			car = 'C';
		else
			car = 'U';
	}
	else if ((list.n_type & N_TYPE) == N_ABS)
		car = 'A';
	else if ((list.n_type & N_TYPE) == N_PBUD)
		car = 'U';
	else if ((list.n_type & N_TYPE) == N_SECT)
		car = type_n_sect(list.n_sect, symt);
	else if ((list.n_type & N_TYPE) == N_INDR)
		car = 'I';
	if (!(list.n_type & N_EXT) && car != '?')
		car = ft_tolower(car);
	return (car);
}
