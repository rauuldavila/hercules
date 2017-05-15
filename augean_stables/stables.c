/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stables.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavila <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 17:14:14 by rdavila           #+#    #+#             */
/*   Updated: 2017/03/10 17:24:00 by rdavila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

long	sum_array(int *array, int size)
{
	long	sum;
	int		index;

	sum = 0;
	index = 0;
	while (index < size)
	{
		sum += array[index];
		index++;
	}
	return (sum);
}

void	allocate_loads_of_memory(void)
{
	int		*int_pointer_powa;
	char	*pointer_powa;
	int		*another_pointer;
	int		index;

	index = 0;
	int_pointer_powa = (int*)malloc(sizeof(int) * 4242);
	pointer_powa = (char*)malloc(sizeof(char*) * 42);
	another_pointer = (int*)malloc(sizeof(int) * 424242);
	bzero(int_pointer_powa, 4242 * sizeof(int));
	bzero(pointer_powa, 42 * sizeof(char*));
	bzero(another_pointer, 424242 * sizeof(int));
	memset(pointer_powa, 42, 42);
	memset(int_pointer_powa, 42, 4242);
	while (index < 424242)
	{
		another_pointer[index] = index * 42;
		index++;
	}
	printf("%ld\n", sum_array(int_pointer_powa, 4242));
	printf("%s\n", pointer_powa);
	printf("%ld\n", sum_array(another_pointer, 424242));
	free(int_pointer_powa);
	free(pointer_powa);
	free(another_pointer);
}

int		main(void)
{
	allocate_loads_of_memory();
	return (0);
}
