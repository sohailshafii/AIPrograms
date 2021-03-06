//https://towardsdatascience.com/how-to-build-your-own-neural-network-from-scratch-in-python-68998a08e4f6

#include "Matrix.h"
#include "Common.h"
#include <cstring>
#include <iostream>

Matrix::Matrix(unsigned int numRows, unsigned int numColumns) {
	this->numRows = numRows;
	this->numColumns = numColumns;

	numElements = numRows*numColumns;
	m = new float[numElements];
	makeIdentity();
}

Matrix::~Matrix() {
	if (m != nullptr) {
		delete[] m;
	}
}

Matrix::Matrix(const Matrix &rhs) {
	allocateAndCopyFrom(rhs);
}

Matrix& Matrix::operator=(const Matrix& rhs) {
	if (&rhs != this) {
		allocateAndCopyFrom(rhs);
	}

	return *this;
}

Matrix Matrix::transpose() const {
	auto transposedNumRows = this->numColumns;
	auto transposedNumColumns = this->numRows;
	Matrix transposed(transposedNumRows,
		transposedNumColumns);

	for (unsigned int row = 0; row < transposedNumRows; row++) {
		for (unsigned int column = 0; column < transposedNumColumns; column++) {
			transposed[row][column] = (*this)(column, row);
		}
	}
	return transposed;
}

void Matrix::makeIdentity() {
	fillWithZeros();
	for (unsigned int rowIndex = 0, oneDimIndex = 0; rowIndex < numRows;
		rowIndex++) {
		for (unsigned int colIndex = 0; colIndex < numColumns;
			colIndex++, oneDimIndex++) {
			if (rowIndex == colIndex) {
				m[oneDimIndex] = 1.0f;
			}
		}
	}
}

void Matrix::fillWithZeros() {
	for (unsigned int elementIndex = 0; elementIndex <
		numElements; elementIndex++) {
		m[elementIndex] = 0.0f;
	}
}

void Matrix::fillWithRandomValues(float min, float max) {
	float range = max - min;
	for (unsigned int elementIndex = 0; elementIndex <
		numElements; elementIndex++) {
		m[elementIndex] = Common::randomUnitValue();
	}
}

void Matrix::print() const {
	for (unsigned int rowIndex = 0, oneDimIndex = 0; rowIndex < numRows;
		rowIndex++) {
		for (unsigned int colIndex = 0; colIndex < numColumns;
			colIndex++, oneDimIndex++) {
			std::cout << m[oneDimIndex] << ", ";
		}
		std::cout << std::endl;
	}
}

void Matrix::allocateAndCopyFrom(const Matrix& other) {
	this->numRows = other.numRows;
	this->numColumns = other.numColumns;

	numElements = numRows*numColumns;
	m = new float[numElements];
	memcpy(m, other.m, numElements * sizeof(float));
}

Matrix Matrix::operator+(const Matrix& rhs) const {
	Matrix sum(rhs.numRows, rhs.numColumns);

	for (unsigned int elementIndex = 0; elementIndex < numElements;
		elementIndex++) {
		sum.m[elementIndex] = this->m[elementIndex]
			+ rhs.m[elementIndex];
	}

	return sum;
}

Matrix Matrix::operator-(const Matrix& rhs) const {
	Matrix diff(rhs.numRows, rhs.numColumns);

	for (unsigned int elementIndex = 0; elementIndex < numElements;
		elementIndex++) {
		diff.m[elementIndex] = this->m[elementIndex]
			- rhs.m[elementIndex];
	}

	return diff;
}

Matrix Matrix::operator*(const Matrix& rhs) const {
	unsigned int resultRows = this->numRows,
		resultCols = rhs.numColumns;
	Matrix product(resultRows, resultCols);
	product.fillWithZeros();

	if (this->numColumns != rhs.numRows) {
		std::cerr << "Can't multiply a (" << numRows
			<< " x " << numColumns << ") matrix "
			<< "with a (" << rhs.numRows <<
			" x " << rhs.numColumns << ") matrix.\n";
	}
	else {
		for (unsigned int row = 0; row < resultRows; row++) {
			auto currRow = product[row];

			for (unsigned int column = 0; column < resultCols;
				column++) {
				for (unsigned int multIndex = 0; multIndex <
					numColumns; multIndex++) {
					currRow[column] += ((*this)(row, multIndex) *
						rhs(multIndex, column));
				}
			}
		}
	}

	return product;
}

Matrix& Matrix::operator+=(const Matrix& rhs) {
	for (unsigned int elementIndex = 0; elementIndex < numElements;
		elementIndex++) {
		m[elementIndex] += rhs.m[elementIndex];
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& rhs) {
	for (unsigned int elementIndex = 0; elementIndex < numElements;
		elementIndex++) {
		m[elementIndex] -= rhs.m[elementIndex];
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& rhs) {
	if (this->numRows != rhs.numRows ||
		this->numColumns != rhs.numColumns) {
		std::cerr << "Can't self multiply a (" << numRows
			<< " x " << numColumns << ") matrix "
			<< "with a (" << rhs.numRows <<
			" x " << rhs.numColumns << ") matrix.\n";
	}
	else {
		*this = *this*rhs;
	}
	return *this;
}

Matrix Matrix::operator+(float scalar) const {
	Matrix sum(*this);

	for (unsigned int elementIndex = 0; elementIndex < numElements;
		elementIndex++) {
		sum.m[elementIndex] = this->m[elementIndex]
			+ scalar;
	}

	return sum;
}

Matrix Matrix::operator-(float scalar) const {
	Matrix diff(*this);

	for (unsigned int elementIndex = 0; elementIndex < numElements;
		elementIndex++) {
		diff.m[elementIndex] = this->m[elementIndex]
			- scalar;
	}

	return diff;
}

Matrix Matrix::operator*(float scalar)  const {
	Matrix product(*this);

	for (unsigned int elementIndex = 0; elementIndex < numElements;
		elementIndex++) {
		product.m[elementIndex] = this->m[elementIndex]
			* scalar;
	}

	return product;
}

Matrix Matrix::operator/(float scalar) const {
	Matrix div(*this);

	for (unsigned int elementIndex = 0; elementIndex < numElements;
		elementIndex++) {
		div.m[elementIndex] = this->m[elementIndex]
			/ scalar;
	}

	return div;
}

Matrix& Matrix::operator+=(float scalar) {
	for (unsigned int elementIndex = 0; elementIndex < numElements;
		elementIndex++) {
		m[elementIndex] += scalar;
	}

	return *this;
}

Matrix& Matrix::operator-=(float scalar) {
	for (unsigned int elementIndex = 0; elementIndex < numElements;
		elementIndex++) {
		m[elementIndex] -= scalar;
	}

	return *this;
}

Matrix& Matrix::operator*=(float scalar) {
	for (unsigned int elementIndex = 0; elementIndex < numElements;
		elementIndex++) {
		m[elementIndex] *= scalar;
	}

	return *this;
}

Matrix& Matrix::operator/=(float scalar) {
	for (unsigned int elementIndex = 0; elementIndex < numElements;
		elementIndex++) {
		m[elementIndex] /= scalar;
	}

	return *this;
}

float* Matrix::getRow(unsigned int rowIndex) {
	return m + rowIndex*numColumns;
}

float* Matrix::operator[](unsigned int rowIndex) {
	return m + rowIndex*numColumns;
}

float& Matrix::operator()(unsigned int row,
	unsigned int col) {
	return m[row*numColumns + col];
}

const float& Matrix::operator()(unsigned int row,
	unsigned int col) const {
	return m[row*numColumns + col];
}
