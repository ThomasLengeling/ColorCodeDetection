#pragma once

#include "ofMain.h"
#include <memory>

/*
Color type of each segment
send each color
*/

class ColorTile;
typedef std::shared_ptr<ColorTile> ColorTileRef;

class ColorTile{
public:
    ColorTile(){
        mColums = 2;
        mRows   = 2;
        numTile = mColums * mRows;

        for(int i = 0; i < numTile; i++){
            ColorTypeRef ctype = ColorType::create();
            mType.push_back(ctype);
        }

    }

    static ColorTileRef create(){
     return std::make_shared<ColorTile>();
   }

   std::vector<ColorTypeRef> getColorVector(){return mType;}

   int getColums(){return mColums;}
   int getRows(){return mRows;}


private:

    int numTile;
    int mColums;
    int mRows;

    //Color type can be red green blue
    std::vector<ColorTypeRef> mType;

};
