/**
 * @file matrix_methods.cpp
 * @brief Реализация операций с матрицами для класса S21.
 */

#include "s21_matrix_oop.h"

/**
 * @brief Добавляет вторую матрицу к текущей.
 *
 * @param other Матрица, которая будет добавлена к текущей матрице.
 * @throws std::invalid_argument Если размеры матриц не совпадают.
 */
void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.GetRows() || cols_ != other.GetCols()) {
    throw std::invalid_argument(
        "Matrices must have the same dimensions for addition");
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other(i, j);
    }
  }
}

/**
 * @brief Вычитает вторую матрицу из текущей.
 *
 * @param other Матрица, которая будет вычтена из текущей матрицы.
 * @throws std::invalid_argument Если размеры матриц не совпадают.
 */
void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.GetRows() || cols_ != other.GetCols()) {
    throw std::invalid_argument(
        "Matrices must have the same dimensions for subtraction");
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other(i, j);
    }
  }
}

/**
 * @brief Умножает текущую матрицу на другую матрицу.
 *
 * @param other Матрица, на которую будет умножена текущая матрица.
 * @throws std::invalid_argument Если число столбцов первой матрицы не равно
 * числу строк второй матрицы.
 */
void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.GetRows()) {
    throw std::invalid_argument(
        "Number of columns in the first matrix must be equal to the number of "
        "rows in the second matrix for multiplication");
  }

  S21Matrix result(rows_, other.GetCols());
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.GetCols(); ++j) {
      for (int k = 0; k < other.rows_; ++k) {
        result(i, j) += matrix_[i][k] * other(k, j);
      }
    }
  }

  *this = result;
}

/**
 * @brief Умножает текущую матрицу на число
 *
 * @param num зЗначение, на которое будет умножена матрица.
 */
void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

/**
 * @brief Изменяет размер матрицы, сохраняя существующие элементы и добавляя
 * новые, если размер увеличивается.
 *
 * @param rows Новое количество строк.
 * @param cols Новое количество столбцов.
 */
void S21Matrix::Resize(int rows, int cols) {
  matrix_.resize(rows);
  for (int i = 0; i < rows; ++i) {
    matrix_[i].resize(cols);
  }
  rows_ = rows;
  cols_ = cols;
}

/**
 * @brief Создает и возвращает транспонированную матрицу.
 *
 * @return Транспонированная матрица.
 */
S21Matrix S21Matrix::Transpose() {
  S21Matrix transposed(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      transposed(j, i) = matrix_[i][j];
    }
  }
  return transposed;
}

/**
 * @brief Вычисляет и возвращает матрицу алгебраических дополнений текущей
 * матрицы.
 *
 * @return Матрица алгебраических дополнений.
 * @throws std::logic_error Если матрица не является квадратной.
 */
S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    // Бросаем исключение, если матрица не квадратная
    throw std::logic_error("Matrix must be square to calculate complements");
  }

  S21Matrix result(rows_, cols_);

  if (rows_ != 1) {
    S21Matrix aux(rows_, cols_);
    for (int x = 0; x < rows_; ++x) {
      for (int y = 0; y < cols_; ++y) {
        S21Matrix minor = GetMatrixMinor(x, y);
        double minorDeterminant = minor.Determinant();
        int sign = ((x + y) % 2 == 0) ? 1 : -1;
        result(x, y) = sign * minorDeterminant;
      }
    }
  } else {
    // Если матрица 1x1, присваиваем значение 1 элементу комплементарной матрицы
    result(0, 0) = 1;
  }

  return result;
}

/**
 * @brief Вычисляет и возвращает определитель текущей матрицы.
 *
 * @return Определитель матрицы.
 * @throws std::logic_error Если матрица не является квадратной.
 */
double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::logic_error(
        "Matrix must be square to calculate its determinant");
  }

  if (rows_ == 1) {
    return matrix_[0][0];
  }

  double determinantValue = 0.0;

  for (int j = 0; j < cols_; ++j) {
    S21Matrix minor = GetMatrixMinor(0, j);
    double minorDeterminant = minor.Determinant();
    int sign = (j % 2 == 0) ? 1 : -1;
    determinantValue += sign * matrix_[0][j] * minorDeterminant;
  }

  return determinantValue;
}

/**
 * @brief Получает минор для определенного элемента текущей матрицы.
 *
 * @param row Индекс строки элемента.
 * @param col Индекс столбца элемента.
 * @return Минор для указанного элемента.
 */
S21Matrix S21Matrix::GetMatrixMinor(int row, int col) const {
  int size = rows_ - 1;
  S21Matrix minor(size, size);

  int minorRow = 0;
  for (int i = 0; i < rows_; ++i) {
    if (i == row) {
      continue;  // Пропускаем текущую строку, чтобы исключить ее из минора
    }

    int minorCol = 0;
    for (int j = 0; j < cols_; ++j) {
      if (j == col) {
        continue;  // Пропускаем текущий столбец, чтобы исключить его из минора
      }

      minor(minorRow, minorCol) =
          matrix_[i][j];  // Копируем элемент в минорную матрицу
      minorCol++;
    }

    minorRow++;
  }

  return minor;
}

/**
 * @brief Вычисляет и возвращает обратную матрицу.
 *
 * @return Обратная матрица.
 * @throws std::logic_error Если определитель матрицы равен нулю, что делает
 * вычисление обратной матрицы невозможным.
 */
S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_) {
    throw std::logic_error("Matrix must be square to calculate its inverse");
  }

  double determinant = Determinant();
  if (fabs(determinant) < 1e-6) {
    throw std::logic_error(
        "Matrix is singular, its inverse cannot be calculated");
  }

  S21Matrix complements = CalcComplements().Transpose();
  S21Matrix inverse(rows_, cols_);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      inverse(i, j) = complements(i, j) / determinant;
    }
  }

  return inverse;
}

/**
 * @brief Возвращает количество строк в матрице.
 *
 * @return Количество строк.
 */
int S21Matrix::GetRows() const { return rows_; }

/**
 * @brief Возвращает количество столбцов в матрице.
 *
 * @return Количество столбцов.
 */
int S21Matrix::GetCols() const { return cols_; }
