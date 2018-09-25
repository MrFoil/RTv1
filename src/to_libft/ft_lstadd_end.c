//
// Created by artem.rudencko on 9/25/2018.
//

#include "libft.h"

void		ft_lstadd_end(t_list **alst, t_list *new)
{
	t_list	*root;

	root = *alst;
	while ((*alst)->next)
		*alst = (*alst)->next;
	(*alst)->next = new;
	*alst = root;
}