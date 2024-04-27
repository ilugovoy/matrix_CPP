/**
 * @file matrix_operators.cpp
 * @brief Реализация перегруженных операторов для класса S21 Matrix
 */

#include "s21_matrix_oop.h"

/**
 * @brief Перегруженный оператор присваивания
 *
 * @param other Матрица, которая будет присвоена текущей матрице
 * @return Текущая матрица с новыми значениями
 */
S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this == &other) {
    return *this;
  }

  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = std::vector<std::vector<double>>(other.matrix_);

  return *this;
}

/**
 * @brief Перегруженный оператор сложения
 *
 * @param other Матрица, которая будет добавлена к текущей матрице
 * @return Результат операции сложения
 * @throws std::invalid_argument Если размеры матриц не совпадают
 */
S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "Matrices must have the same dimensions for addition");
  }

  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result(i, j) = matrix_[i][j] + other(i, j);
    }
  }

  return result;
}

/**
 * @brief Перегруженный оператор вычитания
 *
 * @param other Матрица, которая будет вычтена из текущей матрицы
 * @return Результат операции вычитания
 * @throws std::invalid_argument Если размеры матриц не совпадают
 */
S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "Matrices must have the same dimensions for addition");
  }
  S21Matrix result(rows_, cols_);
  result = *this;
  result.SubMatrix(other);
  return result;
}

/**
 * @brief Перегруженный оператор умножения
 *
 * @param other Матрица, на которую будет умножена текущая матрица
 * @return Результат операции умножения
 * @throws std::invalid_argument Если размеры матриц не совместимы для умножения
 */
S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result = *this;
  result.MulMatrix(other);
  return result;
}

/**
 * @brief Перегруженный оператор сравнения на равенство
 *
 * @param other Матрица, которая будет сравниваться с текущей матрицей
 * @return true, если матрицы равны, false в противном случае
 */
bool S21Matrix::operator==(const S21Matrix& other) const {
  if (this->rows_ != other.GetRows() || this->cols_ != other.GetCols()) {
    return false;
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (matrix_[i][j] != other(i, j)) {
        return false;
      }
    }
  }
  return true;
}

/**
 * @brief Перегруженный оператор присваивания сложения
 *
 * @param other Матрица, которая будет добавлена к текущей матрице
 * @return Текущая матрица с новыми значениями
 */
S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

/**
 * @brief Перегруженный оператор присваивания вычитания
 *
 * @param other Матрица, которая будет вычтена из текущей матрицы
 * @return Текущая матрица с новыми значениями
 */
S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

/**
 * @brief Перегруженный оператор присваивания умножения
 *
 * @param other Матрица, на которую будет умножена текущая матрица
 * @return Текущая матрица с новыми значениями
 */
S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

/**
 * @brief Перегруженный оператор вывода в поток
 *
 * @param os Поток вывода, в который будет записана матрица
 * @param matrix Матрица, которая будет выведена в поток
 * @return Поток вывода с записанной в него матрицей
 * @note позволяет выводить std::cout << matrix;
 */
std::ostream& operator<<(std::ostream& os, const S21Matrix& matrix) {
  for (int i = 0; i < matrix.GetRows(); ++i) {
    for (int j = 0; j < matrix.GetCols(); ++j) {
      os << matrix(i, j) << " ";
    }
    os << std::endl;
  }
  return os;
}

/**
 * @brief Перегруженный оператор индексации для доступа без константы
 *
 * @param i Индекс строки
 * @param j Индекс столбца
 * @return Ссылка на элемент в указанной строке и столбце
 */
double& S21Matrix::operator()(int i, int j) { return matrix_[i][j]; }

/**
 * @brief Перегруженный оператор индексации для доступа с константой
 *
 * @param i Индекс строки
 * @param j Индекс столбца
 * @return Константная ссылка на элемент в указанной строке и столбце
 */
double& S21Matrix::operator()(int i, int j) const {
  return const_cast<double&>(matrix_[i][j]);
}
