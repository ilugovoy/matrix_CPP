/**
 * @file s21_matrix_oop.h
 * @brief Заголовочный файл для класса S21Matrix, реализующего матричные
 * операции.
 */

#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <cmath>
#include <iostream>
#include <vector>

/**
 * @class S21Matrix
 * @brief Класс, реализующий матричные операции.
 */
class S21Matrix {
 public:
  S21Matrix();  // стандартный конструктор
  S21Matrix(int rows, int cols);  // параметризированный конструктор
  S21Matrix(const S21Matrix& other);  // конструктор копирования
  S21Matrix(S21Matrix&& other);  // конструктор переноса
  ~S21Matrix();                  // деструктор

  // методы
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void Resize(int rows, int cols);

  S21Matrix Transpose();
  S21Matrix InverseMatrix();
  S21Matrix CalcComplements();
  S21Matrix GetMatrixMinor(int row, int col) const;

  double Determinant();
  // Методы-аксессоры/геттеры
  int GetRows() const;
  int GetCols() const;

  // Методы-мутаторы/сеттеры
  inline void SetRows(int rows) { rows_ = rows; }
  inline void SetCols(int cols) { cols_ = cols; }

  // перегрузка операторов
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);

  // перегрузка оператора сравнения
  bool operator==(const S21Matrix& other) const;

  // перегрузка операторов индексации
  double& operator()(int i, int j);
  double& operator()(int i, int j) const;

  // перегрузка оператора вывода
  friend std::ostream& operator<<(std::ostream& os, const S21Matrix& matrix);

 private:
  int rows_, cols_;
  std::vector<std::vector<double>> matrix_;
};

#endif  // S21_MATRIX_OOP_H