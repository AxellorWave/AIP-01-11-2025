#include <iostream>

void destroy(int ** mtx, size_t created);
int ** create(size_t rows, size_t cols);
void construct(int ** mtx, int init, size_t rows, size_t cols);
void input(int ** mtx, size_t rows, size_t cols);
void output(int ** mtx, size_t rows, size_t cols);
int ** convert(const int * t, size_t n, const size_t * lns, size_t rows);
void test_convert();

int main()
{
  size_t rows = 0;
  size_t cols = 0;
  std::cin >> rows >> cols;
  if (!std::cin) {
    std::cerr << "AAAAAAAA BAD ENTER!!!!\n";
    return 2;
  }

  int ** matrix = nullptr;
  try {
    matrix = create(rows, cols);
    std::cout << "Created!\n";
  } catch (const std::bad_alloc & e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
  input(matrix, rows, cols);
  if (!std::cin) {
    std::cerr << "AAAAAAAA BAD ENTER!!!!\n";
    destroy(matrix, rows);
    return 2;
  }
  output(matrix, rows, cols);
  destroy(matrix, rows);
  std::cout << "---------------------\n";
  test_convert();
}

void destroy(int ** mtx, size_t created)
{
  for (size_t i = 0; i < created; ++i) {
    delete[] mtx[i];
  }
  delete[] mtx;
}

int ** create(size_t rows, size_t cols)
{
  int ** mtx = new int * [rows];
  size_t created = 0;
  try {
    for (; created < rows; ++created) {
      mtx[created] = new int[cols];
    } 
  } catch (const std::bad_alloc & e) {
    destroy(mtx, created);
    throw;
  }
  return mtx;
}

void construct(int ** mtx, int init, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      mtx[i][j] = init;
    }
  }
}

void input(int ** mtx, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      std::cin >> mtx[i][j];
    }
  }
}

void output(int ** mtx, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows; ++i) {
    std::cout << mtx[i][0];
    for (size_t j = 1; j < cols; ++j) {
      std::cout << " " << mtx[i][j];
    }
    std::cout << "\n";
  }
}

int ** convert(const int * t, size_t n, const size_t * lns, size_t rows)
{
  int ** table = new int * [rows];
  size_t k = 0;
  for (size_t i = 0; i < rows; ++i) {
    table[i] = new int[lns[i]];
    for (size_t j = 0; j < lns[i]; ++j) {
      table[i][j] = t[k];
      ++k;
    }
  }
  return table;
}

void test_convert()
{
  int t[] = {5, 5, 5, 5, 6, 6, 7, 7, 7, 7, 7, 8};
  size_t n = 12;
  size_t lns[] = {4, 2, 5, 1};
  size_t rows = 4;
  int ** table = convert(t, n, lns, rows);
  for (size_t i = 0; i < rows; ++i) {
    std::cout << table[i][0];
    for (size_t j = 1; j < lns[i]; ++j) {
      std::cout << " " << table[i][j];
    }
    std::cout << "\n";
  }
  destroy(table, rows);
}
