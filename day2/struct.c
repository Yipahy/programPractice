#include <stdio.h>
#include <stddef.h>

typedef struct Student
{
	char a;
	float b;
	double c;
	char d;
}Student;

int main()
{
	printf("a的偏移量%ld\n",offsetof(Student,a));
	printf("b的偏移量%ld\n",offsetof(Student,b));
	printf("c的偏移量%ld\n",offsetof(Student,c));
	printf("d的偏移量%ld\n",offsetof(Student,d));
	Student ss={'a',3.14,38924.421,'s'};
	printf("a的值%c\n",*(offsetof(Student,a)+(char*)&ss));
	printf("b的值%1.2f\n",*(float*)(offsetof(Student,b)+(char*)&ss));
	printf("c的值%5.3lf\n",*(double*)(offsetof(Student,c)+(char*)&ss));
	printf("d的值%c\n",*(offsetof(Student,d)+(char*)&ss));
	return 0;
}
