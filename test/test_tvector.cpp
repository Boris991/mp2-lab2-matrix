#include "utmatrix.h"

#include <gtest.h>

TEST(TVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TVector<int> v(-5));
}

TEST(TVector, throws_when_create_vector_with_negative_startindex)
{
  ASSERT_ANY_THROW(TVector<int> v(5, -2));
}

TEST(TVector, can_create_copied_vector)
{
  TVector<int> v(10);

  ASSERT_NO_THROW(TVector<int> v1(v));
}

TEST(TVector, copied_vector_is_equal_to_source_one)
{
   TVector<int> v1;
	for (int i = 0; i < v1.GetSize(); i++)
		v1[i] = i;
	TVector<int> v2(v1);
	EXPECT_EQ(v1, v2);
}

TEST(TVector, copied_vector_has_its_own_memory)
{
    TVector<double>tmp1;
    TVector<double>tmp2(tmp1);
    EXPECT_NE(&tmp1,&tmp2);
}

TEST(TVector, can_get_size)
{
  TVector<int> v(4);
  EXPECT_EQ(4, v.GetSize());
}

TEST(TVector, can_get_start_index)
{
  TVector<int> v(4, 2);

  EXPECT_EQ(2, v.GetStartIndex());
}

TEST(TVector, can_set_and_get_element)
{
  TVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TVector, throws_when_set_element_with_negative_index)
{
   TVector<int> v(4);
   EXPECT_ANY_THROW(v[-1]);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
    TVector<int> v(4);
    EXPECT_ANY_THROW(v[4]);
}

TEST(TVector, can_assign_vector_to_itself)
{
    TVector<int> v;
    ASSERT_NO_THROW(v = v);
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
    TVector<int> v1(7);
    TVector<int> v2(7);
    EXPECT_EQ(v2.GetSize(), v1.GetSize());
    for (int i = 0; i < v2.GetSize(); i++)
    {
        v2[i] = i;
    }
    EXPECT_EQ(v2, v1 = v2);
}

TEST(TVector, assign_operator_change_vector_size)
{
    TVector<int> v1(8);
    TVector<int> v2(14);
    EXPECT_NE(v2.GetSize(), v1.GetSize());
    v1 = v2;
    EXPECT_EQ(v1.GetSize(),14);
    EXPECT_EQ(v1.GetSize(), v2.GetSize());
}


TEST(TVector, can_assign_vectors_of_different_size)
{
    TVector<int> v1(7);
    TVector<int> v2(10);
    EXPECT_NE(v2.GetSize(), v1.GetSize());
    for (int i = 0; i < v1.GetSize(); i++)
    {
        v1[i] = i;
    }
    EXPECT_EQ(v1, v2 = v1);
}

TEST(TVector, compare_equal_vectors_return_true)
{
  TVector<int> v1;
	for (int i = 0; i < v1.GetSize(); i++)
	{
		v1[i] = i;
	}
	TVector<int> v2(v1);
	EXPECT_EQ(true, v1 == v2);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
    TVector<int> v1;
    for (int i = 0; i < v1.GetSize(); i++)
    {
        v1[i] = i;
    }
    EXPECT_EQ(true, v1 == v1);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
    TVector<int> v1(8);
    TVector<int> v2(21);
    EXPECT_NE(v2.GetSize(), v1.GetSize());
    EXPECT_EQ(true, v1 != v2);
}

TEST(TVector, can_add_scalar_to_vector)
{
    TVector<int> v1(8);
    TVector<int> v2(8);
    for (int i = 0; i < v1.GetSize(); i++)
    {
        v1[i] = i + 17;
        v2[i] = i;
    }
    EXPECT_EQ(v1, v2 + 17);
}

TEST(TVector, can_subtract_scalar_from_vector)
{
    TVector<int> v1(8);
    TVector<int> v2(8);
    for (int i = 0; i < v1.GetSize(); i++)
    {
        v1[i] = i - 17;
        v2[i] = i;
    }
    EXPECT_EQ(v1, v2 - 17);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
    TVector<int> v1(8);
    TVector<int> v2(8);
    for (int i = 0; i < v1.GetSize(); i++)
    {
        v1[i] = i * 17;
        v2[i] = i;
    }
    EXPECT_EQ(v1, v2 * 17);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
    TVector<int> v1(56);
    TVector<int> v2(56);
    TVector<int> v3(56);
    for (int i = 0; i < v1.GetSize(); i++)
    {
        v1[i] = i * 19;
        v2[i] = i + 19;
        v3[i]= (i * 19)+(i + 19);
    }
    EXPECT_EQ(v3, v1 + v2);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
    TVector<int> v1(56);
    TVector<int> v2(34);
    for (int i = 0; i < v1.GetSize(); i++)
    {
        v1[i] = i * 19;
    }
    for (int i = 0; i < v2.GetSize(); i++)
    {
        v2[i] = i + 19;
    }
    ASSERT_ANY_THROW(v1 + v2);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
    TVector<int> v1(56);
    TVector<int> v2(56);
    TVector<int> v3(56);
    for (int i = 0; i < v1.GetSize(); i++)
    {
        v1[i] = i * 19;
        v2[i] = i + 19;
        v3[i] = (i * 19) - (i + 19);
    }
    EXPECT_EQ(v3, v1 - v2);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
    TVector<int> v1(56);
    TVector<int> v2(34);
    for (int i = 0; i < v1.GetSize(); i++)
    {
        v1[i] = i * 19;
    }
    for (int i = 0; i < v2.GetSize(); i++)
    {
        v2[i] = i + 19;
    }
    ASSERT_ANY_THROW(v1 - v2);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
    TVector<int> v1(56);
    TVector<int> v2(56);
    int s=0;
    for (int i = 0; i < v1.GetSize(); i++)
    {
        v1[i] = i + 4;
        v2[i] = i - 4;
        s+= (i + 4) * (i - 4);
    }
    EXPECT_EQ(s, v1 * v2);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
    TVector<int> v1(56);
    TVector<int> v2(34);
    for (int i = 0; i < v1.GetSize(); i++)
    {
        v1[i] = i * 19;
    }
    for (int i = 0; i < v2.GetSize(); i++)
    {
        v2[i] = i + 19;
    }
    ASSERT_ANY_THROW(v1 * v2);
}

