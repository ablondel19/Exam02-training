/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:56:02 by ablondel          #+#    #+#             */
/*   Updated: 2022/01/06 16:10:48 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int     check(char c, char *s)
{
    while (*s)
    {
        if (*s == c)
            return (1);
        s++;
    }
    return (0);
}

void    ft_union(char *s1, char *s2)
{
    char t1[128] = {[0 ... 127] = 0};
    char t2[128] = {[0 ... 127] = 0};
    int i = 0;

    while (s1[i])
    {
        t1[(int)s1[i]]++;
        i++;
    }
    i = 0;
    while (s2[i])
    {
        t2[(int)s2[i]]++;
        i++;
    }
    i = 0;
    while (s1[i])
    {
        if (t1[(int)s1[i]] >= 1)
        {
            write(1, &s1[i], 1);
            t1[(int)s1[i]] = -1;
        }
        i++;
    }
    i = 0;
    while (s2[i])
    {
        if (t2[(int)s2[i]] >= 1 && !check(s2[i], s1))
        {
            write(1, &s2[i], 1);
            t2[(int)s2[i]] = -1;
        }
        i++;
    }
}

int     main(int ac, char **av)
{
    if (ac == 3)
        ft_union(av[1], av[2]);
    write(1, "\n", 1);
}