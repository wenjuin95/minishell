/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:10:25 by welow             #+#    #+#             */
/*   Updated: 2024/05/23 15:45:54 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//check for valid env
static int	valid_env(char *s_cmd)
{
	int	i;

	i = 0;
	//check if the first character is a alpha number or '_'
	while (s_cmd != NULL && s_cmd[i] != '=')
	{
		if (ft_isalnum(s_cmd[i]) == FALSE && s_cmd[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	export_cmd(char **cmd, char **env_storage)
{
	int	i;

	i = 0;
	if (cmd == NULL)
		return (print_environment(env_storage), 0);
	while (cmd[i])
	{
		//check if the cmd is valid
		if (valid_env(cmd[i]) == FALSE)
		{
			ft_printf("minishell: export: `%s': not a valid identifier\n",
				cmd[i]);
			return (1);
		}
		//store to env_storage
		
		i++;
	}
	return (0);
}