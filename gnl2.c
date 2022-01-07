#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int		ft_len(char *s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	int i;
	char *dst;

	i = -1;
	dst = NULL;
	dst = (char*)malloc(sizeof(char) * (ft_len(src) + 1));
	if (!dst)
		return (NULL);
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}

char    *ft_strjoin(char *s1, char *s2)
{
	int i;
	char *dst;

	i = 0;
	dst = NULL;
	dst = (char*)malloc(sizeof(char) * (ft_len(s1) + ft_len(s2) + 1));
	if (!dst)
		return (NULL);
	while (*s1)
		dst[i++] = *s1++;
	while (*s2)
		dst[i++] = *s2++;
	dst[i] = '\0';
	return (dst);
}

int    ft_load(int fd, char **load)
{
    int ret;
	char *tmp;
    char buf[BUFFER_SIZE + 1];
    
    ret = -1;
	tmp = NULL;
	*load = ft_strdup("\0");
	if (!(*load))
		return (-1);
    while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
    {
		buf[ret] = '\0';
		tmp = *load;
		*load = ft_strjoin(*load, buf);
		free(tmp);
    }
	return (ret);
}

char	*ft_extract(char *src)
{
	int i;
	char *dst;

	i = 0;
	dst = NULL;
	dst = (char*)malloc(sizeof(char) * (ft_len(src) + 2));
	if (!dst)
		return (NULL);
	while (src[i] && src[i] != '\n')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\n';
	dst[i + 1] = '\0';
	return (dst);
}

int		ft_nl(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

char	*ft_update(char *src)
{
	int i;
	int j;
	char *dst;

	i = 0;
	j = 0;
	dst = NULL;
	dst = (char*)malloc(sizeof(char) * (ft_len(src) + 1));
	if (!dst)
		return (NULL);
	j = ft_nl(src) + 1;
	while (src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

char    *get_next_line(int fd)
{
	static char *load;
	static int	x;
	char		*line;
	char		*tmp;

	line = NULL;
	tmp = NULL;
    if (fd == -1 || BUFFER_SIZE < 1)
        return (NULL);
	if (x == 0)
	{
		if (ft_load(fd, &load) < 0)
			return (NULL);
		x = 1;
		line = ft_extract(load);
		if (!line)
			return (NULL);
		tmp = load;
		load = ft_update(load);
		if (!load)
			return (NULL);
		free(tmp);
		return (line);
	}
	else
	{
		if (!load[0])
			return (NULL);
		line = ft_extract(load);
		if (!line)
			return (NULL);
		tmp = load;
		load = ft_update(load);
		if (!load[0])
			return (NULL);
		free(tmp);
		return (line);
	}
    return (NULL);
}

int     main(int ac, char **av)
{
    (void)ac;
    (void)av;
	int fd;
	char *line;

	fd = open(av[1], O_RDONLY);
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		printf("line = %s", line);
		if (line == NULL)
		{
			//system("leaks a.out");
			//printf("\n");
			return (0);
		}
		free(line);
	}
    return (0);
}