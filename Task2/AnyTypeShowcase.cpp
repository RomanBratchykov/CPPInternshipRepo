#include "AnyType.h"
#include <iostream>
#include <stdexcept>
using namespace ISXAnyType;

void GetTypeName(AnyType& value)
{
	int type = value.get_contained_type();
	switch(type)
	{
		case 0:
            std::cout << "Variable type: Boolean" << std::endl;
            break;
        case 1:
            std::cout << "Variable type: Int" << std::endl;
            break;
        case 2:
            std::cout << "Variable type: Double" << std::endl;
            break;
        case 3:
            std::cout << "Variable type: Char" << std::endl;
            break;
        case 4:
            std::cout << "No type" << std::endl;
            break;
        default:
            std::cout << "Unknown type" << std::endl;
	}
}
int main()
{
    try
    {
    	AnyType a;
    	std::cout <<"None----------------------------"<<std::endl;
    	GetTypeName(a);
    	a.PrintValue();
    	std::cout <<"Int/1----------------------------"<<std::endl;
    	a = 1;
    	GetTypeName(a);
    	a.PrintValue();
    	std::cout <<"Double/1.5----------------------------"<<std::endl;
    	a = 1.5;
    	GetTypeName(a);
    	a.PrintValue();
    	std::cout <<"Char/a----------------------------"<<std::endl;
    	a = 'a';
    	GetTypeName(a);
    	a.PrintValue();
    	std::cout <<"Bool/false(0)----------------------------"<<std::endl;
    	a = false;
    	GetTypeName(a);
    	a.PrintValue();
    	std::cout <<"Int/10----------------------------"<<std::endl;
    	AnyType b = 10;
    	GetTypeName(b);
    	b.PrintValue();
    	a.SwapTwoObjects(b);
    	std::cout <<"Int/10----------------------------"<<std::endl;
    	GetTypeName(a);
    	a.PrintValue();
    	std::cout <<"Bool/false(0)----------------------------"<<std::endl;
    	GetTypeName(b);
    	b.PrintValue();

    }
	catch (...)    {}
	return 0;
}