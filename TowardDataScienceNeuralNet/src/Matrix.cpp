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
	MakeIdentity();
}

Matrix::~Matrix() {
	if (m != nullptr) {
		delete[] m;
	}
}

Matrix::Matrix(Matrix const & rhs) {
	AllocateAndCopyFrom(rhs);
}

Matrix& Matrix::operator=(Matrix const & rhs) {
	if (&rhs != this) {
		AllocateAndCopyFrom(rhs);
	}

	return *this;
}

Matrix Matrix::Transpose() const {
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

void Matrix::MakeIdentity() {
	FillWithZeros();
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

void Matrix::FillWithZeros() {
	for (unsigned int elementIndex = 0; elementIndex <
		numElements; elementIndex++) {
		m[elementIndex] = 0.0f;
	}
}

void Matrix::FillWithRandomValues(float min, float max) {
	float range = max - min;
	for (unsigned int elementIndex = 0; elementIndex <
		numElements; elementIndex++) {
		m[elementIndex] = Common::randomUnitValue();
	}
}

void Matrix::Print() const {
	for (unsigned int rowIndex = 0, oneDimIndex = 0; rowIndex < numRows;
		rowIndex++) {
		for (unsigned int colIndex = 0; colIndex < numColumns;
			colIndex++, oneDimIndex++) {
			std::cout << m[oneDimIndex] << ", ";
		}
		std::cout << std::endl;
	}
}

void Matrix::AllocateAndCopyFrom(Matrix const & other) {
	this->numRows = other.numRows;
	this->numColumns = other.numColumns;

	numElements = numRows*numColumns;
	m = new float[numElements];
	memcpy(m, other.m, numElements * sizeof(float));
}

Matrix Matrix::operator+(Matrix const & rhs) const {
	Matrix sum(rhs.numRows, rhs.numColumns);

	for (unsigned int elementIndex = 0; elementIndex < numElements;
		elementIndex++) {
		sum.m[elementIndex] = this->m[elementIndex]
			+ rhs.m[elementIndex];
	}

	return sum;
}

Matrix Matrix::operator-(Matrix const & rhs) const {
	Matrix diff(rhs.numRows, rhs.numColumns);

	for (unsigned int elementIndex = 0; elementIndex < numElements;
		elementIndex++) {
		diff.m[elementIndex] = this->m[elementIndex]
			- rhs.m[elementIndex];
	}

	return diff;
}

Matrix Matrix::operator*(Matrix const & rhs) const {
	unsigned int resultRows = this->numRows,
		resultCols = rhs.numColumns;
	Matrix product(resultRows, resultCols);
	product.FillWithZeros();

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

Matrix& Matrix::operator+=(Matrix const & rhs) {
	for (unsigned int elementIndex = 0; elementIndex < numElements;
		elementIndex++) {
		m[elementIndex] += rhs.m[elementIndex];
	}
	return *this;
}

Matrix& Matrix::operator-=(Matrix const & rhs) {
	for (unsigned int elementIndex = 0; elementIndex < numElements;
		elementIndex++) {
		m[elementIndex] -= rhs.m[elementIndex];
	}
	return *this;
}

Matrix& Matrix::operator*=(Matrix const & rhs) {
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

float* Matrix::GetRow(unsigned int rowIndex) {
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
