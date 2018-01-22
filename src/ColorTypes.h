#pragma once

#include "ofMain.h"
#include <memory>


/*
Color type of each segment
send each color
*/



class ColorType;
typedef std::shared_ptr<ColorType> ColorTypeRef;

class ColorType{
public:

    enum Color{
        WHITE,
        BLACK,
        RED,
        BLUE,
        GREEN,
        YELLOW
    };

    ColorType(){
        cType = WHITE;
    }

    static ColorTypeRef create(){
     return std::make_shared<ColorType>();
   }


private:

    Color cType;
    bool activated;

};
