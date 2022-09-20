/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:13:56 by eleotard          #+#    #+#             */
/*   Updated: 2022/09/20 21:04:56 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tabtab(char **tab)
{
	int	k;

	k = 0;
	if (!tab)
		return ;
	while (tab[k])
	{
		printf("[%s]\n", tab[k]);
		k++;
	}
}

void	print_err(char *file, char *s, char *s2)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd("\n", 2);
}
