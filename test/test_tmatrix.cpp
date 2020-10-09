#include "utmatrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix)
{
  TMatrix<int> m(5);

  ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
    TMatrix<int> m(10);
    TMatrix<int> m1(m);
    EXPECT_EQ(1, m == m1);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
    TMatrix<int> m(10);
    TMatrix<int> m1(m);
    EXPECT_NE(&m, &m1);
}

TEST(TMatrix, can_get_size)
{
    TMatrix<int> m(10);
    TMatrix<int> m1(m);
    EXPECT_NE(&m, &m1);
}

TEST(TMatrix, can_set_and_get_element)
{
    TMatrix<int> m(10);
    m[1][1] = 4;
    EXPECT_EQ(4, m[1][1]);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
    TMatrix<int> m(10);
    ASSERT_ANY_THROW(m[2][-2] = 1);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
    TMatrix<int> m(10);
    ASSERT_ANY_THROW(m[2][1000000000000] = 1);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
    TMatrix<int> m(10);
    ASSERT_NO_THROW(m = m);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
    TMatrix<int> m(10), m2(10);
    m[0][0] = 1;
    m2[1][1] = 2;
    m = m2;
    TMatrix<int> m3(10);
    m3[1][1] = 2;
    EXPECT_EQ(1, m3 == m);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
    TMatrix<int> m(10), m2(9);
    m = m2;
    EXPECT_EQ(9, m.GetSize());
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
    TMatrix<int> m(5), m2(7);
    m[0][0] = 1;
    m2[1][1] = 2;
    m = m2;
    TMatrix<int> m3(7);
    m3[1][1] = 2;
    EXPECT_EQ(1, m3 == m);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
    TMatrix<int> m(10), m2(10);
    EXPECT_EQ(1, m == m2);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
    TMatrix<int> m(10);
    EXPECT_EQ(1, m == m);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
    TMatrix<int> m(10), m2(18);
    EXPECT_EQ(0, m == m2);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
    TMatrix<int> m(2), m2(2);
    TMatrix<int> m1(2);
    m[0][0] = 2;
    m2[0][0] = 3;
    m1 = m + m2;
    TMatrix<int> m4(2);
    m4[0][0] = 5;
    EXPECT_EQ(1, m4 == m1);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
    TMatrix<int> m(5), m2(7);
    ASSERT_ANY_THROW(m + m2);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
    TMatrix<int> m(2), m2(2);
    TMatrix<int> m1(2);
    m[0][0] = 13;
    m2[0][0] = 3;
    m1 = (m - m2);
    TMatrix<int> m4(2);
    m4[0][0] = 10;
    EXPECT_EQ(1, m4 == m1);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TMatrix<int> m(5), m2(6);
    ASSERT_ANY_THROW(m - m2);
}

