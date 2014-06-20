//
//  RectangleInterface.cpp
//  TestLight
//
//  Created by calf on 14-6-18.
//
//

#include "RectangleInterface.h"

Vec2 RectangleInterface::_center = Vec2(0, 0);
int RectangleInterface::_row = 0;
int RectangleInterface::_column = 0;
Size RectangleInterface::_cellSize = Size(0, 0);
Size RectangleInterface::_rectangleSize = Size(0, 0);

void RectangleInterface::initialize(int row, int column, Size cellSize, int space, Vec2 center)
{
    _center = center;
    _row = row;
    _column = column;
    _cellSize = cellSize;
    _cellSize.width += space;
    _cellSize.height += space;
    
    _rectangleSize = Size(_cellSize.width * _column, _cellSize.height * _row);
}

Vec2 RectangleInterface::getPosition(int row, int column)
{
    Vec2 position = Vec2(0, 9);
    if(row > _row || row <=0) return position;
    if(column > _column || column <=0) return position;
    
    row = _row - row + 1;
    position = Vec2(column * _cellSize.width - _rectangleSize.width/2, row * _cellSize.height - _rectangleSize.height/2);
    
    return position;
}

float RectangleInterface::getAngleX(Vec2 position)
{
    
    return tan(position.x/position.y);
//    return atanhf(position.x/position.y);
}


double RectangleInterface::ConvertDegreesToRadians(double degrees)
{
    double radians = (M_PI / 180) * degrees;
    return (radians);
}

double RectangleInterface::ConvertRadiansToDegrees(double radians)
{
    double degree = (radians*180)/M_PI;
    return (degree);
}
