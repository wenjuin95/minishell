/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:03:29 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/05/20 18:04:18 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(const int c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}
