/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 10:38:47 by yootaki           #+#    #+#             */
/*   Updated: 2021/12/05 07:15:07 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

bool	validate_args(int num, char **args)
{
	int	i;

	if (num < 4 || num > 5)
	{
		printf("%sThe number of arguments is invalid.%s\n", RED, RESET);
		return (false);
	}
	i = 1;
	while (i <= num)
	{
		if (is_digit(args[i]) == false)
		{
			printf("%sArgument error.%s\n", RED, RESET);
			return (false);
		}
		i += 1;
	}
	return (true);
}
