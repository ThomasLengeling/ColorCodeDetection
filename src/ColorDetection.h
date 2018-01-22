#pragma once

#include "ofMain.h"

#include "ofxOpenCv.h"
#include "ofxCv.h"

#include <memory>


#define NUM_COLORS  4
/*
Color detection using parametric detection

*/


/* HSV Color Code:
  Color               Hue      Saturation    Value
  Red     ...     163 - 179    161 - 228   116 - 169
  Orange  ...     0 - 12       112 - 227   134 - 255
  Yellow  ...     22 - 34      38 - 244    160 - 255
  Green   ...     45 - 108     39 - 153    92 - 255
  Blue    ...     92 - 135     62 - 176    32 - 126
  Purple  ...     109 - 139    58 - 148    43 - 87
  **Note: Color May Vary depending on lighting!
*/


//red
const int iLowRedH = 109;
const int iLowRedS = 58;
const int iLowRedV = 43;
const int iHighRedH = 139;
const int iHighRedS = 148;
const int iHighRedV = 87;

//blue
const int iLowBlueH = 92;
const int iLowBlueS = 62;
const int iLowBlueV = 32;
const int iHighBlueH = 135;
const int iHighBlueS = 176;
const int iHighBlueV = 126;

//white
const int iLowWhiteH = 92;
const int iLowWhiteS = 62;
const int iLowWhiteV = 32;
const int iHighWhiteH = 135;
const int iHighWhiteS = 176;
const int iHighWhiteV = 126;

//black
const int iLowBlackH = 92;
const int iLowBlackS = 62;
const int iLowBlackV = 32;
const int iHighBlackH = 135;
const int iHighBlackS = 176;
const int iHighBlackV = 126;

class ColorDetection;
typedef std::shared_ptr<ColorDetection> ColorDetectionRef;

class ColorDetection{
public:
    ColorDetection(){
        //white, black, red, blue,
        for(int i = 0; i < NUM_COLORS; i++){
            ofImage img;
            mImageColors.push_back(img);
        }

        step = 2;
    }

    static ColorDetectionRef create(){
     return std::make_shared<ColorDetection>();
 }

 ofImage getImgDst(){return imgDst;}
 void processColor(ofPixels pixels);

 std::vector<ofImage> getImgVec(){return mImageColors;}

 void compress();

private:

    //detection type
    int type;
    ofImage imgDst;

    std::vector<ofImage> mImageColors;

    int step;
    ofImage outImage;

};
