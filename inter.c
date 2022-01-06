/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:11:57 by ablondel          #+#    #+#             */
/*   Updated: 2022/01/06 16:17:18 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	inter(char *s1, char *s2)
{
	int t1[128] = {[0 ... 127] = 0};
	int i = 0;
	while (s1[i])
	{
		t1[(int)s1[i]]++;
		i++;
	}
	i = 0;
	while (s2[i])
	{
		t1[(int)s2[i]]++;
		i++;
	}
	i = 0;
	while (s1[i])
	{
		if (t1[(int)s1[i]] >= 2)
		{
			write(1, &s1[i], 1);
			t1[(int)s1[i]] = -1;
		}
		i++;
	}
}

int		main(int ac, char **av)
{
	if (ac == 3)
		inter(av[1], av[2]);
	write(1, "\n", 1);
}