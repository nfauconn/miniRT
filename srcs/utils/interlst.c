#include "ray.h"

/* LIST ELEM VARIANT OF INTERSECTION*/

t_inter		*find_hit(t_inter **interlst)
{
	t_inter	*tmp;
	t_inter	*hit;

	tmp = *interlst;
	hit = tmp;
	while (tmp)
	{
		if (tmp->t >= 0 && tmp->t < hit->t)
			hit = tmp;
		tmp = tmp->next;
	}
	if (hit->t < 0)
		return (NULL);
	return (hit);
}

t_inter	*create_inter(float t, t_obj obj)
{
	t_inter	*i;

	i = malloc(sizeof(t_inter));
	if (!i)
		return (NULL);
	i->t = t;
	i->obj = obj;
	return (i);
}

void	interaddback(t_inter **head, t_inter *new)
{
	t_inter	*tmp;

	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	new->next = NULL;
}

void	free_interlst(t_inter **lst)
{
	t_inter	*to_free;

	while (*lst)
	{
		to_free = *lst;
		*lst = (*lst)->next;
		free(to_free);
	}
}

/* add to interlst the new t values found with the given ray
   does not ignore negative t values, as it seems util for chapter 8
   with boolean operations */
void	add_obj_inters(t_xs xs, t_inter **interlst)
{
	size_t				i;
	t_inter				*inter;

	i = -1;
	while (i < xs.count)
	{
		inter = create_inter(xs.t[i], xs.obj);
		interaddback(interlst, inter);
		i++;
	}
}

