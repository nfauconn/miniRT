/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:22:20 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/14 17:16:32 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# include "ft_printf.h"

# define BUFFER_SIZE 100
# define FD_MAX 10240

typedef unsigned long long	t_ull;

typedef enum e_bool
{
	OK = 0,
	FAIL = 1,
}	t_bool;
/* 
typedef struct s_vector
{
	int	x;
	int	y;
}	t_v;

typedef struct s_float_vector
{
	float	x;
	float	y;
}	t_float_vector;

typedef struct s_float_vector
{
	float	x;
	float	y;
}	t_float_vector;
 */
typedef struct s_newstr
{
	char	*str;
	size_t	len;
}	t_newstr;

typedef struct s_indexes
{
	size_t	start;
	size_t	curr;
}	t_indexes;

typedef struct s_charptr
{
	char	*start;
	char	*end;
}	t_charptr;

typedef struct s_list
{
	void			*content;
	int				type;
	struct s_list	*next;
}	t_list;

/* COMPARISON / SEARCH */
int			ft_iswhitespace(int c);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			is_blank(int c);
int			is_identifier(int c);
int			is_quote(int c);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_str_isdigit(char *str);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strend_cmp(char *name, char *end);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strrchr(const char *s, int c);

/* CONVERSION */
int			ft_atoi(const char *s);
float		ft_atof(char *str);
char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);
char		**ft_split_whitespace(char const *s);
t_list		*ft_strarraytolist(char **tab);
char		*ft_ulltoa_base(unsigned long long n, int base, size_t maj);
char		**ft_lsttostrarray(t_list *lst);

/* DISPLAY */
void		ft_lstdisplay(t_list *lst);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_strarraydisplay(char **tab);

/* GNL */
char		*get_next_line(int fd);

/* LISTS */
void		ft_lstadd_back(t_list **alst, t_list *new);
void		ft_lstadd_front(t_list **alst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstnew(void *content);
int			ft_lstsize(t_list *lst);

/* MEMORY */
void		*ft_calloc(size_t count, size_t size);
void		*ft_memalloc(size_t size);
void		ft_memdel(void **ap);
char		*ft_reallocstr(char *str, size_t newlen);
char		*free_replace(char **old, char *new);
void		ft_strarrayclear(char ***tab);
void		ft_strdel(char **as);

/* REPLACE / COPY / JOIN / ITER */
void		ft_bzero(void *s, size_t n);
t_newstr	ft_initnewstr(void);
void		*ft_memccpy(void *dst, const void *src, int c, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);
char		**ft_strarraydup(char **strarray);
char		*ft_strdup(char *s1);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strjoin(char *s1, char *s2);
void		ft_strfjoin(char **over, char *buff);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char *source, size_t start, size_t len);
int			ft_toupper(int c);
int			ft_tolower(int c);

/* SIZE / LEN / MATHS */
int			ft_nbrlen_base(int nbr, int base);
float		ft_negative_power(int nb, int power);
t_ull		ft_power(int nb, int power);
void		ft_rev_int_tab(int *tab, int size);
int			*ft_sort_int_tab(int *tab, int size);
ssize_t		ft_strarraysize(char **tab);
size_t		ft_strlen(const char *str);
int			ft_square_root(int nb);

#endif
