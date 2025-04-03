#pragma once
#include <stdexcept>
#include <algorithm>

template <typename T> class Table {
public:

	Table() : _numRows(0), _numCols(0), arr(nullptr) {
	};

	Table(int numRows, int numCols) : _numRows(numRows), _numCols(numCols) {
		arr = new T[numRows * numCols]{};
	};

	Table(const Table& other) : _numRows(other._numRows), _numCols(other._numCols) {
		arr = new T[_numRows * _numCols];
		std::copy(other.arr, other.arr + (_numRows * _numCols), arr);
	};

	~Table() { delete[] arr; };

	Table& operator=(const Table& other) {
		if (this != &other) {
			delete[] arr;
			_numRows = other._numRows;
			_numCols = other._numCols;
			arr = new T[_numRows * _numCols];
			std::copy(other.arr, other.arr + (_numRows * _numCols), arr);
		}
		return *this;
	};

	Table(Table&& other) noexcept : _numRows(other._numRows), _numCols(other._numCols), arr(other.arr) {
		other.arr = nullptr;
		other._numRows = 0;
		other._numCols = 0;
	};

	Table& operator=(Table&& other) noexcept {
		if (this != &other) {
			delete[] arr;
			_numRows = other._numRows;
			_numCols = other._numCols;
			arr = other.arr;
			other.arr = nullptr;
			other._numRows = 0;
			other._numCols = 0;
		}
		return *this;
	};

	int numRows() const {
		return _numRows;
	};

	int numCols() const {
		return _numCols;
	};

	T& at(int rowNum, int colNum) const {
		if (rowNum < 0 || rowNum >= _numRows || colNum < 0 || colNum >= _numCols) {
			throw std::out_of_range("Index out of range");
		}
		return arr[rowNum * _numCols + colNum];
	};

	T& at(int rowNum, int colNum) {
		if (rowNum < 0 || rowNum >= _numRows || colNum < 0 || colNum >= _numCols) {
			throw std::out_of_range("Index out of range");
		}
		return arr[rowNum * _numCols + colNum];
	};

	T* data() {
		return arr;
	}

	const T* data() const {
		return arr;
	}

	void resize(int newRows, int newCols) {
		Table<T> temp(newRows, newCols);
		int minRows = std::min(newRows, _numRows);
		int minCols = std::min(newCols, _numCols);
		for (int r = 0; r < minRows; ++r) {
			for (int c = 0; c < minCols; ++c) {
				temp.at(r, c) = std::move(at(r, c));
			}
		}
		*this = std::move(temp);
	};

	T* operator[](int rowNum) {
		return arr + rowNum * _numCols;
	};

	const T* operator[](int rowNum) const {
		return arr + rowNum * _numCols;
	};

private:
	T* arr;
	int _numRows;
	int _numCols;
};