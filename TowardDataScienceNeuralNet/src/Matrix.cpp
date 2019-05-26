
#include "Matrix.h"
#include <cstring>

// TODO

Matrix::Matrix(unsigned int numRows, unsigned int numColumns) {
	this->numRows = numRows;
	this->numColumns = numColumns;

	m = new float[numRows*numColumns];
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

void Matrix::makeTranspose() {
	// TODO
}

void Matrix::makeIdentity() {
	// TODO
}

void Matrix::AllocateAndCopyFrom(const Matrix& other) {
	this->numRows = other.numRows;
	this->numColumns = other.numColumns;

	auto numElements = numRows*numColumns;
	m = new float[numElements];
	memcpy(m, other.m, numElements*sizeof(float));
}

Matrix Matrix::operator+(const Matrix& rhs) const {
	Matrix sum(rhs.numRows, rhs.numColumns);
	// TODO

	return sum;
}

Matrix Matrix::operator-(const Matrix& rhs) const {
	Matrix diff(rhs.numRows, rhs.numColumns);
	// TODO

	return diff;
}

Matrix Matrix::operator*(const Matrix& rhs) const {
	Matrix product(rhs.numRows, rhs.numColumns);
	// TODO

	return product;
}

Matrix& Matrix::operator+=(const Matrix& rhs) {
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& rhs) {
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& rhs) {
	return *this;
}

Matrix Matrix::operator+(float scalar) const {
	Matrix sum(*this);
	// TODO

	return sum;
}

Matrix Matrix::operator-(float scalar) const {
	Matrix diff(*this);
	// TODO

	return diff;
}

Matrix Matrix::operator*(float scalar)  const {
	Matrix product(*this);
	// TODO

	return product;
}

Matrix Matrix::operator/(float scalar) const {
	Matrix div(*this);
	// TODO

	return div;
}

Matrix& Matrix::operator+=(float scalar) {
	// TODO
	return *this;
}

Matrix& Matrix::operator-=(float scalar) {
	// TODO
	return *this;
}

Matrix& Matrix::operator*=(float scalar) {
	// TODO
	return *this;
}

Matrix& Matrix::operator/=(float scalar) {
	// TODO
	return *this;
}

float& Matrix::operator()(unsigned int row, unsigned int col) {
	return m[0]; // TODO  	
}

const float& Matrix::operator()(unsigned int row, unsigned int col) const {
	return m[0]; // TODO  	
}
