#include <cub3d.h>

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*a;

	if (!*lst && new)
	{
		*lst = new;
		return ;
	}
	else if (!new)
		return ;
	a = *lst;
	while ((*lst)->next)
		*lst = (*lst)->next;
	(*lst)->next = new;
	*lst = a;
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->img.img = content;
	new->next = NULL;
	return (new);
}
