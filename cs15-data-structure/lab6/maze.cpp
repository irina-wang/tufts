//  ------------------
//  Comp15 spring 2019
//  Recursion and Mazes Lab 
//  maze.cpp
//  Implementation of Maze class: creates a maze and 
//               has several recursion functions to solve it
//               (students must implement those)
//
//  MazeCreator originally created by Chris Gregg on 2/7/14
//  Further edits by: 
//        Eliza Schreibman and Mark A. Sheldon Feb 2017
//        Tanya Sinha and Matias Korman Feb 2019
//  Modified by:
//         Irina Mengqi Wang
//
// -------------------


#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <ctime>

#include "position.h"
#include "maze.h"

#ifdef RANDOM
static const bool really_random = true;
#else
static const bool really_random = false;
#endif

using namespace std;

Maze::Maze(int size)
{
        if (really_random)
                srand(time(NULL));
        else
                srand(0U);

	maze_size = size;
	maze_array_size = maze_size * 2 + 1; // the actual size of the array, 
        generate_maze();
}

/*
 * A way to index the maze using a Position rather than 
 * specifiying the row and column separately.
 * Useful for functions that want to pass and return Positions.
 */
char &Maze::mazeAt(Position p)
{
        return maze[p.row][p.col];
}

/*
 * Solve the maze.
 *
 * Note:  Need to reset the start position to 'S', because
 *        the solve() function below sets it to '.'
 */
void Maze::solve()
{
        // solve(1, 1);
        solve(Position(1, 1));
        maze[1][1] = START;
}

/*
 *  TODO:  Implement this version of the solve() function
 *         or the one above that uses separate row and column indices,
 *         whichever you prefer.
 *
 * solve() assumes an unsolved maze initialized with  
 * a start position of (1, 1).
 * Dead-end paths that have been tested should be marked
 * with lowercase 'b'.
 * The correct path should be marked with periods (.)
 *
 * Be careful! 2d arrays seem backwards and upside down
 * compared to cartesian coordinates:
 * maze[0][0] == top left
 * maze[1][0] == one down, zero to the right
 * maze[0][1] == zero down, one to the right
 * maze[row][col] == row down and col to the right
 */

/*
 *  TODO:  Implement this version of the solve() function
 *         OR the one above that uses separate row and column indices,
 *         whichever you prefer.
*/
bool Maze::solve(Position p)
{
   if (!p.inBounds(maze_array_size, maze_array_size)) {
		return false;
	} else if (mazeAt(p) == WALL || mazeAt(p) == PATH || 
	           mazeAt(p) == REJECT) {
		return false;
	} else if (mazeAt(p) == FINISH) {
		return true;
	} else {
		mazeAt(p) = PATH;
		if (solve(p.north()) || solve(p.east()) || 
		    solve(p.south()) || solve(p.west())) {
			return true;
		}
		mazeAt(p) = REJECT;
		return false;
	} 
}

bool Maze::inBounds(Position p) {
	return (0 < p.row) and (p.row < maze_size)
            and (0 < p.col) and (p.col < maze_size);
}

/*
 * Return the length of the path from start to finish.
 */
int Maze::path_length()
{
        return num_dots_by_rows(1) + 1;
};

/*
 * Return the number of dots in the maze starting at given row.
 * Note:  Recurses on row index.
 *
 * TODO
 */
int Maze::num_dots_by_rows(int row)
{
        // STUB --- Remove entire body and implement
        (void) row;
		int num = 0;
		
		if (row < 0 || row > maze_size)
			return 0;
		else{
			num += num_dots_in_row(row+1, 1);
			return num ;
		}
		
        return NOT_FOUND;
}

/*
 * Return the number of dots in a given row starting at given column.
 * Note:  Recurses on column index.
 *
 * TODO
 */
int Maze::num_dots_in_row(int row, int col)
{
        // STUB --- Remove entire body and implement
        (void) row;
        (void) col;
		int num = 0;
		
		if (col < 0 || col > maze_size)
			return 0;
		if (maze[row][col] == PATH)
			return 1;
		else {
			num += num_dots_in_row(row, col+1);
			return num;
		}

        return NOT_FOUND;
}


/*
 * For fun:
 *
 * Assume maze is not solved.
 * Recursively solve the maze AND count the final path length.
 * Return the length of the final path, i. e., the number of '.'s
 * plus 1.
 */
int Maze::solve_and_count()
{
        int distance;

        // distance = solve_and_count(1, 1);
        distance = solve_and_count(Position(1, 1));

        maze[1][1] = START;
        return distance;
};

/*
 *  TODO  Solve the maze and return the path starting at given position
 *        Do this one OR the version using a Position below.
 */
int Maze::solve_and_count(int row, int col)
{
        // STUB --- Remove entire body and implement
        (void) row;  (void) col;
        return 0;
}

bool Maze::succeeds(int distance)
{
        return distance != NOT_FOUND;
}

/*
 *  TODO  Solve the maze and return the path starting at given position
 *        Do this one OR the version using row and col above.
 */
int Maze::solve_and_count(Position p)
{
        // STUB --- Remove entire body and implement
        (void) p;

        return NOT_FOUND;
}

/*************************************************************/
/*** The code below here was originally taken from         ***/
/*** https://azerdark.wordpress.com/2009/03/29/588/        ***/
/***                                                       ***/
/*** Chris Gregg added a function to convert the           ***/
/*** original mazes from an integer-based representation   ***/
/*** to a character-based one so we could have ASCII       ***/
/*** output.                                               ***/
/***                                                       ***/
/*** Mark A. Sheldon changed the principle representation  ***/
/*** to be character-based and reorganized the code to be  ***/
/*** more modular, to have abstraction boundaries, and to  ***/
/*** have better variable names.                           ***/
/***                                                       ***/
/*** You are not expected do understand this code.         ***/
/*************************************************************/

/*
 * Generates a maze
 */
void Maze::generate_maze()
{
	int index = 0;
	int backtrack_x[MAX_CELLS];
	int backtrack_y[MAX_CELLS];

        initialize_maze();

	backtrack_x[index] = 1;
	backtrack_y[index] = 1;
	maze_generator(index, backtrack_x, backtrack_y, 1, 1, maze_size, 1);

        install_start_finish();
}

/*
 * Set up a maze including walls and border
 */
void Maze::initialize_maze()
{
	for (int row = 0; row < MAX_ARRAY_SIZE; ++row) {
		for (int col = 0; col < MAX_ARRAY_SIZE; ++col) {
			if (row % 2 == 0 or col % 2 == 0)
				maze[row][col] = WALL;
			else
				maze[row][col] = EMPTY;
		}
	}
}

/*
 * Currently, we always start in the upper left corner (inside the
 * border walls) and finish in the lower right cornder (also inside
 * the border walls).
 */
void Maze::install_start_finish()
{
        maze[1][1] = START;
        maze[maze_array_size - 2][maze_array_size - 2] = FINISH;
}

/*
 * This is the actual maze generator.  It uses a backtracking search
 * with some randomness togenerate the maze.
 */
void Maze::maze_generator(int index, int backtrack_x[MAX_CELLS],
                          int backtrack_y[MAX_CELLS], int x, int y, int n,
                          int visited)
{
	if (visited < n * n) {
		int neighbour_valid = -1;
		int neighbour_x[4];
		int neighbour_y[4];
		int step[4];

		int x_next;
		int y_next;

		if (x - 2 > 0 and is_closed(x - 2, y)) {   // upside
			neighbour_valid++;
			neighbour_x[neighbour_valid] = x - 2;;
			neighbour_y[neighbour_valid] = y;
			step[neighbour_valid] = 1;
		}

		if (y - 2 > 0 and is_closed(x, y - 2)) {   // leftside
			neighbour_valid++;
			neighbour_x[neighbour_valid] = x;
			neighbour_y[neighbour_valid] = y - 2;
			step[neighbour_valid] = 2;
		}

		if (y + 2 < n * 2 + 1 and is_closed(x, y + 2)) { // rightside
			neighbour_valid++;
			neighbour_x[neighbour_valid] = x;
			neighbour_y[neighbour_valid] = y + 2;
			step[neighbour_valid] = 3;
		}

		if (x + 2 < n * 2 + 1 and is_closed(x + 2, y)) { // downside
			neighbour_valid++;
			neighbour_x[neighbour_valid] = x + 2;
			neighbour_y[neighbour_valid] = y;
			step[neighbour_valid] = 4;
		}

		if (neighbour_valid == -1) {
			// backtrack
			x_next = backtrack_x[index];
			y_next = backtrack_y[index];
			index--;
		}
		if (neighbour_valid != -1) {
			int randomization = neighbour_valid + 1;
			int random = rand() % randomization;
			x_next = neighbour_x[random];
			y_next = neighbour_y[random];
			index++;
			backtrack_x[index] = x_next;
			backtrack_y[index] = y_next;

			int rstep = step[random];

			if (rstep == 1)
				maze[x_next + 1][y_next] = EMPTY;
			else if (rstep == 2)
				maze[x_next][y_next + 1] = EMPTY;
			else if (rstep == 3)
				maze[x_next][y_next - 1] = EMPTY;
			else if (rstep == 4)
				maze[x_next - 1][y_next] = EMPTY;
			visited++;
		}

		maze_generator(index, backtrack_x, backtrack_y,
				x_next, y_next, n, visited);
	}
}

/*
 * Print the maze to standard output.
 */
void Maze::print()
{
	for (int row = 0; row < maze_array_size; ++row) {
		for (int col = 0; col < maze_array_size; ++col) {
			cout << maze[row][col];
		}
		cout << endl;
	}
        cout << endl;
}

/*
 * Checks if the position is a wall (marked with a 'X') and
 * returns 1 if the position is a wall, 0 otherwise.
 */
int Maze::is_closed(int x, int y)
{
	if (maze[x - 1][y]  == WALL
            and maze[x][y - 1] == WALL
            and maze[x][y + 1] == WALL
            and maze[x + 1][y] == WALL)
		return 1;

	return 0;
}

/* 
 * Checks if two mazes are identical by checking the contents
 * of every position in the maze. 
 */
bool Maze::isSameSolutionAs(Maze anotherMaze)
{
	for (int row = 0; row < maze_array_size; row++) {
		for (int col = 0; col < maze_array_size; col++) {
			if (maze[row][col] != anotherMaze.maze[row][col]) {
				return false;
			}
		}
	}
	return true;
}
