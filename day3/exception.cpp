/*
 *栈解旋：抛出异常的函数中，函数会释放try{}中之前创建的对象（除了throw的对象），但函数并未结束。但是，如果异常没有被捕获，则程序则会异常终止
 */
#include <iostream>
#include <stdexcept>
#include <unistd.h>
class Father
{
	public:
		virtual void print()
		{
			std::cout<<"Father"<<std::endl;
		}
	private:
		int a;
};
class Son:public Father
{
	public:
		virtual void print() override
		{
			std::cout<<"Son"<<std::endl;
		}
	private:
		double d;
};
class AA
{
	public:
		AA(int age)
		{
			if(age<0||age>130) throw std::out_of_range("年龄不在正常范围内");
			else this->age=age;
		}
	private:
		int age;
};
void stdexcepttest()
{
	try{//try{}中内容栈解旋
		AA a(200);
	}catch(std::out_of_range &ex){
		std::cout<<ex.what()<<std::endl;
	}
}
void func()
{
	throw "adfew";//手动抛异常
}
void func1()
{
	throw Son();//默认构造函数
}
void test()
{
	try{
		func1();//try{}中内容栈解旋
	}catch(Father&f){//父类引用指向子类对象，实际上是子类
		//若catch无法捕获异常对象，会终止程序
		f.print();
	}
}
int main()
{
	Son s;
	Father f;
	f=s;
	f.print();//Father
	Father& ff=s;
	ff.print();//Son
	test();//Son
	try
	{//try{}中内容栈解旋
		func();
	}
	catch(int)
	{
		std::cout<<"throw int"<<std::endl;
	}
	catch(...)//throw unknown
	{
		std::cout<<"throw unknown"<<std::endl;
	}
	stdexcepttest();//年龄不在正常范围内
	ff.print();
	sleep(100);
	return 0;
}
