#include <stdexcept>

#include <gtest/gtest.h>

#include "include/legacy/avl.h"

namespace {

class AVLTest : public ::testing::Test {
protected:
	DS::AVL tree;
};

TEST_F(AVLTest, EmptyTreeOperations) {
	EXPECT_FALSE(tree.search(42));
	EXPECT_THROW(tree.getMin(), std::out_of_range);
	EXPECT_THROW(tree.getMax(), std::out_of_range);
}

TEST_F(AVLTest, RootLeftRotationPreservesSearchAndExtrema) {
	tree.insert(1);
	tree.insert(2);
	tree.insert(3);

	EXPECT_TRUE(tree.search(1));
	EXPECT_TRUE(tree.search(2));
	EXPECT_TRUE(tree.search(3));
	EXPECT_FALSE(tree.search(4));
	EXPECT_EQ(tree.getMin(), 1);
	EXPECT_EQ(tree.getMax(), 3);
}

TEST_F(AVLTest, RootRightRotationPreservesSearchAndExtrema) {
	tree.insert(3);
	tree.insert(2);
	tree.insert(1);

	EXPECT_TRUE(tree.search(1));
	EXPECT_TRUE(tree.search(2));
	EXPECT_TRUE(tree.search(3));
	EXPECT_FALSE(tree.search(4));
	EXPECT_EQ(tree.getMin(), 1);
	EXPECT_EQ(tree.getMax(), 3);
}

TEST_F(AVLTest, DoubleRotationPreservesSearchAndExtrema) {
	tree.insert(3);
	tree.insert(1);
	tree.insert(2);

	EXPECT_TRUE(tree.search(1));
	EXPECT_TRUE(tree.search(2));
	EXPECT_TRUE(tree.search(3));
	EXPECT_FALSE(tree.search(4));
	EXPECT_EQ(tree.getMin(), 1);
	EXPECT_EQ(tree.getMax(), 3);
}

TEST_F(AVLTest, RemoveSingleChildNodeKeepsRemainingValuesReachable) {
	for (int value : {10, 5, 15, 12}) {
		tree.insert(value);
	}

	tree.remove(15);

	EXPECT_FALSE(tree.search(15));
	EXPECT_TRUE(tree.search(10));
	EXPECT_TRUE(tree.search(5));
	EXPECT_TRUE(tree.search(12));
	EXPECT_EQ(tree.getMin(), 5);
	EXPECT_EQ(tree.getMax(), 12);

	tree.insert(11);
	EXPECT_TRUE(tree.search(11));
	EXPECT_EQ(tree.getMax(), 12);
}

TEST_F(AVLTest, DuplicateInsertDoesNotCreateExtraNode) {
	tree.insert(10);
	tree.insert(10);

	EXPECT_TRUE(tree.search(10));
	tree.remove(10);
	EXPECT_FALSE(tree.search(10));
	EXPECT_THROW(tree.getMin(), std::out_of_range);
	EXPECT_THROW(tree.getMax(), std::out_of_range);
}

}  // namespace
