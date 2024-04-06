/*
 * static修饰的成员变量：属于类不是对象，生命周期是整个进程，类内声明，类外初始化（不可在函数内）
 * static修饰的成员函数只能访问static成员变量
*/
#include <iostream>

class Printer
{
public:
	 int func()
	 {
		return ++count;
	 }
	 static Printer* getPrinter()
	 {
		return p;
	 }
	 int getcount()
	 {
		return count;
	 }
private:
	static Printer* p;
	int count;
	Printer()
	{
		count=0;
	}
	Printer(const Printer &pt)
	{
		count=pt.count;
	}
};

Printer* Printer::p=new Printer;
int main()
{
	Printer* pp=Printer::getPrinter();
	Printer* ppp=Printer::getPrinter();
	pp->func();
	ppp->func();
	std::cout<<pp->getcount()<<' '<<ppp->getcount()<<std::endl;
	return 0;
}
