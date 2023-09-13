#include <iostream>
#include <vector>
#include <queue>

/**
 * we will use Exploring Graphs algorithm, more specifiaclly BFS. With BFS we can explore all the squeres level by lev, starting fron start
 * position, and continue seraching till we reach the destination. By this way we can make sure that we find the shortest path.
 * We can look at the chessboard as an unweighted Graph,, cells(squeres) are vertices and moves (paths) are the edges
 */

/**
 * We need a struct of Coordinates, so we can make objects with x and y coordinates later. In fact, each point (start, current, destination)
 * are objects with x and y values
 */

struct CoordinateXY
{
    int x;
    int y;
    // Constructor
    CoordinateXY(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
};
/**
 * We need to have a isValid function to check the coordinates that user has provided us with are valid, they are not out of the chessboard
 */
bool isValid(int x, int y)
{
    if (x >= 0 && x < 8 && y >= 0 && y < 8)
        return true;
    else
        return false;
}

/**
 * allPossibleMoves is a 2D array of int that stores all the possible moves that a knight can make. 8 is the number of rows ,since chessboard has
 * 8 rows and 2 is number of columns with shows changes in the x and y values, going up, down, left, right
 */
int allPossibleMoves[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

/**
 * Here we have the knight_moves function that tries to find the simplest possible way (shortest path) from the current position to the destination
*/
std::vector<CoordinateXY> knight_moves(const CoordinateXY &start, const CoordinateXY &destination)
{    
    std::vector<CoordinateXY> path;// making a vector of CoordinateXY objects to create the path
    std::queue<std::vector<CoordinateXY>> moves;// making a queue of vector of CoordinateXy objects

    /**
     * isVisited is a 2D vector, it keeps track of the squares are visited during the BFS, initially all the squares are initialized to false\
     * because at first none of the squares are visited, then step by step each time a square is visited , we assign the value true to it
     * to avoid any inifinit loops
    */
    std::vector<std::vector<bool>> isVisited(8, std::vector<bool>(8, false));

    moves.push({start}); // pushing the start point of our move of the path to the queue
    isVisited[start.x][start.y] = true;// since this square (start point) is pushed to the queue and we visited it, we need to assign value true to it

    while (!moves.empty())// while the queue of moves is not empty, we keep doing the below steps to reach the dstination
    {
        std::vector<CoordinateXY> currentPath = moves.front(); // current path is the first path in the queue
        CoordinateXY current = currentPath.back();
        moves.pop();
        // if the condition is true  it means we reached the destination
        if (current.x == destination.x && current.y == destination.y)
        {
            return currentPath;
        }
        // if we haven't reached the destination yet, we need keep making new moves
        for (int i = 0; i < 8; i++)
        {
            int nextMove_x = current.x + allPossibleMoves[i][0];// the new value of x coordinates of the new move
            int nextMove_y = current.y + allPossibleMoves[i][1];// the new value of y coordinates of the new move
            //we need to make sure new moves x and y coordinates are valid, in other words we check we didn't move to the out of the chessboard
            if (isValid(nextMove_x, nextMove_y) && !isVisited[nextMove_x][nextMove_y]) 
            {
                isVisited[nextMove_x][nextMove_y] = true; // so if the new moves' coordinates are valid, mark them as visited
                std::vector<CoordinateXY> nextPath = currentPath;// create a new path to show the next move of the knight
                nextPath.push_back({nextMove_x, nextMove_y}); // add the next move (coordinates)to the end of the nextPath vector 
                moves.push(nextPath);// pushing the next path the queue of moves we had from beginning
            }
        }
    }
    return path; // and at the end return the path we found
}
int main()
{
   /**
    * Declaring necessary varaibles
   */
    int currentX;
    int currentY;
    int destinationX;
    int destinationY;
    
    /**
     * Asking users for the inputs, dimension of two valid squares
    */
    std::cout << "Enter the current Knight's location (with format 'x y'): ";
    std::cin >> currentX >> currentY;
    std::cout << "Enter the destination  location(with format 'x y'): ";
    std::cin >> destinationX >> destinationY;
    
    /**
     * making objects start and destination based on the coordinates we've got from users
    */
    CoordinateXY start(currentX, currentY);
    CoordinateXY destinaton(destinationX, destinationY);
   
   // calling the knight_moves function with the start and destination obj 
    std::vector<CoordinateXY> path = knight_moves(start, destinaton);

    if (!path.empty())// if path is not empty we keep printing the moves, and total number of moves
    {
        std::cout << "You made it in " << path.size() - 1 << " moves from [" << currentX << ", " << currentY << "] to [" << destinationX << ", " << destinationY << "]!"
                  << " Here is your path: " << std::endl;
        for (int i = 0; i < path.size(); i++)// groing through the path vector to print the moves
        {
            std::cout << "[" << path[i].x << ", " << path[i].y << "]" << std::endl;
        }
    }
    else// if path is empty, we couldn't find any paths
    {
        std::cout << "No Path Found" << std::endl;
    }

    return 0;
}