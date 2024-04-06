/*
 C++类型转换：
 1、静态类型转换：基础类型转换、子类指针/引用转父类指针/引用
 2、动态类型转换：发生多态时，子类指针转为父类指针
 3、常量转换：常量指针/引用转为普通指针/引用，或者反之
*/
#include <iostream>
class Father
{
	private:
		int a;
	public:
		virtual void func()
		{
			std::cout<<"I am Father"<<std::endl;
		}
};

class Son:public Father
{
	private:
		double b;
	public:
		void func() override
		{
			std::cout<<"I am Son"<<std::endl;
		}
};

int main()
{
	char c;//静态转换之基本类型转换
	double d=static_cast<double>(c);

	Son* s;//静态转换之子类指针转父类指针
	Father* f=static_cast<Father*>(s);

	Son s1;//静态转换之子类引用转父类引用
	Son &ref_s=s1;
	Father &ref_f=static_cast<Father&>(ref_s);
	ref_f.func();//I am Son

	Son* ss;//动态转换：发生多态时，子类指针转为父类指针
	Father* ff=dynamic_cast<Father*>(ss);

	const int* p=nullptr;
	int* newp=const_cast<int*>(p);

	int* pp=nullptr;
	const int* newpp=const_cast<const int*>(pp);

	Son sss;
	Father fff=sss;
	fff.func();//I am Father

	Son ssss;
	Father& ffff=ssss;
	ffff.func();//I am Son

	Father* fffff=new Son;;
	fffff->func();//I am Son
	delete fffff;
	return 0;
}
