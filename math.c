#include <stdio.h>
#include <string.h>

/**
 * sum - computes sum of two numbers
 * Return: sum of the two numbers.
 */
int sum(void)
{
	int num1, num2;
	int sum;

	printf("Enter two numbers:\n");
	scanf("%d %d", &num1, &num2);
	sum = num1 + num2;
	printf("Sum of your two numbers is: %d ):\n", sum);
	return (0);
}

