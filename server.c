/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galpers <galpers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:14:55 by galpers           #+#    #+#             */
/*   Updated: 2022/03/30 15:20:50 by galpers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static char	*ft_appendc(char *start, char c)
{
	size_t	i;
	char	*tmp;

	tmp = malloc(ft_strlen(start) + 2);
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while (start[i] != '\0')
	{
		tmp[i] = start[i];
		i++;
	}
	tmp[i] = c;
	tmp[i + 1] = '\0';
	free(start);
	return (tmp);
}

static void	ft_convert(char *s)
{
	int				pos;
	unsigned char	c;
	size_t			i;

	pos = 1;
	c = 0;
	i = ft_strlen(s) - 1;
	while (i + 1 != 0)
	{
		c += pos * (s[i] - '0');
		pos *= 2;
		i--;
	}
	write(1, &c, 1);
}

static void	ft_read_bit_and_conversion(int sig)
{
	static char	*bits;
	static int	bitcount;

	bitcount++;
	if (bits == NULL)
	{
		bits = ft_strdup("");
		bitcount = 1;
	}
	if (sig == SIGUSR2)
		bits = ft_appendc(bits, '0');
	else
		bits = ft_appendc(bits, '1');
	if (bitcount == 8)
	{
		ft_convert(bits);
		free(bits);
		bits = NULL;
	}
}

int	main(void)
{
	ft_printf("Server PID: %u\n", getpid());
	while (1 == 1)
	{
		signal(SIGUSR1, ft_read_bit_and_conversion);
		signal(SIGUSR2, ft_read_bit_and_conversion);
		pause();
	}
	return (0);
}
