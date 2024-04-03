#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void func(char** p){
	*p="hello world";
}//p被释放
void* func1(){
	char* p="hello";//p指向常量区的hello(浅拷贝)
	return p;
}
void* func2(){
	char* p=malloc(10);
	memset(p,0,10);
	strcpy(p,"hello1");//p指向拷贝在堆区的hello1(深拷贝)
	return p;
}
void* func3(){
	char p[16];
	strcpy(p,"hello2");//p指向拷贝在栈区的hello2(深拷贝)
	return p;//返回野指针
}//p已被释放，栈区hello2释放
void func4(char* p){//即p=buf4
	p="hello3";//p不再指向hhhhh,而是指向hello3(浅拷贝)
}//p被释放
void func5(char* p){
	memset(p,0,10);
	strcpy(p,"hello4");//p指向拷贝在main栈区的hello4(深拷贝)
}
int main(){
	char* buf;
	char* buf1=func1();//buf1指向常量区hello
	char* buf2=func2();//buf2指向堆区的hello1
	func(&buf);//buf指向的是常量区的hello world，&buf被释放
	char* buf3="kkkkk";
    buf3=func3();//buf3指向已释放的栈区
	char* buf4="hhhhh";
	func4(buf4);//p的修改与buf4无关
	char buf5[10];
	func5(buf5);
	printf("%s\n",buf);//hello world
	printf("%s\n",buf1);//hello
	printf("%s\n",buf2);//hello1
	//printf("%s\n",buf3);//buf3为野指针
	printf("%s\n",buf4);//hhhhh
	printf("%s\n",buf5);//hello4
	free(buf2);
	buf2=NULL;
	return 0;
}
