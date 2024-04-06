/*
面向对象的三大特性：
1、通过给类中成员授予权限实现封装，能隐藏类中的细节
2、继承是一种类间关系，能代码复用
3、多态：一个接口多种方法，父类指针指向子类对象，可以调用子类方法

const替代#define的好处：const修饰的变量有类型和作用域，可以检查类型是否匹配和限定作用范围
const修饰全局变量不可改变，const修饰局部变量可以间接改变

c与c++的区别：
1、c++结构体能写函数
2、c++结构体定义对象时无需加struct
3、c++类型转换要显式
4、c++的const全局变量没有内存
5、c++的三目运算符返回的左值
6、c++有引用类型
7、c++能重载函数

内联函数inline：没有函数入口地址，建议编译器将函数体插入并替换函数调用处，节省了调用函数的额外时间开支（类似于宏替换），类的成员函数默认内联

malloc与free不会调用构造函数初始化，不会调用析构函数释放，因此转用new与delete

常函数即在（）后加const，不会修改成员变量（除非变量加mutable声明）

常对象即在实例化对象前加const，只能调用常函数和修改mutable修饰的成员变量

友元friend函数或类在其他类中声明，可让该函数或类访问其他类的私有成员

析构、构造、重载赋值都不能继承
*/
#include "cppconcept.h"

int main()
{
	int a=10,b=20;
	(a>b?a:b)=30;
	printf("a=%d b=%d\n",a,b);
	std::string p="hello world";
	std::string &pp=p;
	pp="hjk";
	std::cout<<p<<std::endl;
	func(10);
	func(10,20);
	func(10,20,30);
	Student s;
	Student s1(s);//显式调用拷贝构造函数
	//Student s2=s;//隐式调用拷贝构造函数，加explicit后不可
	Student s2;
	s2=s;
	s.printData();
	s1.printData();
	s2.printData();
	printStudent(s);
	Student* s3=new Student("yipahy",1,"cs",18,95);
	Student* s4=s3;//浅拷贝,不是隐式调用拷贝构造，只是指针指向同一地址
	Student* s5=new Student(*s3);
	const Student s6("yyds",2,"md",21,99);
	s3->printData();
	s4->printData();
	s5->printData();
	s6.printData();
	printStudent(*s3);
	std::cout<<s1+*s3<<std::endl;
	std::cout<<s1++<<std::endl;
	std::cout<<++s1<<std::endl;
	Function func;
	std::cout<<func(100,20)<<std::endl;

	delete s3;
	delete s5;
	return 0;
}
