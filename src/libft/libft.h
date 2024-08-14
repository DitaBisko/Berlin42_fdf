/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:32:29 by dbisko            #+#    #+#             */
/*   Updated: 2024/07/18 17:33:49 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_atoi(char *str);
int		ft_memcmp(void *s1, void *s2, size_t n);
int		ft_lstsize(t_list *lst);

char	*ft_strchr(char *s, int c);
char	*ft_strrchr(char *s, int c);
char	*ft_itoa(int n);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strnstr(char *haystack, char *needle, size_t len);
char	*ft_strmapi(char *s, char (*f)(unsigned int, char));
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s1);
char	**ft_split(char *str, char sep);
char	*ft_strtrim(char *s1, char *set);

void	*ft_memchr(void *s, int c, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	ft_putchar_fd(char c, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, void *src, size_t n);
void	*ft_memmove(void *dest, void *src, size_t n);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));

size_t	ft_strlen(char *s);
size_t	ft_strlcpy(char *dst, char *src, size_t size);
size_t	ft_strlcat(char *dest, char *src, size_t destsize);

t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// gnl
char	*get_next_line(int fd);

// ft_printf
void	put_num(unsigned int n);

int		ft_printf(const char *string, ...);
int		ft_print_str(char *s);
int		ft_put_char(int c);
int		ft_print_number(int number);
int		ft_print_unsigned(unsigned int number);
int		num_len(unsigned int n);
int		ft_print_pnt(void *address);
int		ft_print_unsigned(unsigned int n);
int		ft_print_lower_hex(unsigned int num);
int		ft_print_upper_hex(unsigned int num);

// from split
int		count_words(char *str, char sep);
void	free_arr(char **arr, int count);

#endif
