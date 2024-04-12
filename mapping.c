#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mapping.h"
#include "math.h"
#include <stdlib.h>

struct Map populateMap()
{
	struct Map result = {
			// 0	1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4
			// A B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y
			{
					{0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 0
					{0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0}, // 1
					{0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0}, // 2
					{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 3
					{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 4
					{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 5
					{1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0}, // 6
					{1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1}, // 7
					{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1}, // 8
					{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 9
					{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 10
					{1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1}, // 11
					{1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1}, // 12
					{1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1}, // 13
					{1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1}, // 14
					{1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1}, // 15
					{0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 16
					{0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 17
					{0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // 18
					{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 19
					{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 20
					{0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0}, // 21
					{0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1}, // 22
					{0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1}, // 23
					{0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}	 // 24
			},
			MAP_ROWS,
			MAP_COLS};
	return result;
}

int getNumRows(const struct Map *map)
{
	return map->numRows;
}

int getNumCols(const struct Map *map)
{
	return map->numCols;
}

void printMap(const struct Map *map, const int base1, const int alphaCols)
{
	//              01234567890123456
	//              1248F
	char sym[] = {" XB?G?.?Y?-?*?+?P"};
	int r, c, rowMax;

	rowMax = map->numRows + base1;

	printf("%4s", " ");
	for (c = 0; c < map->numCols; c++)
	{
		if (alphaCols)
			printf("%c", 'A' + c);
		else
			printf("%d", c % 10);
	}
	printf("\n");
	printf("%4s", " ");
	for (c = 0; c < map->numCols; c++)
	{
		printf("-");
	}
	printf("\n");

	for (r = base1; r < rowMax; r++)
	{
		printf("%3d|", r);
		for (c = 0; c < map->numCols; c++)
		{
			printf("%c", sym[map->squares[r - base1][c]]);
		}
		printf("\n");
	}
}

struct Route getBlueRoute()
{
	struct Route result = {
			{
					{0, 0},
					{1, 0},
					{2, 0},
					{3, 0},
					{4, 0},
					{4, 1},
					{4, 2},
					{4, 3},
					{4, 4},
					{4, 5},
					{4, 6},
					{4, 7},
					{4, 8},
					{4, 9},
					{5, 9},
					{6, 9},
					{7, 9},
					{8, 9},
					{9, 9},
					{10, 9},
					{10, 10},
					{11, 10},
					{12, 10},
					{13, 10},
					{14, 10},
					{15, 10},
					{16, 10},
					{17, 10},
					{17, 11},
					{17, 12},
					{17, 13},
					{17, 14},
					{17, 15},
					{17, 16},
					{17, 17},
					{17, 18},
					{17, 19},
					{17, 20},
					{17, 21},
					{17, 22},
					{17, 23},
					{17, 24},
			},
			42,
			BLUE};
	return result;
}

struct Route getGreenRoute()
{
	struct Route result = {
			{{0, 0},
			 {1, 0},
			 {2, 0},
			 {3, 0},
			 {4, 0},
			 {4, 1},
			 {4, 2},
			 {4, 3},
			 {4, 4},
			 {4, 5},
			 {4, 6},
			 {4, 7},
			 {4, 8},
			 {4, 9},
			 {4, 10},
			 {4, 11},
			 {3, 11},
			 {2, 11},
			 {1, 11},
			 {0, 11},
			 {0, 12},
			 {0, 13},
			 {0, 14},
			 {0, 15},
			 {0, 16},
			 {0, 17},
			 {0, 18},
			 {0, 19},
			 {1, 19},
			 {2, 19},
			 {3, 19},
			 {4, 19},
			 {5, 19},
			 {6, 19},
			 {7, 19},
			 {8, 19},
			 {9, 19},
			 {9, 20},
			 {9, 21},
			 {9, 22},
			 {9, 23},
			 {9, 24}

			},
			42,
			GREEN};
	return result;
}

struct Route getYellowRoute()
{
	struct Route result = {
			{{0, 0},
			 {1, 0},
			 {2, 0},
			 {3, 0},
			 {4, 0},
			 {4, 1},
			 {4, 2},
			 {4, 3},
			 {5, 3},
			 {6, 3},
			 {7, 3},
			 {8, 3},
			 {9, 3},
			 {9, 2},
			 {9, 1},
			 {10, 1},
			 {11, 1},
			 {12, 1},
			 {13, 1},
			 {14, 1},
			 {15, 1},
			 {16, 1},
			 {17, 1},
			 {18, 1},
			 {19, 1},
			 {19, 2},
			 {19, 3},
			 {19, 4},
			 {19, 5},
			 {19, 6},
			 {19, 7},
			 {19, 8},
			 {19, 9},
			 {19, 10},
			 {19, 11},
			 {19, 12},
			 {19, 13},
			 {19, 14},
			 {19, 15},
			 {19, 16},
			 {19, 17},
			 {19, 18},
			 {19, 19},
			 {19, 20},
			 {19, 21},
			 {19, 22},
			 {19, 23},
			 {19, 24}},
			48,
			YELLOW};
	return result;
}

struct Map addRoute(const struct Map *map, const struct Route *route)
{
	int r, c;
	struct Map result = {{0}, 0};

	for (r = 0; r < map->numRows; r++)
	{
		for (c = 0; c < map->numCols; c++)
		{
			result.squares[r][c] = map->squares[r][c];
		}
	}
	result.numRows = map->numRows;
	result.numCols = map->numCols;

	for (r = 0; r < route->numPoints; r++)
	{
		result.squares[route->points[r].row][route->points[r].col] += route->routeSymbol;
	}

	return result;
}

void addPtToRoute(struct Route *route, struct Point pt)
{
	route->points[route->numPoints++] = pt;
}

void addPointToRoute(struct Route *route, const int row, const int col)
{
	struct Point pt = {row, col};
	addPtToRoute(route, pt);
}

void addPointToRouteIfNot(struct Route *route, const int row, const int col, const struct Point notThis)
{
	struct Point pt = {row, col};
	if (notThis.row != row || notThis.col != col)
		addPtToRoute(route, pt);
}

double distance(const struct Point *p1, const struct Point *p2)
{
	int deltaRow = p2->row - p1->row;
	int deltaCol = p2->col - p1->col;

	return sqrt((double)(deltaRow * deltaRow + deltaCol * deltaCol));
}

struct Route shortestPath(const struct Map *map, const struct Point start, const struct Point dest, struct Building building)
{
	struct Route result = {{0, 0}, 0, DIVERSION};
	struct Point last = {-1, -1};
	struct Point current = start;
	struct Route possible = {{0, 0}, 0, 0};
	int close = 0;

	if (isNextToDes(current, dest))
	{
		return result;
	}

	while (!eqPt(current, dest) && close >= 0)
	{
		possible = getPossibleMoves(map, current, last);
		close = getClosestPoint(&possible, dest, building);

		if (pointOnRoute(possible.points[close], result))
		{
			struct Route deadEnd =
					{
							{0, 0},
							-1,
							DIVERSION};

			return deadEnd;
		}
		else if (close >= 0)
		{
			last = current;
			current = possible.points[close];
			addPtToRoute(&result, current);
			if (isNextToDes(current, dest))
			{
				break;
			}
		}
	}

	if (!isNextToDes(current, dest) && result.numPoints == 0)
	{
		result.numPoints = -1;
	}

	return result;
}

struct Route getPossibleMoves(const struct Map *map, const struct Point p1, const struct Point backpath)
{
	struct Route result = {{0, 0}, 0, DIVERSION};

	if (p1.row > 0)
	{
		if (map->squares[p1.row - 1][p1.col] != 1)
			addPointToRouteIfNot(&result, p1.row - 1, p1.col, backpath); // square above
																																	 // if (p1.col > 0 && map->squares[p1.row - 1][p1.col - 1] != 1)
																																	 // 	addPointToRouteIfNot(&result, p1.row - 1, p1.col - 1, backpath); // top left
																																	 // if (p1.col < (map->numCols - 1) && map->squares[p1.row - 1][p1.col + 1] != 1)
																																	 // 	addPointToRouteIfNot(&result, p1.row - 1, p1.col + 1, backpath); // top right
	}
	if (p1.col > 0 && map->squares[p1.row][p1.col - 1] != 1)
		addPointToRouteIfNot(&result, p1.row, p1.col - 1, backpath); // left
	if (p1.col < (map->numCols - 1) && map->squares[p1.row][p1.col + 1] != 1)
		addPointToRouteIfNot(&result, p1.row, p1.col + 1, backpath); // right
	if (p1.row < (map->numRows - 1))
	{
		if (map->squares[p1.row + 1][p1.col] != 1)
			addPointToRouteIfNot(&result, p1.row + 1, p1.col, backpath); // square below
																																	 // if (p1.col > 0 && map->squares[p1.row + 1][p1.col - 1] != 1)
																																	 // 	addPointToRouteIfNot(&result, p1.row + 1, p1.col - 1, backpath); // bot left
																																	 // if (p1.col < (map->numCols - 1) && map->squares[p1.row + 1][p1.col + 1] != 1)
																																	 // 	addPointToRouteIfNot(&result, p1.row + 1, p1.col + 1, backpath); // top right
	}

	return result;
}

int eqPt(const struct Point p1, const struct Point p2)
{
	return p1.row == p2.row && p1.col == p2.col;
}

struct Building findBuildingBoundaries(struct Map map, struct Point point)
{
	struct Building building = {
			{-1, -1}, // topRight
			{-1, -1}, // topLeft
			{-1, -1}, // bottomRight
			{-1, -1}	// bottomLeft
	};

	if (map.squares[point.row][point.col] != 1)
	{
		// The point is not in a building.
		return building;
	}

	// Start with the given point as all corners.
	building.topLeft = point;
	building.topRight = point;
	building.bottomLeft = point;
	building.bottomRight = point;

	// Expand out to find the furthest points that are still '1'.
	for (int row = point.row; row >= 0; --row)
	{
		if (map.squares[row][point.col] == 1)
		{
			building.topLeft.row = row;
			building.topRight.row = row;
		}
		else
		{
			break; // Reached the top boundary.
		}
	}

	for (int row = point.row; row < MAP_ROWS; ++row)
	{
		if (map.squares[row][point.col] == 1)
		{
			building.bottomLeft.row = row;
			building.bottomRight.row = row;
		}
		else
		{
			break; // Reached the bottom boundary.
		}
	}

	for (int col = point.col; col >= 0; --col)
	{
		if (map.squares[point.row][col] == 1)
		{
			building.topLeft.col = col;
			building.bottomLeft.col = col;
		}
		else
		{
			break; // Reached the left boundary.
		}
	}

	for (int col = point.col; col < MAP_COLS; ++col)
	{
		if (map.squares[point.row][col] == 1)
		{
			building.topRight.col = col;
			building.bottomRight.col = col;
		}
		else
		{
			break; // Reached the right boundary.
		}
	}

	return building;
}

int getClosestPoint(const struct Route *route, const struct Point pt, struct Building building)
{
	int i, closestIdx = -1;
	double closestDist = 999999.99, dist;

	for (i = 0; i < route->numPoints; i++)
	{
		dist = distance(&pt, &route->points[i]);

		if (isNextToDes(route->points[i], pt))
		{
			closestDist = dist;
			closestIdx = i;
		}
		else if (dist < closestDist)
		{
			if (pointAtBuildBottom(pt, building))
			{

				closestDist = dist;
				closestIdx = i;
			}
			else
			{
				if (!(willReachEdgeCanNotGoUp(route->points[i], building)))
				{
					closestDist = dist;
					closestIdx = i;
				}
			}

			// !pointAtBuildBottom(route->points[i], building)
			// !(willReachEdgeCanNotGoUp(route->points[i], building))
		}
	}
	return closestIdx;
}

/**********************
 * Functions I added
 *********************/

int letterToIndex(char letter)
{
	letter = toupper(letter); // Convert the letter to uppercase to simplify conversion
	if (letter >= 'A' && letter <= 'Z')
	{
		return letter - 'A';
	}
	else
	{
		return -1; // Return -1 if the input is not a letter
	}
}

char indexToLetter(int index)
{
	if (index >= 0 && index <= 25)
	{
		return 'A' + index;
	}
	else
	{
		return '?'; // Return '?' if the index is not valid
	}
}

int pointOnRoute(struct Point pt, struct Route route)
{
	for (int i = 0; i < route.numPoints; i++)
	{

		if (eqPt(pt, route.points[i]))
		{
			return 1;
		}
	}
	return 0;
};

int isNextToDes(struct Point p1, struct Point des)
{
	if ((abs(p1.col - des.col) <= 1 && p1.row == des.row) || (abs(p1.row - des.row) <= 1 && p1.col == des.col))
	{
		return 1;
	}
	else
	{
		return 0;
	};
}

void printPointOnRoute(const struct Route route)
{
	if (route.numPoints > 0)
	{
		for (int i = 0; i < route.numPoints; i++)
		{
			printf("row %d, col %c\n", route.points[i].row + 1, indexToLetter(route.points[i].col));
		}
	}
}

int willReachEdgeCanNotGoUp(struct Point pt, struct Building building)
{
	int buildingWidth = building.bottomRight.col - building.bottomLeft.col;
	if (pt.col + buildingWidth >= 24 && pt.row > building.bottomRight.row)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int pointAtBuildBottom(struct Point pt, struct Building building)
{
	return pt.row == building.bottomRight.row;
}