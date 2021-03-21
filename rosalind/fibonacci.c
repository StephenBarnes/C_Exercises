#include <stdio.h>
#include <malloc.h>

int fib(int n) {
	// fib(1) = fib(2) = 1

	// x and y are values of fib(i-1) and fib(i), or the other way around when
	// i is odd.

	int x = 1, y = 1, i = 2;
	while (i < n) {
		if (i % 2)
			x = x + y;
		else
			y = x + y;
		i++;
	}
	return (i % 2) ? y : x;
	// note edge case n=1; returns fib(2) instead, but it's equal to fib(1)
}


int main() {
	printf("fib(n) where n = ");
	int n; // assume it's a positive integer
	scanf("%d", &n);
	printf("%d\n", fib(n));
}
