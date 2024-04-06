/*
 *链接前，不同的cpp文件单独编译，main文件只是导入函数或类的声明
 *链接时，才将所有的可执行文件链接成可执行文件，此时才有函数入口地址
 *因此，类模板会二次编译，第一次是对类模板的实现cpp文件，第二次是对类模板的
 *实例化main.cpp编译。如果分文件编写（即.h与.cpp）,第一次编译则会报错，因为
 *编译器不知类模板实现的具体数据类型，不同的数据类型会产生不同的代码，故应
 *将cpp与h整合为hpp。
*/
#include "template.hpp"

template<class T>
void myswap(T& a,T& b);

int main()
{
	int a=20,b=30;
	double c=3.14,d=4.13;
	myswap<int>(a,b);
	myswap<double>(c,d);
	std::cout<<a<<" "<<b<<std::endl;
	std::cout<<c<<" "<<d<<std::endl;

	TemplateTest<std::string,int> t1("yyds",18);
	TemplateTest<std::string> t2("yys",25);
	t1.print();
	t2.print();

	return 0;
}

template<class T>
void myswap(T& a,T& b)
{
	T tmp=a;
	a=b;
	b=tmp;
}
