#pragma once


// row-order matrix
class Matrix {
public:
	Matrix(unsigned int numRows, unsigned int numColumns);
	~Matrix();

	Matrix(const Matrix &rhs);
	Matrix& operator=(const Matrix& rhs);

  	Matrix transpose() const;
  	void makeIdentity();
    void fillWithZeros();

	Matrix operator+(const Matrix& rhs) const;
  	Matrix operator-(const Matrix& rhs) const;
  	Matrix operator*(const Matrix& rhs) const;

  	Matrix& operator+=(const Matrix& rhs);
  	Matrix& operator-=(const Matrix& rhs);
  	Matrix& operator*=(const Matrix& rhs);

  	Matrix operator+(float scalar) const;
  	Matrix operator-(float scalar) const;
  	Matrix operator*(float scalar) const;
  	Matrix operator/(float scalar) const;

  	Matrix& operator+=(float scalar);
  	Matrix& operator-=(float scalar);
  	Matrix& operator*=(float scalar);
  	Matrix& operator/=(float scalar);

  	int getNumRows() const { return numRows; }
  	int getNumColumns() const { return numColumns; }

    float* getRow(unsigned int rowIndex);
    float* operator[](unsigned int rowIndex);

  	float& operator()(unsigned int row, unsigned int col);
  	const float& operator()(unsigned int row, unsigned int col) const;

private:
	unsigned int numRows, numColumns, numElements;
	float *m;

	void AllocateAndCopyFrom(const Matrix& other);
};
