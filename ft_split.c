/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 18:56:45 by jmabel            #+#    #+#             */
/*   Updated: 2022/02/20 15:44:41 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (len > ft_strlen(s) - (size_t)start)
		len = ft_strlen(s) - (size_t)start;
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (i < len)
		dest[i++] = s[(size_t)start++];
	dest[i] = '\0';
	return (dest);
}

static	size_t	ft_str_count(char const *s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static void	ft_free_array_with_len(char **arr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len - 1)
		free(arr[i++]);
	free(arr);
}

static	char	**ft_make_array(char **arr, char const *s, char c)
{
	const char	*start;
	size_t		i;
	size_t		letter;

	i = 0;
	while (*s)
	{
		letter = 0;
		while (*s == c && *s)
			s++;
		start = (char *)s;
		while (*s != c && *s)
		{
			letter++;
			s++;
		}
		if (*(s - 1) != c)
		{
			arr[i++] = ft_substr(start, 0, letter);
			if (arr == NULL)
				ft_free_array_with_len(arr, i);
		}
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char		**arr;

	if (!s)
		return (NULL);
	arr = malloc(sizeof(*arr) * (ft_str_count(s, c) + 1));
	if (arr == NULL)
		return (NULL);
	arr = ft_make_array(arr, s, c);
	return (arr);
}
