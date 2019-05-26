
#include "Matrix.h"
#include <cstring>

// TODO

Matrix::Matrix(unsigned int numRows, unsigned int numColumns) {
	this->numRows = numRows;
	this->numColumns = numColumns;

	numElements = numRows*numColumns;
	m = new float[numElements];
	makeIdentity();
}

Matrix::~Matrix() {
	if (m != nullptr) {
		delete [] m;
	}
}

Matrix::Matrix(const Matrix &rhs) {
	AllocateAndCopyFrom(rhs);
}

Matrix& Matrix::operator=(const Matrix& rhs) {
	if (&rhs != this) {
		AllocateAndCopyFrom(rhs);
	}

	return *this;
}

Matrix Matrix::transpose() const {
  	Matrix transposed(*this);
  	// TODO
  	return transposed;	
}

void Matrix::makeIdentity() {
	fillWithZeros();
	for (int rowIndex = 0; rowIndex < numRows; rowIndex++) {
		int oneDimIndex = rowIndex*numColumns + rowIndex;
		m[oneDimIndex] = 1.0f;
	}
}

void Matrix::fillWithZeros() {
	for (int elementIndex = 0; elementIndex <
		numElements; elementIndex++) {
		m[elementIndex] = 0.0f;
	}
}

void Matrix::AllocateAndCopyFrom(const Matrix& other) {
	this->numRows = other.numRows;
	this->numColumns = other.numColumns;

	numElements = numRows*numColumns;
	m = new float[numElements];
	memcpy(m, other.m, numElements*sizeof(float));
}

Matrix Matrix::operator+(const Matrix& rhs) const {
	Matrix sum(rhs.numRows, rhs.numColumns);
	
	for (int elementIndex = 0; elementIndex < numElements;
		elementIndex++) {
		sum.m[elementIndex] = this->m[elementIndex]
			+ rhs.m[elementIndex];
	}

	return sum;
}

Matrix Matrix::operator-(const Matrix& rhs) const {
	Matrix diff(rhs.numRows, rhs.numColumns);

	for (int elementIndex = 0; elementIndex < numElements;
		elementIndex++) {
		diff.m[elementIndex] = this->m[elementIndex]
			- rhs.m[elementIndex];
	}

	return diff;
}

Matrix Matrix::operator*(const Matrix& rhs) const {
	Matrix product(rhs.numRows, rhs.numColumns);
	// TODO

	return product;
}

Matrix& Matrix::operator+=(const Matrix& rhs) {
	for (int elementIndex = 0; elementIndex < numElements;
		elementIndex++) {
		m[elementIndex] += rhs.m[elementIndex];
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& rhs) {
	for (int elementIndex = 0; elementIndex < numElements;
		elementIndex++) {
		m[elementIndex] -= rhs.m[elementIndex];
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& rhs) {
	// TODO
	return *this;
}

Matrix Matrix::operator+(float scalar) const {
	Matrix sum(*this);

	for (int elementIndex = 0; elementIndex < numElements;
		elementIndex++) {
		sum.m[elementIndex] = this->m[elementIndex]
			+ scalar;
	}

	return sum;
}

Matrix Matrix::operator-(float scalar) const {
	Matrix diff(*this);

	for (int elementIndex = 0; elementIndex < numElements;
		elementIndex++) {
		diff.m[elementIndex] = this->m[elementIndex]
			- scalar;
	}

	return diff;
}

Matrix Matrix::operator*(float scalar)  const {
	Matrix product(*this);

	for (int elementIndex = 0; elementIndex < numElements;
		elementIndex++) {
		product.m[elementIndex] = this->m[elementIndex]
			* scalar;
	}

	return product;
}

Matrix Matrix::operator/(float scalar) const {
	Matrix div(*this);

	for (int elementIndex = 0; elementIndex < numElements;
		elementIndex++) {
		div.m[elementIndex] = this->m[elementIndex]
			/ scalar;
	}

	return div;
}

Matrix& Matrix::operator+=(float scalar) {
	for (int elementIndex = 0; elementIndex < numElements;
		elementIndex++) {
		m[elementIndex] += scalar;
	}

	return *this;
}

Matrix& Matrix::operator-=(float scalar) {
	for (int elementIndex = 0; elementIndex < numElements;
		elementIndex++) {
		m[elementIndex] -= scalar;
	}

	return *this;
}

Matrix& Matrix::operator*=(float scalar) {
	for (int elementIndex = 0; elementIndex < numElements;
		elementIndex++) {
		m[elementIndex] *= scalar;
	}

	return *this;
}

Matrix& Matrix::operator/=(float scalar) {
	for (int elementIndex = 0; elementIndex < numElements;
		elementIndex++) {
		m[elementIndex] /= scalar;
	}

	return *this;
}

float* Matrix::operator[] (unsigned int row) {
	return &m[row*numColumns];
}

float& Matrix::operator()(unsigned int row,
	unsigned int col) {
	return m[row*numColumns + col]; // TODO  	
}

const float& Matrix::operator()(unsigned int row,
	unsigned int col) const {
	return m[row*numColumns + col]; // TODO  	
}
