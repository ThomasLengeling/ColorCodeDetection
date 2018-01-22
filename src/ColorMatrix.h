#pragma once

#include "ofMain.h"

#include "ColorTile.h"
#include "ColorTypes.h"

#include <memory>

/*
Color type of each segment
send each color

Matrix with the color assigment for each element
*/

class ColorMatrix;
typedef std::shared_ptr<ColorMatrix> ColorMatrixRef;

class ColorMatrix{
public:
    ColorMatrix(){
        mColums = 10;
        mRows  =  10;
        for(int i = 0; i < mColums; i++){
            for(int j = 0; j < mRows; j++){
                ColorTileRef tile = ColorTile::create();
                mTileMatrix.push_back(tile);
            }
        }
    }

    //create memory for the color matrix class
    static ColorMatrixRef create(){
     return std::make_shared<ColorMatrix>();
   }

   //update the matrix with colors obtained from the color detection algorithm
   void updateColorMatrix();

   //draw the color matrix
   void drawMatrix(int posx, int posy);

private:

    int mColums;
    int mRows;

    std::vector<ColorTileRef> mTileMatrix;
    
};
