#include <iostream>

void destroy(int ** mtx, size_t created);
int ** create(size_t rows, size_t cols);
void construct(int ** mtx, int init, size_t rows, size_t cols);

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
  } catch (const std::bad_alloc & e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
  construct(matrix, 2, rows, cols);
  std::cout << matrix[0][0] << "\n";
  destroy(matrix, rows);
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
