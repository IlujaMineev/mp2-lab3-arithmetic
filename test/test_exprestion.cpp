// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "Exprestion.h"

TEST(Exprestion, can_create_the_object_exprestion)
{
	EXPECT_NO_THROW(Exprestion("example"));
}

TEST(Exprestion, fix_spaces_and_unar_minus)
{
	Exprestion s("- 1+  2");
	string t = "0-1+2";
	ASSERT_EQ(t, s.GetExpr());
}



