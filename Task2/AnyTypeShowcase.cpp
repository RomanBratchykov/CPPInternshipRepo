#include "AnyType.h"
#include <iostream>
#include <stdexcept>
using namespace ISXAnyType;

//Shows variable types based on enumerator value
void GetTypeName(AnyType& value)
{
	int type = value.get_contained_type();
	switch(type)
	{
		case BooleanType:
            std::cout << "Variable type: Boolean" << std::endl;
            break;
        case IntType:
            std::cout << "Variable type: Int" << std::endl;
            break;
        case DoubleType:
            std::cout << "Variable type: Double" << std::endl;
            break;
        case CharType:
            std::cout << "Variable type: Char" << std::endl;
            break;
        case NoneType:
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
    	AnyType variable_one;
    	std::cout <<"None----------------------------"<<std::endl;
    	GetTypeName(variable_one);
    	variable_one.PrintValue();
    	std::cout <<"Int/1----------------------------"<<std::endl;
    	variable_one = 1;
    	GetTypeName(variable_one);
    	variable_one.PrintValue();
    	std::cout <<"Double/1.5----------------------------"<<std::endl;
    	variable_one = 1.5;
    	GetTypeName(variable_one);
    	variable_one.PrintValue();
    	std::cout <<"Char/a----------------------------"<<std::endl;
    	variable_one = 'a';
    	GetTypeName(variable_one);
    	variable_one.PrintValue();
    	std::cout <<"Bool/false(0)----------------------------"<<std::endl;
    	variable_one = false;
    	GetTypeName(variable_one);
    	variable_one.PrintValue();
    	std::cout <<"Int/10----------------------------"<<std::endl;
    	AnyType variable_two = 10;
    	GetTypeName(variable_two);
    	variable_two.PrintValue();
    	variable_one.SwapTwoObjects(variable_two);
    	std::cout <<"Int/10----------------------------"<<std::endl;
    	GetTypeName(variable_one);
    	variable_one.PrintValue();
    	std::cout <<"Bool/false(0)----------------------------"<<std::endl;
    	GetTypeName(variable_two);
    	variable_two.PrintValue();
    	std::cout <<"Test for To methods----------------------------"<<std::endl;
		std::cout <<"ToInt " << variable_one.ToInt() << std::endl;
    	std::cout <<"ToBool " << variable_two.ToBool() << std::endl;
    }
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	try
	{
		AnyType variable = 10;
		int StoredValueInt = variable.ToInt();
		int StoredValueDouble = variable.ToDouble();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}