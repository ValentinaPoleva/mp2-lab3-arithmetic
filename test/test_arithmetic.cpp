#include <gtest.h>
#include <iostream>
#include "arithmetic.h"


TEST(TArithmetictic, can_create_arithmetic)
{
  string str = "123";
  ASSERT_NO_THROW(TArithmetic(srt));
}

TEST(TArithmetictic, can_divide_string_on_tokens)
{
  string str = "(1+2)*3";
  string strT = "( 1 + 2 ) * 3 ";
  TArithmetic Ar(str);
  Ar.DivideIntoTokens();
  EXPECT_EQ(Ar.WriteStr(),strT);
}

TEST(TArithmetictic, can_divide_string_on_tokens_1)
{
  string str = "(1+a-2)*b/123";
  string strT = "( 1 + a - 2 ) * b / 123 ";
  TArithmetic Ar(str);
  Ar.DivideIntoTokens();
  EXPECT_EQ(Ar.WriteStr(),strT);
}

TEST(TArithmetictic, can_divide_string_on_tokens_2)
{
  string str = "(1+a-2)*b/12.3";
  string strT = "( 1 + a - 2 ) * b / 12.3 ";
  TArithmetic Ar(str);
  Ar.DivideIntoTokens();
  EXPECT_EQ(Ar.WriteStr(),strT);
}

/*---------------bracket block-------------------------------*/
TEST(TArithmetictic, can_check_bracket_1){
  string str = ")";
  TArithmetic Ar(str);
  ASSERT_ANY_THROW(Ar.CheckBrackets());
}
TEST(TArithmetictic, can_check_bracket_2){
  string str = "(";
  TArithmetic Ar(str);
  ASSERT_ANY_THROW(Ar.CheckBrackets());
}
TEST(TArithmetictic, can_check_bracket_3){
  string str = "(()";
  TArithmetic Ar(str);
  ASSERT_ANY_THROW(Ar.CheckBrackets());
}
TEST(TArithmetictic, can_check_bracket_4){
  string str = "(()))";
  TArithmetic Ar(str);
  ASSERT_ANY_THROW(Ar.CheckBrackets());
}
TEST(TArithmetictic, can_check_bracket_5){
  string str = "( 1 + a - 2 ) * b / 123 ";
  TArithmetic Ar(str);
  ASSERT_NO_THROW(Ar.CheckBrackets());
}
/*------------------end-----------------------------------------*/

TEST(TArithmetictic, can_consider_postfix_0)
{
  string str = "(1+2)";
  TArithmetic Ar(str);
  double s = Ar.PolishNotation();
  EXPECT_EQ(s,3);
}

TEST(TArithmetictic, can_consider_postfix_1)
{
  string str = "1+2";
  TArithmetic Ar(str);
  double s = Ar.PolishNotation();
  EXPECT_EQ(s,3);
}

TEST(TArithmetictic, can_consider_postfix_2)
{
  string str = "2*3+1";
  TArithmetic Ar(str);
  double s = Ar.PolishNotation();
  EXPECT_EQ(s,7);
}

TEST(TArithmetictic, can_consider_postfix_3)
{
  string str = "(8+2*5)/(1+3*2-4)";
  TArithmetic Ar(str);
  double s = Ar.PolishNotation();
  EXPECT_EQ(s,6);
}

TEST(TArithmetictic, can_consider_postfix_4)
{
  string str = "((8+2*5)/(1+3*2-4))+(1-3)*2";
  TArithmetic Ar(str);
  double s = Ar.PolishNotation();
  EXPECT_EQ(s,2);
}

TEST(TArithmetictic, can_consider_postfix_5)
{
  string str = "((8+2*5)/(1+3*2-4))+(1-3)*2.5";
  TArithmetic Ar(str);
  double s = Ar.PolishNotation();
  EXPECT_EQ(s,1);
}

TEST(TArithmetictic, can_consider_postfix_var)
{
  string str = "((8+b*5)/(1+3*b-4))+(1-3)*a";
  int n = 2;
  char name[2] = {'a','b'};
  double val[2] = {2.5, 2};
  TArithmetic Ar(str);
  Ar.SetVars(n,name,val);
  double s = Ar.PolishNotation();
  EXPECT_EQ(s,1);
}