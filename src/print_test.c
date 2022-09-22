/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:13:56 by eleotard          #+#    #+#             */
/*   Updated: 2022/09/22 18:36:46 by elpastor         ###   ########.fr       */
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
	char	*error;

	error = ft_strjoin_free("minishell: ", file, 3);
	if (s)
		error = ft_strjoin_free(error, s, 0);
	if (s2)
		error = ft_strjoin_free(error, s2, 0);
	error = ft_strjoin_free(error, "\n", 0);
	if (error)
	{
		ft_putstr_fd(error, 2);
		free(error);
	}
}

void	print_env(t_env *env)
{
	printf("%d\n", !env);
	while (env)
	{
		printf("name : %s, content : %s\n", env->name, env->content);
		env = env->next;
	}
	printf("\n\n\n");
}
