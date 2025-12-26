/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/12/27 00:49:25 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

static int	is_valid_number(const char *str)
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

double	ft_atof(const char *str)
{
	double	result;
	double	fraction;
	int		sign;

	while (is_space(*str))
		str++;
	if (!is_valid_number(str))
		error_exit("Error\nInvalid number format");
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = 0;
	while (*str >= '0' && *str <= '9')
		result = result * 10 + (*str++ - '0');
	if (*str == '.')
		str++;
	fraction = 0.1;
	while (*str >= '0' && *str <= '9')
	{
		result += (*str++ - '0') * fraction;
		fraction *= 0.1;
	}
	return (result * sign);
}

void	free_parts(char **parts)
{
	int	i;

	if (!parts)
		return ;
	i = 0;
	while (parts[i])
		free(parts[i++]);
	free(parts);
}

void	init_scene(t_scene *scene)
{
	scene->has_ambient = 0;
	scene->has_camera = 0;
	scene->has_light = 0;
	scene->objects = NULL;
	scene->object_count = 0;
}

int	check_extension(char *filename)
{
	int	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strncmp(filename + len - 3, ".rt", 3) == 0);
}
