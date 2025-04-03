#include "gtest/gtest.h"
#include "table.hpp"
#include <vld.h>


TEST(Constructor, DefaultConstructorInt) {
	Table<int> table;

	int rows = table.numRows();
	int cols = table.numCols();

	EXPECT_EQ(rows, 0);
	EXPECT_EQ(cols, 0);
};

TEST(Constructor, DefaultConstructorString) {
	Table<std::string> table;

	int rows = table.numRows();
	int cols = table.numCols();

	EXPECT_EQ(rows, 0);
	EXPECT_EQ(cols, 0);
};

TEST(Constructor, DefaultConstructorDouble) {
	Table<double> table;

	int rows = table.numRows();
	int cols = table.numCols();

	EXPECT_EQ(rows, 0);
	EXPECT_EQ(cols, 0);
};

TEST(Constructor, ValueConstructorInt) {
	Table<int> table(3, 5);

	int rows = table.numRows();
	int cols = table.numCols();

	EXPECT_EQ(rows, 3);
	EXPECT_EQ(cols, 5);
};

TEST(Constructor, ValueConstructorString) {
	Table<std::string> table(3, 5);

	int rows = table.numRows();
	int cols = table.numCols();

	EXPECT_EQ(rows, 3);
	EXPECT_EQ(cols, 5);
};

TEST(Constructor, ValueConstructorBool) {
	Table<bool> table(3, 5);

	int rows = table.numRows();
	int cols = table.numCols();

	EXPECT_EQ(rows, 3);
	EXPECT_EQ(cols, 5);
};

TEST(Access, ConstAt) {
	const Table<int> t(3, 5);

	t.at(1, 3) = 10;
	t.at(1, 4) = 14;

	EXPECT_EQ(t.at(1, 3), 10);
	EXPECT_EQ(t.at(1, 4), 14);
	EXPECT_THROW(t.at(3, 5), std::out_of_range);
};

TEST(Access, NonConstAt) {
	Table<int> t(3, 5);

	t.at(1, 3) = 10;
	t.at(1, 4) = 14;

	EXPECT_EQ(t.at(1, 3), 10);
	EXPECT_EQ(t.at(1, 4), 14);
	EXPECT_THROW(t.at(3, 5), std::out_of_range);
};

TEST(Access, Data) {
	Table<int> t(3, 5);
	int* dataPtr = t.data();

	EXPECT_NE(dataPtr, nullptr);
};

TEST(Access, ConstData) {
	const Table<int> t(3, 5);
	const int* dataPtr = t.data();

	EXPECT_NE(dataPtr, nullptr);
};

TEST(Copy, CopyConstructor) {
	Table<int> t(3, 5);
	t.at(1, 3) = 10;
	Table<int> copy = t;

	EXPECT_EQ(copy.numRows(), 3);
	EXPECT_EQ(copy.numCols(), 5);
	EXPECT_EQ(copy.at(1, 3), 10);
};

TEST(Copy, CopyAssignment) {
	Table<int> t(3, 5);
	t.at(1, 3) = 10;
	Table<int> copy;
	copy = t;

	EXPECT_EQ(copy.numRows(), 3);
	EXPECT_EQ(copy.numCols(), 5);
	EXPECT_EQ(copy.at(1, 3), 10);
};

TEST(Move, MoveConstructor) {
	Table<int> t(3, 5);
	t.at(1, 3) = 10;
	Table<int> moved = std::move(t);

	EXPECT_EQ(moved.numRows(), 3);
	EXPECT_EQ(moved.numCols(), 5);
	EXPECT_EQ(moved.at(1, 3), 10);
};

TEST(Move, MoveAssignment) {
	Table<int> t(3, 5);
	t.at(1, 3) = 10;
	Table<int> moved;
	moved = std::move(t);

	EXPECT_EQ(moved.numRows(), 3);
	EXPECT_EQ(moved.numCols(), 5);
	EXPECT_EQ(moved.at(1, 3), 10);
};

TEST(Resize, Resize) {
	Table<int> t(3, 5);
	t.at(1, 3) = 10;
	t.resize(4, 6);

	EXPECT_EQ(t.numRows(), 4);
	EXPECT_EQ(t.numCols(), 6);
	EXPECT_EQ(t.at(1, 3), 10);
};

TEST(Access, RowOperator) {
	Table<int> t(3, 5);
	t.at(1, 3) = 10;

	int* row = t[1];
	EXPECT_EQ(row[3], 10);
};
