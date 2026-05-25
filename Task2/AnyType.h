#pragma once
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <utility>

namespace ISXAnyType
{
enum ContainedType
{
	BooleanType,
	IntType,
	DoubleType,
	CharType,
	NoneType
};
class AnyType
{
public:
    AnyType()
	    : m_integer(0)
		, m_current_type(NoneType)
	{};
    AnyType(int integer)
	    : m_integer(integer)
		, m_current_type(IntType)
	{};
    AnyType(char character)
	    : m_character(character)
		, m_current_type(CharType)
	{};
    AnyType(bool boolean)
	    : m_boolean(boolean)
		, m_current_type(BooleanType)
	{};
    AnyType(double doubleValue)
	    : m_double(doubleValue)
		, m_current_type(DoubleType)
	{};
    ~AnyType()
    {

    };

	AnyType& operator=(int integer)
	{
		m_integer = integer;
		m_current_type = IntType;
		return *this;
	}
	AnyType& operator=(bool boolean)
	{
		m_boolean = boolean;
		m_current_type = BooleanType;
		return *this;
	}

	AnyType& operator=(char character)
	{
		m_character = character;
		m_current_type = CharType;
		return *this;
	}

	AnyType& operator=(double doubleValue)
    {
        m_double = doubleValue;
        m_current_type = DoubleType;
        return *this;
    }


    void SwapTwoObjects(AnyType& other)
	{
		std::swap(m_double, other.m_double);
		std::swap(m_current_type, other.m_current_type);
	};

	int ToInt()
	{
		if (m_current_type != IntType)
		{
			throw std::runtime_error("Error: Contained type is not int");
		}
		return m_integer;
	};
	double ToDouble()
	{
		if (m_current_type != DoubleType)
		{
			throw std::runtime_error("Error: Contained type is not double");
		}
		return m_double;
	};
	char ToChar()
	{
		if (m_current_type != CharType)
		{
			throw std::runtime_error("Error: Contained type is not char");
		}
		return m_character;
	};
	bool ToBool()
	{
		if (m_current_type != BooleanType)
		{
			throw std::runtime_error("Error: Contained type is not boolean");
		}
		return m_boolean;
	};
    ContainedType get_contained_type() const
    {
	    return m_current_type;
    }
	void PrintValue()
    {
	    switch (m_current_type)
	    {
	    	case 0:
        		std::cout << (m_boolean ? "true" : "false") << std::endl;
        		break;
	    	case 1:
	    		std::cout << m_double << std::endl;
	    		break;
	    	case 2:
	    		std::cout << m_integer << std::endl;
	    		break;
	    	case 3:
        		std::cout << m_character << std::endl;
        		break;
	    	case 4:
	    		std::cout << "No value" << std::endl;
	    		break;
	    	default:
        		std::cout << "Unknown type" << std::endl;
        		break;
	    }
    }
private:
    union
    {
    	bool m_boolean;
    	char m_character;
    	int m_integer;
    	double m_double;
    };
	ContainedType m_current_type;
};
}