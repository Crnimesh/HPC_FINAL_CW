#include <stdio.h>
int main(int argc, char const *argv[])
{
	/* code 
		B=A+C
		B=C+D
		C=B+D
		Assigning the initial value::
	*/
	int A=1,B,C=2,D=3;
	B=A+C;
	B=C+D;
	C=B+D;
	printf("%d::%d\n",B,C);

	return 0;
}
