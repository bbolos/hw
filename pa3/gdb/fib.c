#include<stdio.h>

int f(int x) {
	if(x == 0 || x == 1){
		return x;
	}
	else {
		return f(x-1) + f(x-2);
	}
}

int main(void) {
	int limit = 10, i, n;

	printf("Here are the first %d numbers in the Fibonacci sequence:\n", limit);
	for(i = 0; i < limit; i++) {
		n = f(i);
		printf("%d\n", n);
	}

	return 0;
}
