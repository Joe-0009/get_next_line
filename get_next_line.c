#include "get_next_line.h"


void	ft_free(char *buffer)
{
    if (!buffer)
        return ;
    free(buffer);
}

char *get_after(char *buffer)
{
    char *line_location;
    char *after;
    size_t len;

    line_location = ft_strchr(buffer, '\n');
    if (!line_location)
        return (NULL);
    line_location++;
    len = ft_strlen(line_location);
    after = ft_calloc(len + 1, 1);
    if (!after)
        return (ft_free(buffer), NULL);
    after = ft_memcpy(after, line_location, len + 1);
    
    ft_free(buffer);
    return (after);
}

char *get_before(char *buffer)
{
    char *before;
    int i;

    i = 0;
    if (!buffer)
        return (NULL);
    while (buffer[i] && buffer[i] != '\n')
        i++;
    if (buffer[i] == '\n')
        i++;
    before = ft_calloc(i + 1, 1);
    if (!before)
        return (NULL);
    ft_memcpy(before, buffer, i);
    return (before);
}

char *get_line(int fd, char *rbuf)
{
    int return_bytes;
    char *buffer;

    buffer = ft_calloc(BUFFER_SIZE + 1, 1);
    if (!buffer)
        return (NULL);
    while (1)
    {
        return_bytes = read(fd, buffer, BUFFER_SIZE);
        if (return_bytes < 0)
            return (ft_free(buffer), ft_free(rbuf), NULL);
        if (return_bytes == 0)
            break ;
        buffer[return_bytes] = '\0';
        rbuf = ft_strjoin(rbuf, buffer);
        if (!rbuf)
            return(ft_free(buffer), ft_free(rbuf), NULL);
        if (ft_strchr(rbuf, '\n'))
            break ;
    }
    ft_free(buffer);
    return (rbuf);
}

char *get_next_line(int fd)
{
    static char *buffer;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
        return (NULL);
    buffer = get_line(fd, buffer);
    if (!buffer)
        return (NULL);
    if (buffer && !*buffer)
    {
        ft_free(buffer);
        return (NULL);
    }
    line = get_before(buffer);
    buffer = get_after(buffer);
    return (line);
}

