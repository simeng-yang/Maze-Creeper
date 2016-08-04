#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>     //ifstream
#include <iostream>     //standard c output modes
#include <iomanip>     //setprecision()
#include <vector>     //vectors, including 2-dimensional
#include <cstdlib>     //system("cls") to clear console
#include <stack>     //stacks
#include <math.h>     //sqrt()
#include <ctime>     //clock in DelayFrame()
#include <windows.h>     //functions in the Windows API, such as SetConsoleCursorPosition

#include "Cell.h"      //Class for individual unit "cells" of maze

class Graph
{
    public:
        Graph();
        virtual ~Graph();
        void LoadGraph(const std::string &fileName);
        void DisplayGraph();
        void DFS(int r, int c, int toAnimate, int frameDuration);
        void DelayFrame(clock_t millisec);
        void MoveCursor(int x, int y);
    private:
        int height;     //# of rows of maze
        int width;     //# of columns of maze
        int numPaths;     //# of possible path positions in maze
        int pathDistance;     //Total distance of correct position sequence
        char buffer;     //To store char elements from external text-file
        const char obstacle, goal, path;     //Constant chars to represent elements of maze
        double cellsVisited;     //# of cells visited without duplications; double because of use in division

        std::vector <std::vector<Cell*> > maze;     //Stores maze
        std::vector <Cell*> cells;     //Stores individual rows of maze to be allocated into maze 2-dimensional vector
        std::stack <Cell*> cellSequence;     //Stack of cells to store sequence of positions in use
};

#endif // GRAPH_H
