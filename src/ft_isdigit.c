/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 22:22:34 by yootaki           #+#    #+#             */
/*   Updated: 2021/12/05 07:22:10 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <limits.h>

static bool	ft_ovcheck(int sign, long num, long next_num)
{
	long	ov_div;
	long	ov_mod;

	ov_div = INT_MAX / 10;
	ov_mod = INT_MAX % 10;
	if (sign == 1 && ((num > ov_div)
			|| (ov_div == num && next_num > ov_mod)))
	{
		return (false);
	}
	if (sign == -1 && ((num > ov_div)
			|| (ov_div == num && next_num > ov_mod + 1)))
	{
		return (false);
	}
	return (true);
}

bool	is_digit(char *arg)
{
	int		i;
	int		sign;
	long	result;
	bool	check;

	sign = 1;
	result = 0;
	i = 0;
	while (arg[i] == ' ' || (arg[i] >= 7 && arg[i] <= 13))
		i++;
	if (arg[i] == '-')
	{
		return (false);
	}
	else if (arg[i] == '+')
		i++;
	while (arg[i] != '\0' && (arg[i] >= '0' && arg[i] <= '9'))
	{
		check = ft_ovcheck(sign, result, arg[i] - '0');
		if (result > 0 && check == false)
			return (false);
		result = result * 10 + (arg[i++] - '0');
	}
	return (true);
}
