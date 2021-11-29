#include <algorithm>
#include <cassert>
#include <iostream>
#include <thread>
#if defined(_OPENMP)
#include <omp.h>
#endif
#include "ProdMatMat.hpp"

namespace {
void prodSubBlocks(int iRowBlkA, int iColBlkB, int iColBlkA, int szBlock,
                   const Matrix& A, const Matrix& B, Matrix& C) {
    for (int k = iColBlkA; k < std::min(A.nbCols, iColBlkA + szBlock); k++)
        #pragma omp parallel for collapse(2)
         for (int j = iColBlkB; j < std::min(B.nbCols, iColBlkB + szBlock); j++)
             for (int i = iRowBlkA; i < std::min(A.nbRows, iRowBlkA + szBlock); ++i)
                C(i, j) += A(i, k) * B(k, j);
}
const int szBlock = 128;
}  // namespace

Matrix operator*(const Matrix& A, const Matrix& B) {
  Matrix C(A.nbRows, B.nbCols, 0.0);
  for (int block = 0; block < std::min(A.nbRows, B.nbCols); block += szBlock) {
    #pragma omp parallel for collapse(2)
      for (int blocj = 0; blocj < std::min(A.nbRows, B.nbCols); blocj += szBlock) {
          for (int bloci = 0; bloci < std::min(A.nbRows, B.nbCols); bloci += szBlock) {
              prodSubBlocks(bloci, blocj, block, szBlock, A, B, C);
          }
      }
  }
  return C;
}
