#include <gtest/gtest.h>
#include "AnyType.h"
#include <string>

using ISXAnyType::AnyType;
using ISXAnyType::BooleanType;
using ISXAnyType::IntType;
using ISXAnyType::DoubleType;
using ISXAnyType::CharType;
using ISXAnyType::NoneType;

namespace
{
std::string CapturePrint(AnyType& value)
{
    testing::internal::CaptureStdout();
    value.PrintValue();
    return testing::internal::GetCapturedStdout();
}
}

TEST(AnyTypeConstructors, DefaultIsNone)
{
    AnyType value;
    EXPECT_EQ(value.get_contained_type(), NoneType);
    EXPECT_EQ(CapturePrint(value), "No value\n");
}

TEST(AnyTypeConstructors, IntConstructor)
{
    AnyType value(42);
    EXPECT_EQ(value.get_contained_type(), IntType);
    EXPECT_EQ(value.ToInt(), 42);
    EXPECT_EQ(CapturePrint(value), "42\n");
}

TEST(AnyTypeConstructors, DoubleConstructor)
{
    AnyType value(1.5);
    EXPECT_EQ(value.get_contained_type(), DoubleType);
    EXPECT_DOUBLE_EQ(value.ToDouble(), 1.5);
    EXPECT_EQ(CapturePrint(value), "1.5\n");
}

TEST(AnyTypeConstructors, CharConstructor)
{
    AnyType value('a');
    EXPECT_EQ(value.get_contained_type(), CharType);
    EXPECT_EQ(value.ToChar(), 'a');
    EXPECT_EQ(CapturePrint(value), "a\n");
}

TEST(AnyTypeConstructors, BoolConstructor)
{
    AnyType value(true);
    EXPECT_EQ(value.get_contained_type(), BooleanType);
    EXPECT_EQ(value.ToBool(), true);
    EXPECT_EQ(CapturePrint(value), "1\n");
}

TEST(AnyTypeAssignments, AssignInt)
{
    AnyType value;
    value = 7;
    EXPECT_EQ(value.get_contained_type(), IntType);
    EXPECT_EQ(value.ToInt(), 7);
}

TEST(AnyTypeAssignments, AssignDouble)
{
    AnyType value;
    value = 2.25;
    EXPECT_EQ(value.get_contained_type(), DoubleType);
    EXPECT_DOUBLE_EQ(value.ToDouble(), 2.25);
}

TEST(AnyTypeAssignments, AssignChar)
{
    AnyType value;
    value = 'z';
    EXPECT_EQ(value.get_contained_type(), CharType);
    EXPECT_EQ(value.ToChar(), 'z');
}

TEST(AnyTypeAssignments, AssignBool)
{
    AnyType value;
    value = false;
    EXPECT_EQ(value.get_contained_type(), BooleanType);
    EXPECT_EQ(value.ToBool(), false);
}

TEST(AnyTypeConversions, ToIntThrowsOnWrongType)
{
    AnyType value(1.5);
    EXPECT_THROW(value.ToInt(), std::runtime_error);
}

TEST(AnyTypeConversions, ToDoubleThrowsOnWrongType)
{
    AnyType value(3);
    EXPECT_THROW(value.ToDouble(), std::runtime_error);
}

TEST(AnyTypeConversions, ToCharThrowsOnWrongType)
{
    AnyType value(true);
    EXPECT_THROW(value.ToChar(), std::runtime_error);
}

TEST(AnyTypeConversions, ToBoolThrowsOnWrongType)
{
    AnyType value('b');
    EXPECT_THROW(value.ToBool(), std::runtime_error);
}

TEST(AnyTypeCopying, CopyConstructorCopiesValue)
{
    AnyType original(99);
    AnyType copy(original);
    EXPECT_EQ(copy.get_contained_type(), IntType);
    EXPECT_EQ(copy.ToInt(), 99);
}

TEST(AnyTypeCopying, CopyAssignmentCopiesValue)
{
    AnyType original('x');
    AnyType copy;
    copy = original;
    EXPECT_EQ(copy.get_contained_type(), CharType);
    EXPECT_EQ(copy.ToChar(), 'x');
}

TEST(AnyTypeMoving, MoveAssignmentPreservesValue)
{
    AnyType original(4.75);
    AnyType target;
    target = std::move(original);
    EXPECT_EQ(target.get_contained_type(), DoubleType);
    EXPECT_DOUBLE_EQ(target.ToDouble(), 4.75);
}

TEST(AnyTypeSwap, SwapsDifferentTypes)
{
    AnyType left(10);
    AnyType right(true);
    left.SwapTwoObjects(right);

    EXPECT_EQ(left.get_contained_type(), BooleanType);
    EXPECT_EQ(left.ToBool(), true);
    EXPECT_EQ(right.get_contained_type(), IntType);
    EXPECT_EQ(right.ToInt(), 10);
}

TEST(AnyTypeSwap, SwapsWithNone)
{
    AnyType left;
    AnyType right('q');
    left.SwapTwoObjects(right);

    EXPECT_EQ(left.get_contained_type(), CharType);
    EXPECT_EQ(left.ToChar(), 'q');
    EXPECT_EQ(right.get_contained_type(), NoneType);
}

TEST(AnyTypeDestroy, ResetsToNone)
{
    AnyType value(123);
    value.Destroy();
    EXPECT_EQ(value.get_contained_type(), NoneType);
    EXPECT_EQ(CapturePrint(value), "No value\n");
}
