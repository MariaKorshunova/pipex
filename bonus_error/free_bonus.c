/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 17:13:03 by jmabel            #+#    #+#             */
/*   Updated: 2022/03/07 17:22:33 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free_array(char **arr)
{
	int	i;
	int	number_str_in_array;

	i = 0;
	number_str_in_array = 0;
	while (arr[number_str_in_array] != NULL)
	{
		number_str_in_array++;
	}
	while (i < number_str_in_array)
		free(arr[i++]);
	free(arr);
}

void	ft_free_pipex(t_pipex *pipex)
{
	ft_free_array(pipex->bin_path);
	ft_free_array(pipex->cmd);
}
