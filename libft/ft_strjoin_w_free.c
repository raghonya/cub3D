/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:21:11 by raghonya          #+#    #+#             */
/*   Updated: 2023/01/16 16:22:22 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*strjoin_w_free(char const *s1, char const *s2)
{
	int		i;
	int		k;
	char	*s;
	size_t	len1;
	size_t	len2;

	if (!s1)
		return (ft_strdup(s2));
	i = -1;
	k = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s = malloc (sizeof(char) * (len1 + len2 + 1));
	if (!s)
		return (NULL);
	while (++i < (int)(len1 + len2))
	{
		if (i < (int)len1)
			s[i] = s1[i];
		else
			s[i] = s2[k++];
	}
	s[i] = 0;
	free((char *)s1);
	return (s);
}
