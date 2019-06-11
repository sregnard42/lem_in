/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 08:34:16 by sregnard          #+#    #+#             */
/*   Updated: 2018/12/03 11:50:20 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_tab(char ***ptr_content)
{
	char	**content;
	int		i;

	content = *ptr_content;
	i = 0;
	while (content[i])
		ft_memdel((void **)&(content[i++]));
	free(content);
	content = NULL;
	*ptr_content = content;
}
