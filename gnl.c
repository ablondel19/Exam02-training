/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:53:06 by ablondel          #+#    #+#             */
/*   Updated: 2022/01/07 13:53:30 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int k = 1;

int		ft_len(char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
}

int		ft_nl(char *s)
{
	int i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char 	*ft_extract(char *src, int nl)
{
	int i = 0;
	char *dst = NULL;
	dst = malloc(sizeof(char) * (ft_len(src) + 1));
	if (!dst)
		return (NULL);
	while (src[i] && i <= nl)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_update(char *src, int nl)
{
	int i = 0;
	char *dst = NULL;
	dst = malloc(sizeof(char) * (ft_len(src) + 1));
	if (!dst)
		return (NULL);
	while (src[nl])
	{
		dst[i] = src[nl];
		nl++;
		i++;
	}
	dst[i] = '\0';
	free(src);
	src = dst;
	return (src);
}

char	*ft_strdup(char *src)
{
	char *dst = NULL;
	int i = -1;

	dst = malloc(sizeof(char) * (ft_len(src) + 1));
	if (!dst)
		return (NULL);
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int i = 0;
	char *dst = NULL;

	dst = malloc(sizeof(char) * (ft_len(s1) + ft_len(s2) + 1));
	if (!dst)
		return (NULL);
	while (*s1)
		dst[i++] = *s1++;
	while (*s2)
		dst[i++] = *s2++;
	dst[i] = '\0';
	return (dst);
}

char	*get_next_line(int fd)
{
	static char	*remaining;
	int			ret;
	char		*line;
	char		*tmp;
	char		buf[BUFFER_SIZE + 1];

	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	if (!remaining)
		if (!(remaining = ft_strdup("")))
			return (NULL);
	ret = BUFFER_SIZE;
	if (k == -1)
		return (NULL);
	while (ret == BUFFER_SIZE && ft_nl(remaining) == -1)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return (NULL);
		buf[ret] = '\0';
		tmp = remaining;
		remaining = ft_strjoin(remaining, buf);
		free(tmp);
		if (!remaining)
			return (NULL);
	}
	if (ft_nl(remaining) >= 0)
	{
		line = ft_extract(remaining, ft_nl(remaining));
		if (!line)
			return (NULL);
		tmp = remaining;
		remaining = ft_update(remaining, ft_nl(remaining) + 1);
		if (!remaining)
			return (NULL);
		return (line);
	}
	if (ft_nl(remaining) < 0)
	{
		k = -1;
		if (!(line = ft_strdup(remaining)))
			return (NULL);
		free(remaining);
		return (line);
	}
	return (NULL);
}

int		main(int ac, char **av)
{
	char *s = NULL;
	if (ac != 2)
		return (0);
	int fd = open(av[1], O_RDONLY);
	while (1)
	{
		s = get_next_line(fd);
		if (!s)
		{
			//printf("%s", s);
			//system("leaks a.out");
			return (0);
		}
		printf("%s", s);
		free(s);
	}
}