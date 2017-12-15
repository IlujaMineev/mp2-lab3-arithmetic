// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(Stack, can_create_stack)
{
	EXPECT_NO_THROW(Stack<int>(3));
}

TEST(Stack, can_empty)
{
	Stack<int> A(3);
	A.push(3);
	EXPECT_EQ(false, A.empty());
}

TEST(Stack, new_stack_is_empty)
{
	Stack<int> A(3);
	EXPECT_EQ(true, A.empty());
}

TEST(Stack, cant_create_stack_with_negative_size)
{
	EXPECT_ANY_THROW(Stack<int>(-3));
}

TEST(Stack, can_push)
{
	Stack<int> A(3);
	EXPECT_NO_THROW(A.push(2));
}

TEST(Stack, can_pop)
{
	Stack<int> A(3);
	A.push(4);
	EXPECT_EQ(4, A.pop());
}

TEST(Stack, can_pick)
{
	Stack<int> A(3);
	A.push(4);
	EXPECT_EQ(4, A.peek());
}
