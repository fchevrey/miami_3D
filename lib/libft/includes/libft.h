/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 16:05:21 by fchevrey          #+#    #+#             */
/*   Updated: 2018/04/19 14:54:55 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <limits.h>
# define BUFF_SIZE 4096
# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

typedef struct		s_list
{
	void			*content;
	int				id;
	struct s_list	*next;
}					t_list;

void				ft_bzero(void *s, size_t n);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_atoi(const char *str);
size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *src);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,
		size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void(*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char(*f)(char));
char				*ft_strmapi(char const *s, char(*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *c, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putnbr(int nbr);
void				ft_putnbr_fd(int n, int fd);
void				ft_putnbrnl(int nb);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
int					ft_str_is_digit(const char *src);
t_list				*ft_lstnew(void *content, int id);
t_list				*ft_lstnew_cpy(void const *content, size_t content_size,
		int id);
void				ft_lstdelone(t_list **alst, void (*del)(void *));
void				ft_lstdel(t_list **alst, void(*del)(void *));
void				ft_lstadd(t_list **amst, t_list *new_elem);
t_list				*ft_lstsrch(t_list *lst, int id);
void				ft_lstadd_last(t_list *alst, t_list *new_elem);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
char				*ft_strlower(char *src);
char				*ft_strupper(char *src);
void				ft_tabprint(char **tab);
void				ft_tabdel(char ***tab);
char				*ft_strjoinf(char *s1, char const *s2);
char				*ft_strsubf(char *c, unsigned int start, size_t len);
int					get_next_line(const int fd, char **line);
int					get_next_line_multi(const int fd, char **line);
void				print_memory(const void *addr, size_t size);
size_t				ft_tablen(char **tab);
int					count_lines_of_file(char *filename);
#endif
