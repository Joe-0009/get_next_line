#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

#include <stdio.h>
/* get_next_line_utils.c */
size_t ft_strlen(const char *str);
char *ft_strdup(char *str);
char *ft_strjoin(char *s1, char *s2);
char *ft_strchr(char *str, int c);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
/* main function */
char *get_next_line(int fd);


#endif // GET_NEXT_LINE_H