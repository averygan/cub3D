/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:02:25 by yliew             #+#    #+#             */
/*   Updated: 2023/09/07 15:10:58 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
/*
int	main(void)
{
	char	*test[6] = {"a", "A", "x", "X", "0", ""};
	int	i = 0;

	while (i < 6)
	{
		printf("%s: %i\n", test[i], ft_isalpha((int)(*test[i])));
		i++;
	}
	return (0);
}
*/
