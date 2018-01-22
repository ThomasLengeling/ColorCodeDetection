#include "ColorMatrix.h"

void ColorMatrix::updateColorMatrix() {}

void ColorMatrix::drawMatrix(int posx, int posy) {

  for (int i = 0; i < mColums; i++) {
    for (int j = 0; j < mRows; j++) {
      int indexIJ = j * mColums + i;
      ColorTileRef tile = mTileMatrix.at(indexIJ);

      for (int l = 0; l < tile->getColums(); l++) {
        for (int k = 0; k < tile->getRows(); k++) {

          int indexLK = k * tile->getColums() + l;
          auto colorType = tile->getColorVector();

          ColorTypeRef colortype = colorType.at(indexLK);

          // now we draw each point
        }
      }
    }
  }
}
