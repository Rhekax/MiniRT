/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 00:00:00 by yenyilma          #+#    #+#             */
/*   Updated: 2025/12/29 00:00:00 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int	is_valid_number(const char *str)
{
	int	i;
	int	has_digit;
	int	has_dot;

	i = 0;
	has_digit = 0;
	has_dot = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (has_dot)
				return (0);
			has_dot = 1;
		}
		else if (str[i] >= '0' && str[i] <= '9')
			has_digit = 1;
		else
			return (0);
		i++;
	}
	return (has_digit);
}
