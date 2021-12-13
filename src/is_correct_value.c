/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_correct_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 13:39:17 by yootaki           #+#    #+#             */
/*   Updated: 2021/12/13 17:53:00 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <limits.h>

// static bool	ovcheck(int sign, long num, long next_num)
// {
// 	long	ov_div;
// 	long	ov_mod;

// 	ov_div = INT_MAX / 10;
// 	ov_mod = INT_MAX % 10;
// 	if (sign == 1 && ((num > ov_div)
// 			|| (ov_div == num && next_num > ov_mod)))
// 	{
// 		return (false);
// 	}
// 	if (sign == -1 && ((num > ov_div)
// 			|| (ov_div == num && next_num > ov_mod + 1)))
// 	{
// 		return (false);
// 	}
// 	return (true);
// }

// bool	is_correct_value(char *arg)
// {
// 	int		i;
// 	int		sign;
// 	long	result;
// 	bool	check;

// 	sign = 1;
// 	result = 0;
// 	i = 0;
// 	if (arg[i] == '-')
// 		return (false);
// 	else if (arg[i] == '+')
// 		i++;
// 	if (arg[i] == '0')
// 		return (false);
// 	while (arg[i] != '\0')
// 	{
// 		if (!(arg[i] >= '0' && arg[i] <= '9'))
// 			return (false);
// 		check = ovcheck(sign, result, arg[i] - '0');
// 		if (result > 0 && check == false)
// 			return (false);
// 		result = result * 10 + (arg[i++] - '0');
// 	}
// 	return (true);
// }


static bool	int_overcheck(long num)
{
	if (num > INT_MAX)
	{
		return (false);
	}
	return (true);
}

bool	is_correct_value(char *arg)
{
	int		i;
	long	result;

	result = 0;
	i = 0;
	if (arg[i] == '-')
		return (false);
	else if (arg[i] == '+')
		i++;
	if (arg[i] == '0')
		return (false);
	while (arg[i] != '\0')
	{
		if (!(arg[i] >= '0' && arg[i] <= '9'))
			return (false);
		result = result * 10 + (arg[i++] - '0');
		if (int_overcheck(result) == false)
			return (false);
	}
	return (true);
}
