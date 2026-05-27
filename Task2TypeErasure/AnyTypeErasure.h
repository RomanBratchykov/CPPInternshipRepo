#pragma once

#include <iostream>
#include <stdexcept>
#include <utility>
#include <typeinfo>

namespace ISXAnyType
{
class AnyTypeErasure
{
// TYPEDEFS AND ENUMS
private:
	struct Holder
	{
		virtual ~Holder() = default;
		virtual Holder* clone() const = 0;
		virtual const std::type_info& get_type_info() const = 0;
		virtual void print() const = 0;
	};

	template <typename T>
	struct HolderImpl : Holder
	{
		T m_value;

		HolderImpl(const T& value) : m_value(value)
		{
		}

		Holder* clone() const override
		{
			return new HolderImpl(m_value);
		}

		const std::type_info& get_type_info() const override
		{
			return typeid(T);
		}

		void print() const override
		{
			std::cout << m_value << std::endl;
		}
	};

public:
// LIFECYCLE
	AnyTypeErasure() : m_holder(nullptr)
	{
	}

	template <typename T>
	AnyTypeErasure(const T& value) : m_holder(new HolderImpl<T>(value))
	{
	}

	AnyTypeErasure(const AnyTypeErasure& other) : m_holder(other.m_holder ? other.m_holder->clone() : nullptr)
	{
	}

	AnyTypeErasure(AnyTypeErasure&& other) noexcept : m_holder(std::exchange(other.m_holder, nullptr))
	{
	}

	~AnyTypeErasure()
	{
		delete m_holder;
	}

// OPERATORS
	AnyTypeErasure& operator=(const AnyTypeErasure& other)
	{
		if (this != &other)
		{
			delete m_holder;
			m_holder = other.m_holder ? other.m_holder->clone() : nullptr;
		}
		return *this;
	}

	AnyTypeErasure& operator=(AnyTypeErasure&& other) noexcept
	{
		if (this != &other)
		{
			delete m_holder;
			m_holder = std::exchange(other.m_holder, nullptr);
		}
		return *this;
	}

	template <typename T>
	AnyTypeErasure& operator=(const T& value)
	{
		delete m_holder;
		m_holder = new HolderImpl<T>(value);
		return *this;
	}

// METHODS
	const std::type_info& get_type_info() const
	{
		if (m_holder)
		{
			return m_holder->get_type_info();
		}
		return typeid(void);
	}

	void PrintValue() const
	{
		if (m_holder)
		{
			m_holder->print();
		}
		else
		{
			std::cout << "None" << std::endl;
		}
	}

	void PrintSystemTypeName() const
	{
		if (m_holder)
		{
			std::cout << "System type: " << m_holder->get_type_info().name() << std::endl;
		}
		else
		{
			std::cout << "System type: void (Empty)" << std::endl;
		}
	}

	void SwapTwoObjects(AnyTypeErasure& other)
	{
		std::swap(m_holder, other.m_holder);
	}

	template <typename T>
	T GetAs() const
	{
		if (!m_holder)
		{
			throw std::runtime_error("Bad cast exception: object is empty");
		}

		if (get_type_info() != typeid(T))
		{
			throw std::runtime_error("Bad cast exception: type mismatch");
		}

		return static_cast<HolderImpl<T>*>(m_holder)->m_value;
	}

// DATA MEMBERS
private:
	Holder* m_holder;
};
}