/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htumanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:22:43 by htumanya          #+#    #+#             */
/*   Updated: 2021/10/18 19:22:44 by htumanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_iscap(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (!ft_isdigit(string[i]))
			return (0);
		++i;
	}
	return (1);
}
