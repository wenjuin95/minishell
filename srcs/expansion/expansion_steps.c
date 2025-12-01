/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_steps.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:25:17 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/08/11 20:13:58 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*quote_removal(char *str)
{
	char	*removed;

	removed = ft_substr(str, 1, ft_strlen(str) - 2);
	free(str);
	return (removed);
}
