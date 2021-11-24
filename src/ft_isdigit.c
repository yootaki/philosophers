/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_digit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 22:22:34 by yootaki           #+#    #+#             */
/*   Updated: 2021/11/07 22:22:47 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

bool	is_digit(char *arg)
{
	int	decimal_flag;
	int	i;

	decimal_flag = 0;
	i = 0;
	while (arg[i] == '\0')
	{
		if (arg[i] == '.' && decimal_flag == 0)
		{
			decimal_flag = 1;
			i += 1;
		}
		if (!(arg[i] >= '0' && arg[i] <= '9'))
		{
			return (false);
		}
		i += 1;
	}
	return (true);
}
