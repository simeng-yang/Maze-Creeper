/*
Name: Simeng Yang
Date: April 27, 2016
Course Info: ICS4U, Unit 8 - Search Algorithms, Mr. M. Trink

Description:
For a maze loaded from an external text-file, this program will show the sequence of positions
to reach the goal or, if there is no solution, will indicate
that no path is available.
*/

#include <Graph.h>     //Contains maze functions

using namespace std;

int main()
{
    //Text-file name must be specified
    const string fileName = "data.txt";
    //Starting position
    const int startX = 1;
    const int startY = 1;
    //Determines how maze solving is shown
    int toAnimate = -1;
    int frameDuration = -1;
    string userChoice;

    Graph maze;

    //Load maze from external text-file
    maze.LoadGraph(fileName);

    //Display initial state of maze
    maze.DisplayGraph();

    //User can decide whether to monitor the maze progression or not
    do {
        cout << endl << "Animate maze progression (Y - Yes, N - No)? ";
        cin >> userChoice;
        if (userChoice == "Y" || userChoice == "y") {
            toAnimate = 1;
            do {
                //User can choose the speed at which the progression proceeds,
                //corresponding to a time in milliseconds
                cout << endl << "Specify solve speed (S - Slow, M - Medium, F - Fast): ";
                cin >> userChoice;
                if (userChoice == "S" || userChoice == "s"){
                    frameDuration = 200;
                }
                else if (userChoice == "M" || userChoice == "m"){
                    frameDuration = 100;
                }
                else if (userChoice == "F" || userChoice == "f"){
                    frameDuration = 0;
                }
            } while (frameDuration == -1);
        }
        else if (userChoice == "N" || userChoice == "n") {
            toAnimate = 0;
        }
    } while (toAnimate == -1);

    //Clear message
    std::system("cls");

    //Solve the maze, with option for visual display of maze being solved
    maze.DFS(startX, startY, toAnimate, frameDuration);

    return 0;
}
