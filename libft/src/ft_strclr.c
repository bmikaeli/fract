/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmikaeli <bmikaeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/28 12:16:26 by bmikaeli          #+#    #+#             */
/*   Updated: 2013/12/11 09:54:47 by bmikaeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <libft.h>

void			ft_strclr(char *s)
{
	int			i;

	i = 0;
	i += ft_strlen(s);
	while (i > 0)
	{
		*s = '\0';
		i--;
		s++;
	}
}
