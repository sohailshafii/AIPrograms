#pragma once

// row-order matrix
class Matrix {
public:
	Matrix(unsigned int numRows, unsigned int numColumns);
	~Matrix();

	Matrix(Matrix const & rhs);
	Matrix& operator=(Matrix const & rhs);

	Matrix Transpose() const;
	void MakeIdentity();
	void FillWithZeros();
	void FillWithRandomValues(float min, float max);
	void Print() const;

	Matrix operator+(Matrix const & rhs) const;
	Matrix operator-(Matrix const & rhs) const;
	Matrix operator*(Matrix const & rhs) const;

	Matrix& operator+=(Matrix const & rhs);
	Matrix& operator-=(Matrix const & rhs);
	Matrix& operator*=(Matrix const & rhs);

	Matrix operator+(float scalar) const;
	Matrix operator-(float scalar) const;
	Matrix operator*(float scalar) const;
	Matrix operator/(float scalar) const;

	Matrix& operator+=(float scalar);
	Matrix& operator-=(float scalar);
	Matrix& operator*=(float scalar);
	Matrix& operator/=(float scalar);

	int GetNumRows() const { return numRows; }
	int GetNumColumns() const { return numColumns; }

	float* GetRow(unsigned int rowIndex);
	float* operator[](unsigned int rowIndex);

	float& operator()(unsigned int row, unsigned int col);
	const float& operator()(unsigned int row, unsigned int col) const;

private:
	unsigned int numRows, numColumns, numElements;
	float *m;

	void AllocateAndCopyFrom(Matrix const & other);
};
