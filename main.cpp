#include <iostream>

void destroy(int ** mtx, size_t created);
int ** create(size_t rows, size_t cols);

int main()
{
  int ** matrix = nullptr;
  try {
    matrix = create(5, 5);
  } catch (const std::bad_alloc & e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
  destroy(matrix, 5);
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