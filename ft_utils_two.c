/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 23:17:15 by seojang           #+#    #+#             */
/*   Updated: 2024/12/07 23:17:37 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_test.h"

size_t	ft_strlen(char const *str)
{
	size_t	len;

	len = 0;
	while (*(str + len))
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;

	len = 0;
	while (*src)
	{
		if (len + 1 < size)
			*dst++ = *src;
		src++;
		len++;
	}
	if (size > 0)
		*dst = '\0';
	return (len);
}
