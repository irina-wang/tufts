//  ------------------
//  Comp15 spring 2019
//  Recursion and Mazes Lab 
//  position.h
//  Interface and Implementation of position: a very simple 
//               class that can store two integers to represent
//               (x and y coordinates of a possible location in the maze)
//
//  MazeCreator originally created by Chris Gregg on 2/7/14
//  Further edits by: 
//        Eliza Schreibman and Mark A. Sheldon Feb 2017
//        Tanya Sinha and Matias Korman Feb 2019
//
// -------------------


#ifndef POSITION_H
#define POSITION_H

struct Position {
        int row, col;
        Position()
        {
                row = col = 0;
        }
        Position(int r, int c)
        {
                row = r;
                col = c;
        }
        Position north()
        {
                return Position(row - 1, col);
        }
        Position south()
        {
                return Position(row + 1, col);
        }
        Position east()
        {
                return Position(row, col + 1);
        }
        Position west()
        {
                return Position(row, col - 1);
        }
        bool inBounds(int rowLimit, int colLimit)
        {
                return (0 < row) and (row < rowLimit)
                        and (0 < col) and (col < colLimit);
        }
};

#endif
