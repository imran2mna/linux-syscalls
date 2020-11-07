#include <stdio.h>
#include "add.h"

int main(void){
	int x=5 , y=7;
	x++; y++;
	printf("(%d + %d) = %d\n", x, y , add(y, x));
}
