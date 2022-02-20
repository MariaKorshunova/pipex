/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 16:44:24 by jmabel            #+#    #+#             */
/*   Updated: 2022/02/20 19:50:07 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
			i++;
		return (i);
	}
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (s)
	{
		len = 0;
		while (s[len])
			len++;
		write(fd, s, len);
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*temp_s1;
	unsigned char	*temp_s2;

	i = 0;
	temp_s1 = (unsigned char *)s1;
	temp_s2 = (unsigned char *)s2;
	while ((*temp_s1 || *temp_s2) && i < n)
	{
		if (*temp_s1 != *temp_s2)
			return (*temp_s1 - *temp_s2);
		temp_s1++;
		temp_s2++;
		i++;
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	dest = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		dest[i] = s1[i];
		i++;
	}
	j = i;
	i = 0;
	while (i < ft_strlen(s2))
		dest[j++] = s2[i++];
	dest[j] = '\0';
	return (dest);
}
