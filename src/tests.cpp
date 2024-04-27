/**
 * @file tests.cpp
 * @brief Тесты для класса S21Matrix.
 */

#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

// --> Тесты конструкторов

/**
 * @brief Тест на проверку работы базового конструктора.
 */
TEST(S21MatrixTest, DefaultConstructorTest) {
  S21Matrix matrix1;
  ASSERT_EQ(0, matrix1.GetRows());
  ASSERT_EQ(0, matrix1.GetCols());
}

/**
 * @brief Тест на проверку работы параметризированного конструктора.
 */
TEST(S21MatrixTest, ParameterizedConstructorTest) {
  S21Matrix matrix2(3, 3);
  ASSERT_EQ(3, matrix2.GetRows());
  ASSERT_EQ(3, matrix2.GetCols());
}

/**
 * @file
 * @brief Набор тестов для класса S21Matrix: конструктор копирования для пустой
 * матрицы.
 */
TEST(S21MatrixTest, CopyConstructorEmptyMatrixTest) {
  S21Matrix matrix1;
  S21Matrix matrix2(matrix1);
  ASSERT_EQ(0, matrix2.GetRows());
  ASSERT_EQ(0, matrix2.GetCols());
}

/**
 * @file
 * @brief Набор тестов для класса S21Matrix: конструктор перемещения для пустой
 * матрицы.
 */
TEST(S21MatrixTest, MoveConstructorEmptyMatrixTest) {
  S21Matrix matrix1;
  S21Matrix matrix2(std::move(matrix1));
  ASSERT_EQ(0, matrix2.GetRows());
  ASSERT_EQ(0, matrix2.GetCols());
}

/**
 * @brief Тест на проверку работы конструктора копирования.
 */
TEST(S21MatrixTest, CopyConstructorTest) {
  S21Matrix matrix3(3, 3);
  matrix3(0, 0) = 1.0;
  matrix3(1, 1) = 2.0;
  matrix3(2, 2) = 3.0;

  S21Matrix matrix4(matrix3);
  ASSERT_EQ(matrix3, matrix4);
}

/**
 * @brief Тест на проверку работы конструктора переноса.
 */
TEST(S21MatrixTest, MoveConstructorTest) {
  S21Matrix matrix5(3, 3);
  matrix5(0, 0) = 1.0;
  matrix5(1, 1) = 2.0;
  matrix5(2, 2) = 3.0;

  S21Matrix matrix6(std::move(matrix5));
  ASSERT_EQ(3, matrix6.GetRows());
  ASSERT_EQ(3, matrix6.GetCols());
  ASSERT_EQ(1.0, matrix6(0, 0));
  ASSERT_EQ(2.0, matrix6(1, 1));
  ASSERT_EQ(3.0, matrix6(2, 2));
}

// --> Тесты перегруженных операторов

/**
 * @brief Тест на проверку работы оператора присваивания.
 */
TEST(S21MatrixTest, AssignmentOperatorTest) {
  S21Matrix matrix1(3, 3);
  matrix1(0, 0) = 1.0;
  matrix1(1, 1) = 2.0;
  matrix1(2, 2) = 3.0;

  S21Matrix matrix2 = matrix1;
  ASSERT_EQ(matrix1, matrix2);
}

/**
 * @brief Тест на самоприсваивание оператора присваивания.
 */
TEST(S21MatrixTest, AssignmentOperatorSelfAssignmentTest) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix1 = matrix1;

  ASSERT_EQ(matrix1(0, 0), 1.0);
  ASSERT_EQ(matrix1(0, 1), 2.0);
  ASSERT_EQ(matrix1(1, 0), 3.0);
  ASSERT_EQ(matrix1(1, 1), 4.0);
}

/**
 * @brief Тест на проверку работы оператора сложения.
 */
TEST(S21MatrixTest, AdditionOperatorTest) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  S21Matrix result = matrix1 + matrix2;
  ASSERT_EQ(result(0, 0), 6.0);
  ASSERT_EQ(result(0, 1), 8.0);
  ASSERT_EQ(result(1, 0), 10.0);
  ASSERT_EQ(result(1, 1), 12.0);
}

/**
 * @brief Тест проверки выброса исключения сложения при разных размерах матриц.
 */
TEST(S21MatrixTest, AdditionOperatorExceptionTest) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix2(3, 3);

  ASSERT_THROW(matrix + matrix2, std::invalid_argument);
  ASSERT_THROW(matrix.SumMatrix(matrix2), std::invalid_argument);
}

/**
 * @brief Тест на проверку работы оператора вычитания.
 */
TEST(S21MatrixTest, SubtractionOperatorTest) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 10.0;
  matrix1(0, 1) = 20.0;
  matrix1(1, 0) = 30.0;
  matrix1(1, 1) = 40.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  S21Matrix result = matrix1 - matrix2;
  ASSERT_EQ(result(0, 0), 5.0);
  ASSERT_EQ(result(0, 1), 14.0);
  ASSERT_EQ(result(1, 0), 23.0);
  ASSERT_EQ(result(1, 1), 32.0);
}

/**
 * @brief Тест проверки выброса исключения вычитания при разных размерах матриц.
 */
TEST(S21MatrixTest, SubtractionOperatorExceptionTest) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(3, 3);
  ASSERT_THROW(matrix1 - matrix2, std::invalid_argument);
  ASSERT_THROW(matrix1.SubMatrix(matrix2), std::invalid_argument);
}

/**
 * @brief Тест на проверку работы оператора умножения.
 */
TEST(S21MatrixTest, MultiplyMatricesWithEqualDimension) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5;
  matrix2(0, 1) = 6;
  matrix2(1, 0) = 7;
  matrix2(1, 1) = 8;

  S21Matrix result = matrix1 * matrix2;

  S21Matrix expected(2, 2);
  expected(0, 0) = 19;
  expected(0, 1) = 22;
  expected(1, 0) = 43;
  expected(1, 1) = 50;

  ASSERT_EQ(expected, result);
}

/**
 * @brief Тест на проверку работы оператора сравнения на равенство.
 */
TEST(S21MatrixTest, EqualityOperatorTest) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 4.0;

  S21Matrix matrix3(3, 3);
  matrix3(0, 0) = 1.0;
  matrix3(0, 1) = 2.0;
  matrix3(1, 0) = 3.0;
  matrix3(1, 1) = 5.0;

  ASSERT_TRUE(matrix1 == matrix2);
  ASSERT_FALSE(matrix1 == matrix3);
}

/**
 * @brief Тест проверки равенства матриц с разными значениями.
 */
TEST(S21MatrixTest, EqualityOperatorDifferentMatricesTest) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 5.0;  // Разное значение в последнем элементе

  ASSERT_FALSE(matrix1 == matrix2);
}

/**
 * @brief Тест на проверку работы оператора присваивания сложения.
 */
TEST(S21MatrixTest, PlusAssignmentOperatorTest) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  matrix1 += matrix2;
  ASSERT_EQ(matrix1(0, 0), 6.0);
  ASSERT_EQ(matrix1(0, 1), 8.0);
  ASSERT_EQ(matrix1(1, 0), 10.0);
  ASSERT_EQ(matrix1(1, 1), 12.0);
}

/**
 * @brief Тест на проверку работы оператора присваивания вычитания.
 */
TEST(S21MatrixTest, MinusAssignmentOperatorTest) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 10.0;
  matrix1(0, 1) = 20.0;
  matrix1(1, 0) = 30.0;
  matrix1(1, 1) = 40.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  matrix1 -= matrix2;
  ASSERT_EQ(matrix1(0, 0), 5.0);
  ASSERT_EQ(matrix1(0, 1), 14.0);
  ASSERT_EQ(matrix1(1, 0), 23.0);
  ASSERT_EQ(matrix1(1, 1), 32.0);
}

/**
 * @brief Тест на проверку работы оператора присваивания умножения.
 */
TEST(S21MatrixTest, MultiplyAssignmentOperatorTest) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;

  S21Matrix matrix2(3, 2);
  matrix2(0, 0) = 7.0;
  matrix2(0, 1) = 8.0;
  matrix2(1, 0) = 9.0;
  matrix2(1, 1) = 10.0;
  matrix2(2, 0) = 11.0;
  matrix2(2, 1) = 12.0;

  matrix1 *= matrix2;
  ASSERT_EQ(matrix1(0, 0), 58.0);
  ASSERT_EQ(matrix1(0, 1), 64.0);
  ASSERT_EQ(matrix1(1, 0), 139.0);
  ASSERT_EQ(matrix1(1, 1), 154.0);
}

/**
 * @brief Тест на проверку работы оператора вывода в поток.
 */
TEST(S21MatrixTest, StreamOperatorTest) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  std::stringstream ss;
  ss << matrix;
  ASSERT_EQ(ss.str(), "1 2 \n3 4 \n");
}

/**
 * @brief Тест на проверку работы оператора индексации.
 */
TEST(S21MatrixTest, IndexOperatorTest) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  ASSERT_EQ(matrix(0, 0), 1.0);
  ASSERT_EQ(matrix(0, 1), 2.0);
  ASSERT_EQ(matrix(1, 0), 3.0);
  ASSERT_EQ(matrix(1, 1), 4.0);

  matrix(0, 0) = 5.0;
  ASSERT_EQ(matrix(0, 0), 5.0);
}

// ----> Тесты методов

/**
 * @brief Проверяет корректность вычисления обратной матрицы.
 */
TEST(MatrixMethodsTest, InverseMatrixTest) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 2.0;
  matrix(0, 1) = 1.0;
  matrix(1, 0) = 1.5;
  matrix(1, 1) = 3.0;

  S21Matrix inverseMatrix = matrix.InverseMatrix();

  ASSERT_FLOAT_EQ(inverseMatrix(0, 0), 0.66666669);
  ASSERT_FLOAT_EQ(inverseMatrix(0, 1), -0.22222222);
  ASSERT_FLOAT_EQ(inverseMatrix(1, 0), -0.33333334);
  ASSERT_FLOAT_EQ(inverseMatrix(1, 1), 0.44444445);

  // Проверяем ситуацию, когда определитель равен нулю
  S21Matrix singularMatrix(2, 2);
  singularMatrix(0, 0) = 2.0;
  singularMatrix(0, 1) = 2.0;
  singularMatrix(1, 0) = 4.0;
  singularMatrix(1, 1) = 4.0;
  ASSERT_THROW(singularMatrix.InverseMatrix(), std::logic_error);
}

/**
 * @brief Проверяет корректность вычисления определителя для квадратной матрицы.
 */
TEST(MatrixMethodsTest, DeterminantTest) {
  S21Matrix squareMatrix(3, 3);
  squareMatrix(0, 0) = 1.0;
  squareMatrix(0, 1) = 2.0;
  squareMatrix(0, 2) = 3.0;
  squareMatrix(1, 0) = 4.0;
  squareMatrix(1, 1) = 5.0;
  squareMatrix(1, 2) = 6.0;
  squareMatrix(2, 0) = 7.0;
  squareMatrix(2, 1) = 8.0;
  squareMatrix(2, 2) = 9.0;
  ASSERT_EQ(squareMatrix.Determinant(), 0.0);

  // Проверяем базовый случай: матрица 1x1
  S21Matrix baseCaseMatrix(1, 1);
  baseCaseMatrix(0, 0) = 5.0;
  ASSERT_EQ(baseCaseMatrix.Determinant(), 5.0);
}

/**
 * @brief Проверяет корректность вычисления матрицы алгебраических дополнений.
 */
TEST(S21MatrixTest, CalcComplementsTests) {
  S21Matrix A(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 0;
  A(1, 1) = 4;
  A(1, 2) = 2;
  A(2, 0) = 5;
  A(2, 1) = 2;
  A(2, 2) = 1;

  S21Matrix expectedComplements(3, 3);
  expectedComplements(0, 0) = 0;
  expectedComplements(0, 1) = 10;
  expectedComplements(0, 2) = -20;
  expectedComplements(1, 0) = 4;
  expectedComplements(1, 1) = -14;
  expectedComplements(1, 2) = 8;
  expectedComplements(2, 0) = -8;
  expectedComplements(2, 1) = -2;
  expectedComplements(2, 2) = 4;

  S21Matrix result = A.CalcComplements();
  ASSERT_EQ(expectedComplements, result);

  S21Matrix B(2, 3);
  ASSERT_THROW(B.CalcComplements(), std::logic_error);

  S21Matrix C(3, 2);
  ASSERT_THROW(C.CalcComplements(), std::logic_error);

  S21Matrix G(1, 1);
  G(0, 0) = 5;
  S21Matrix expectedComplementsG(1, 1);
  expectedComplementsG(0, 0) = 1;
  S21Matrix resultG = G.CalcComplements();
  ASSERT_EQ(expectedComplementsG, resultG);
}

/**
 * @brief Проверяет корректность транспонирования матрицы.
 */
TEST(S21MatrixTest, TransposeTest) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;

  S21Matrix expectedTransposed(3, 2);
  expectedTransposed(0, 0) = 1.0;
  expectedTransposed(0, 1) = 4.0;
  expectedTransposed(1, 0) = 2.0;
  expectedTransposed(1, 1) = 5.0;
  expectedTransposed(2, 0) = 3.0;
  expectedTransposed(2, 1) = 6.0;

  S21Matrix transposed = matrix.Transpose();
  ASSERT_EQ(expectedTransposed, transposed);
}

/**
 * @brief Проверяет корректность изменения размера матрицы.
 */
TEST(S21MatrixTest, ResizeTest) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;

  S21Matrix expectedResized(3, 4);
  expectedResized(0, 0) = 1.0;
  expectedResized(0, 1) = 2.0;
  expectedResized(0, 2) = 3.0;
  expectedResized(0, 3) = 0.0;
  expectedResized(1, 0) = 4.0;
  expectedResized(1, 1) = 5.0;
  expectedResized(1, 2) = 6.0;
  expectedResized(1, 3) = 0.0;
  expectedResized(2, 0) = 0.0;
  expectedResized(2, 1) = 0.0;
  expectedResized(2, 2) = 0.0;
  expectedResized(2, 3) = 0.0;

  matrix.Resize(3, 4);
  ASSERT_EQ(expectedResized, matrix);
}

/**
 * @brief Умножает все элементы матрицы на заданное число.
 *
 * @param num Число, на которое будут умножены все элементы матрицы.
 */
TEST(MatrixMethodsTest, MulNumberTest) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;

  double num = 2.0;
  matrix.MulNumber(num);

  ASSERT_EQ(matrix(0, 0), 2.0);
  ASSERT_EQ(matrix(0, 1), 4.0);
  ASSERT_EQ(matrix(0, 2), 6.0);
  ASSERT_EQ(matrix(1, 0), 8.0);
  ASSERT_EQ(matrix(1, 1), 10.0);
  ASSERT_EQ(matrix(1, 2), 12.0);
}

/**
 * @brief Тест проверки выброса исключения при попытке умножения матриц с
 * неподходящими размерами.
 *
 * Создается матрица размером 2x3, которая заполняется значениями.
 * Затем создается вторая матрица размером 4x2, что делает их неподходящими для
 * умножения. Проверяется, что при попытке умножить такие матрицы выбрасывается
 * исключение std::invalid_argument.
 */
TEST(S21MatrixTest, MulMatrixExceptionTest) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;

  S21Matrix matrix2(4, 2);

  ASSERT_THROW(matrix1.MulMatrix(matrix2), std::invalid_argument);
}

/**
 * @brief Тест проверки выброса исключения при попытке вычислить определитель
 * неквадратной матрицы.
 */
TEST(S21MatrixTest, DeterminantNonSquareMatrixExceptionTest) {
  S21Matrix nonSquareMatrix(2, 3);
  ASSERT_THROW(nonSquareMatrix.Determinant(), std::logic_error);
}

/**
 * @brief Тест проверки выброса исключения при попытке вычислить обратную
 * матрицу для неквадратной матрицы.
 */
TEST(S21MatrixTest, InverseMatrixNonSquareMatrixExceptionTest) {
  S21Matrix nonSquareMatrix(2, 3);
  ASSERT_THROW(nonSquareMatrix.InverseMatrix(), std::logic_error);
}

/**
 * @brief Тест проверки выброса исключения при попытке вычислить обратную
 * матрицу для сингулярной матрицы.
 */
TEST(S21MatrixTest, InverseMatrixSingularMatrixExceptionTest) {
  S21Matrix singularMatrix(2, 2);
  singularMatrix(0, 0) = 2.0;
  singularMatrix(0, 1) = 2.0;
  singularMatrix(1, 0) = 4.0;
  singularMatrix(1, 1) = 4.0;
  ASSERT_THROW(singularMatrix.InverseMatrix(), std::logic_error);
}

/**
 * @brief Точка входа для запуска тестов.
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 * @return Код возврата (0 в случае успешного завершения).
 */
int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
