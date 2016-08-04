#include "Graph.h"

//Constructor: initialize char and "stat" variables
Graph::Graph():obstacle('X'), goal('$'), path(' '), cellsVisited(1), numPaths(1)
{

}

//Moves the cursor to a set location on the console screen
void Graph::MoveCursor(int x, int y)
{
    //Initialize the coordinates for the cursor
    COORD coord = {x, y};
    //Set the position
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Pauses for the specified duration of time in milliseconds
void Graph::DelayFrame(clock_t millisec)
{
    clock_t start_time = clock();
    clock_t end_time = millisec + start_time;
    while(clock() != end_time);
}

//Loads in the maze from an external text-file
//Gets # rows, # columns and all symbols for all elements in maze
void Graph::LoadGraph(const std::string &fileName)
{
  std::ifstream fileData(fileName.c_str());

  //# rows
  fileData >> height;
  //# columns
  fileData >> width;
  //Don't skip blank spaces
  fileData >> std::noskipws;

  //Adds elements from external text-file to one row of the maze
  for (int row = 0; row < height; row++)
  {
      for (int col = 0; col < width; col++)
      {
          fileData >> buffer;

          //If there is a new line character, take the next character
          if (buffer == '\n')
          {
             fileData >> buffer;
          }

          cells.push_back(new Cell(row, col, buffer));

          //If there is a new path position, increment the counter
          if (buffer == path)
          {
              numPaths++;
          }
      }

      //Pushes the row into a 2-dimensional vector
      maze.push_back(cells);
      cells.clear();
  }

  //Close file
  fileData.close();
}

//Displays the current state of the maze when called
void Graph::DisplayGraph()
{
//Outputs all elements of maze in 2-dimensional vector to screen
for (int row = 0; row < height; row++)
{
    for (int col = 0; col < width; col++)
    {
        std::cout << maze[row][col] -> GetChar();
    }
    std::cout << std::endl;
}
}

/*Depth First Search
Maze search starts at r = 1, c = 1
*/
void Graph::DFS(int r, int c, int toAnimate, int frameDuration)
{
    //If goal is reached, stop
    if (maze[r][c] -> GetChar() == goal){

        //Show only final solved state of maze
        if (toAnimate == 0) {
            //Moves cursor back to beginning to overwrite any console output
            MoveCursor(0,0);
            //Displays state of maze
            DisplayGraph();
        }

        //Declare array to hold 'solution set' for valid path
        int stackSize = cellSequence.size();
        Cell** solutionSet = new Cell*[stackSize];

        //Fill array with path positions
        for (int i = 0; i < stackSize; i++)
        {
            solutionSet[i] = cellSequence.top();
            //Remove the topmost cell once it has been added to array
            cellSequence.pop();
        }

        //Write dimensions of maze solved
        std::cout << std::endl << "# Rows: " << height << std::endl;
        std::cout << "# Columns: " << width << std::endl;

        std::cout << std:: endl << "Path Sequence: " << std::endl;
        //Display valid path positions in correct order as array elements
        for (int j = stackSize - 1; j >= 0; j--)
        {
            std::cout << "(" << solutionSet[j] -> GetRow() << ", " << solutionSet[j] -> GetColumn() << ") -> ";

            //Makes the display more optimal for viewing by approximately "equalizing" display x and y dimensions
            int interval = sqrt(stackSize);
            if ((stackSize - j) % interval == 0)
            {
                std::cout << std:: endl;
            }
        }

        //Don't forget position of goal at the end which is not in stack
        std::cout << "(" << r << ", " << c << ") = $" << std:: endl;

        //Delete dynamically allocated array
        delete solutionSet;

        //Total distance of path is the stack size + 1 for the goal cell
        pathDistance = stackSize + 1;

        //Writes path length
        std::cout << std:: endl << "Solved | # Steps in Path: " << pathDistance;

        //Writes % and #cells visited
        std::cout << std:: endl << "       | % Cells Visited: "
        << std::setprecision(4) << cellsVisited / numPaths * 100 << " ("
        << cellsVisited << " / " << numPaths << " possible path positions)";
    }
    else {
        //Otherwise, push current cell to stack
        if (maze[r][c] -> GetChar() == path)
        {
         cellSequence.push(maze[r][c]);
         cellsVisited++;
        }

        //Set current cell as visited and mark it with #times visited (know how many repeats - 1)
        maze[r][c] -> SetChar(maze[r][c] -> GetCounter());

        //Increment the number of times visited (prior)
        maze[r][c] -> IncrementCounter();


        //Goes through all 4 adjacent cells and checks conditions

        //Down
        if (r+1 < maze.size() && ((maze[r+1][c] -> GetChar() == path) || (maze[r+1][c] -> GetChar() == goal)))
        {
            r++;
        }
        //Up
        else if ((r-1 > 0) && ((maze[r-1][c] -> GetChar() == path) || (maze[r-1][c] -> GetChar() == goal)))
        {
            r--;
        }
        //Right
        else if (c+1 < maze[0].size() && ((maze[r][c+1] -> GetChar() == path) || (maze[r][c+1] -> GetChar() == goal)))
        {
            c++;
        }
        //Left
        else if (c-1 > 0 && ((maze[r][c-1] -> GetChar() == path) || (maze[r][c-1] -> GetChar() == goal)))
        {
            c--;
        }
        else
        {
            //No neighboring cells are free and unvisited, so we need to backtrack

            //Sets current cell to obstacle
            maze[r][c] -> SetChar(obstacle);

            //Remove current (top) cell from stack
            cellSequence.pop();

            //If there are cells still in the stack (non-empty):
            if (!(cellSequence.empty()))
            {
                //Get row and column of last valid cell in stack and use those to resume search
                r = cellSequence.top() -> GetRow();
                c = cellSequence.top() -> GetColumn();
            }
        }

    //Displays state of maze as it is being solved
    if (toAnimate == 1) {
        //Moves cursor back to beginning to overwrite any console output
        MoveCursor(0,0);
        DisplayGraph();
        //Pause for appropriate number of milliseconds, so user can monitor progression of search
        DelayFrame(frameDuration);
    }

        if (cellSequence.empty())
        {
            //Displays only final unsolved state of maze
            if (toAnimate == 0) {
                //Moves cursor back to beginning to overwrite any console output
                MoveCursor(0,0);
                DisplayGraph();
            }

            //If the stack is empty, there are no neighboring cells that can be used and there is no solution
            std::cout << std::endl << "No solution: -1";
        }
        else
        {
            /*Otherwise, perform DFS again with the new values for r and c
            Note that by placing DFS(r,c) outside of the above conditions,
            it is possible to spare the need for separately calling DFS(r, c) multiple times*/
            DFS(r, c, toAnimate, frameDuration);
        }
    }
}

//Destructor
Graph::~Graph()
{

}
