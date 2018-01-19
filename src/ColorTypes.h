#pragma once

/*
Color type of each segment
send each color
*/


class ColorType;
typedef std::shared_ptr<ColorType> ColorTypeRef;

class ColorType{
public:
    ColorType(){
        cType = WHITE;
    }

    static ColorTypeRef create(){
     return std::make_shared<ColorType>();
   }


private;

    Color cType;
    bool activated;

    typedef Color{
        RED,
        BLUE,
        Green,
        WHITE
    }Color;
};
