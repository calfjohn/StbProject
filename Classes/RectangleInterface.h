//
//  RectangleInterface.h
//  TestLight
//
//  Created by calf on 14-6-18.
//
//

#ifndef __TestLight__RectangleInterface__
#define __TestLight__RectangleInterface__

#include "cocos2d.h"
USING_NS_CC;

class RectangleInterface{
public:
    static void initialize(int row, int column, Size cellSize, int space, Vec2 center);
    static Vec2 getPosition(int row, int column);
    static Vec2 getCenterPosition(){return _center;}
    static Size getCellSize(){return _cellSize;}

    static float getAngleX(Vec2 position);
    
    static double ConvertDegreesToRadians(double degrees);
    static double ConvertRadiansToDegrees(double radians);
    
    static int getSpace(){return _space;}
    static int getRows(){return _row;}
    static int getColumns(){return _column;}
protected:
    static Vec2 _center;
    static int _space;
    static int _row;
    static int _column;
    static Size _cellSize;
    static Size _rectangleSize;
};
#endif /* defined(__TestLight__RectangleInterface__) */
