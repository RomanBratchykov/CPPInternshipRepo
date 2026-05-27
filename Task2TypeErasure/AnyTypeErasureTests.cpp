#include <gtest/gtest.h>
#include "AnyTypeErasure.h"
#include <typeinfo>
#include <stdexcept>

using namespace ISXAnyType;

TEST(AnyTypeErasureTests, DefaultConstructorIsEmpty) {
    AnyTypeErasure any;
    EXPECT_EQ(any.get_type_info(), typeid(void));
    EXPECT_THROW(any.GetAs<int>(), std::runtime_error);
    EXPECT_THROW(any.GetAs<double>(), std::runtime_error);
}

TEST(AnyTypeErasureTests, IntValueTypeSafety) {
    AnyTypeErasure any(42);
    EXPECT_EQ(any.get_type_info(), typeid(int));
    EXPECT_EQ(any.GetAs<int>(), 42);

    EXPECT_THROW(any.GetAs<double>(), std::runtime_error);
    EXPECT_THROW(any.GetAs<char>(), std::runtime_error);
    EXPECT_THROW(any.GetAs<bool>(), std::runtime_error);
}

TEST(AnyTypeErasureTests, DoubleValueTypeSafety) {
    AnyTypeErasure any(3.1415);
    EXPECT_EQ(any.get_type_info(), typeid(double));
    EXPECT_EQ(any.GetAs<double>(), 3.1415);

    // Перевірка type safety
    EXPECT_THROW(any.GetAs<int>(), std::runtime_error);
    EXPECT_THROW(any.GetAs<float>(), std::runtime_error);
}

TEST(AnyTypeErasureTests, CharValueTypeSafety) {
    AnyTypeErasure any('A');
    EXPECT_EQ(any.get_type_info(), typeid(char));
    EXPECT_EQ(any.GetAs<char>(), 'A');

    // Перевірка type safety
    EXPECT_THROW(any.GetAs<int>(), std::runtime_error);
}

TEST(AnyTypeErasureTests, BoolValueTypeSafety) {
    AnyTypeErasure any(true);
    EXPECT_EQ(any.get_type_info(), typeid(bool));
    EXPECT_EQ(any.GetAs<bool>(), true);

    // Перевірка type safety
    EXPECT_THROW(any.GetAs<int>(), std::runtime_error);
}

TEST(AnyTypeErasureTests, CopyConstructorPreservesType) {
    AnyTypeErasure original(100);
    AnyTypeErasure copy(original);

    EXPECT_EQ(copy.get_type_info(), typeid(int));
    EXPECT_EQ(copy.GetAs<int>(), 100);
    copy = 200;
    EXPECT_EQ(original.GetAs<int>(), 100);
    EXPECT_EQ(copy.GetAs<int>(), 200);
}

TEST(AnyTypeErasureTests, MoveConstructorTransfersType) {
    AnyTypeErasure original(9.99);
    AnyTypeErasure moved(std::move(original));

    EXPECT_EQ(original.get_type_info(), typeid(void));
    EXPECT_EQ(moved.get_type_info(), typeid(double));
    EXPECT_EQ(moved.GetAs<double>(), 9.99);
}

TEST(AnyTypeErasureTests, CopyAssignmentChangesTypeSafe) {
    AnyTypeErasure a(10);
    AnyTypeErasure b(20.5);

    b = a;
    EXPECT_EQ(b.get_type_info(), typeid(int));
    EXPECT_EQ(a.GetAs<int>(), 10);
    EXPECT_EQ(b.GetAs<int>(), 10);

    EXPECT_THROW(b.GetAs<double>(), std::runtime_error);
}

TEST(AnyTypeErasureTests, MoveAssignmentChangesTypeSafe) {
    AnyTypeErasure a('Z');
    AnyTypeErasure b(3.14);

    b = std::move(a);
    EXPECT_EQ(a.get_type_info(), typeid(void));
    EXPECT_EQ(b.get_type_info(), typeid(char));
    EXPECT_EQ(b.GetAs<char>(), 'Z');

    EXPECT_THROW(b.GetAs<double>(), std::runtime_error);
}

TEST(AnyTypeErasureTests, TypeReassignmentIsTypeSafe) {
    AnyTypeErasure any(123);
    EXPECT_EQ(any.GetAs<int>(), 123);

    any = 3.14;
    EXPECT_EQ(any.get_type_info(), typeid(double));
    EXPECT_EQ(any.GetAs<double>(), 3.14);

    EXPECT_THROW(any.GetAs<int>(), std::runtime_error);
}

TEST(AnyTypeErasureTests, SwapObjectsSwapsTypesSafely) {
    AnyTypeErasure a(10);
    AnyTypeErasure b('C');

    a.SwapTwoObjects(b);

    EXPECT_EQ(a.get_type_info(), typeid(char));
    EXPECT_EQ(a.GetAs<char>(), 'C');
    EXPECT_THROW(a.GetAs<int>(), std::runtime_error);

    EXPECT_EQ(b.get_type_info(), typeid(int));
    EXPECT_EQ(b.GetAs<int>(), 10);
    EXPECT_THROW(b.GetAs<char>(), std::runtime_error);
}