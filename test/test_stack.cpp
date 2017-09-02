#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> v(5));
}

TEST(TStack, cant_create_too_large_stack)
{
  ASSERT_ANY_THROW(TStack<int> v(MAX_STACK_SIZE + 1));
}

TEST(TStack, throws_when_create_stack_with_negative_length)
{
  ASSERT_ANY_THROW(TStack<int> v(-5));
}

TEST(TStack, can_create_copied_stack)
{
  TStack<int> v(10);

  ASSERT_NO_THROW(TStack<int> v1(v));
}

TEST(TStack, can_set_and_get_elem)
{
  TStack<int> v(10);

  v.SetElem(1);

  EXPECT_EQ(1, v.GetElem());
} 

TEST(TStack, can_check_empty_stack)
{
  TStack<int> v(10);

  EXPECT_EQ(1, v.IsEmpty());
} 

TEST(TStack, can_check_full_stack)
{
  TStack<int> v(2);

  v.SetElem(1);
  v.SetElem(1);

  EXPECT_EQ(1, v.IsFull());
} 

TEST(TStack, assert_when_stack_overflow)
{
  TStack<int> v(2);

  v.SetElem(1);
  v.SetElem(1);

  ASSERT_ANY_THROW(v.SetElem(8));
} 

TEST(TStack, assert_when_stack_empty)
{
  TStack<int> v(2);

  ASSERT_ANY_THROW(v.GetElem());
} 

