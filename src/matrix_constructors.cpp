/**
 * @file matrix_constructors.cpp
 * @brief Реализация конструкторов и деструктора класса S21Matrix
 *
 * Данный файл содержит реализацию базового конструктора, параметризированного
 * конструктора, конструктора копирования, конструктора переноса и деструктора
 * класса S21Matrix.
 */

#include "s21_matrix_oop.h"

/**
 * @brief Базовый конструктор класса S21Matrix.
 *
 * Инициализирует матрицу нулевой размерности (0x0).
 */
S21Matrix::S21Matrix() : rows_(0), cols_(0) {}

/**
 * @brief Параметризированный конструктор класса S21Matrix.
 *
 * Создает матрицу заданных размеров (rows x cols).
 *
 * @param rows Количество строк матрицы.
 * @param cols Количество столбцов матрицы.
 */
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  matrix_.resize(rows_);
  for (int i = 0; i < rows_; ++i) {
    matrix_[i].resize(cols_);
  }
}

/**
 * @brief Конструктор копирования класса S21Matrix.
 *
 * Создает копию существующей матрицы.
 *
 * @param other Ссылка на матрицу, которую нужно скопировать.
 */
S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {}

/**
 * @brief Конструктор переноса класса S21Matrix.
 *
 * Переносит содержимое другой матрицы в новую матрицу.
 *
 * @param other Ссылка на матрицу, содержимое которой нужно перенести.
 */
S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_),
      cols_(other.cols_),
      matrix_(std::move(other.matrix_)) {}

/**
 * @brief Деструктор класса S21Matrix.
 *
 * Освобождает память, занятую матрицей, по завершении работы с ней.
 */
S21Matrix::~S21Matrix() {}
