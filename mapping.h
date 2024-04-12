#pragma once
#ifndef MAPPING_H
#define MAPPING_H

#define MAP_ROWS 25
#define MAP_COLS 25
#define MAX_ROUTE 100
#define BLUE 2
#define GREEN 4
#define YELLOW 8
#define DIVERSION 16
#include <ctype.h>

/**
 * A map is a 2D raster representation of a map with contents of the map encoded as numeric values.
 */
struct Map
{
	int squares[MAP_ROWS][MAP_COLS];
	int numRows;
	int numCols;
};

/**
 * A point represents the row-column position of a square on a map.
 */
struct Point
{
	int row;
	int col;
};
struct Building
{
	// top right
	struct Point topRight;
	// top left
	struct Point topLeft;
	// buttom right
	struct Point bottomRight;
	// buttom left
	struct Point bottomLeft;
};

/**
 * A route is a collection of points that are adjacent to one another and constitute a path from the
 * first point on the path to the last.
 */
struct Route
{
	struct Point points[MAX_ROUTE];
	int numPoints;
	char routeSymbol;
};

struct ShortestRouteInfo
{
	struct Route shortestRoute;
	struct Point start;
	struct Point end;
};

/**
 * Create a map with the position of all buildings in it.
 * @returns - a map with the position of all buildings added to it.
 */
struct Map populateMap();

/**
 * Get the number of rows in a map.
 * @param map - the map to query
 * @returns - the number of rows in the map.
 */
int getNumRows(const struct Map *map);

/**
 * Get the number of columns in a map.
 * @param map - the map to query
 * @returns - the number of columns in the map.
 */
int getNumCols(const struct Map *map);

/**
 * Print the map usign the symbols:
 * space = open space
 * X = building
 * B = blue route
 * G = green route
 * Y = yellow route
 * . = B & G routes overlap
 * - = B & Y routes overlap
 * * = G & Y routes overlap
 * + = B & G & Y routes overlap
 * P = a shortest path or route from one point to another
 * @param map - map to print
 * @param base1 - if true print row indices from 1 up otherwise 0 up
 * @param alphaCols - if true print col header as letters, otherwise numbers
 */
void printMap(const struct Map *map, const int base1, const int alphaCols);

/**
 * Add a route to a map using the indicated symbol.
 * @param map - map to add route to
 * @param route - the route to add to the map
 * @returns a copy of the original map with the route added to it
 */
struct Map addRoute(const struct Map *map, const struct Route *route);

/**
 * Add a point to a route
 * @param route - the route to which the point should be added
 * @param point - the point to add to the route.
 */
void addPtToRoute(struct Route *route, struct Point pt);

/**
 * Add a point to a route if it is not equal to another point.
 * @param route - the route to which the point should be added
 * @param row - the row of the point to add to the route.
 * @param col - the column of the point to add to the route.
 * @param notThis - the point will be added to the route ONLY if it is not equal to this point.
 */
void addPointToRouteIfNot(struct Route *route, const int row, const int col, const struct Point notThis);

/**
 * Add a point to a route
 * @param route - the route to which the point should be added
 * @param point - the point to add to the route.
 */
void addPointToRoute(struct Route *route, const int row, const int col);

/**
 * Build and return the route for the blue trucks.
 * @returns - the route for the blue trucks.
 */
struct Route getBlueRoute();

/**
 * Build and return the route for the green trucks.
 * @returns - the route for the green trucks.
 */
struct Route getGreenRoute();

/**
 * Build and return the route for the yellow trucks.
 * @returns - the route for the yellow trucks.
 */
struct Route getYellowRoute();

/**
 * Calculate the Euclidian distance between two points.
 * @param p1 - the first point
 * @param p2 - the second point
 * @returns - the distance between p1 and p2.
 */
double distance(const struct Point *p1, const struct Point *p2);

/**
 * Calculate the shortest path between two points so that the path does not pass through buildings.
 * @param map - the map showing the location of buildings.
 * @param start - the point to start from
 * @param dest - the point to go to
 * @returns - the shortest path from start to dest. If there is no path, then a Route of zero length is returned.If start
 * and dest are the same point, it also returns a Route of zero length.
 */
struct Route shortestPath(const struct Map *map, const struct Point start, const struct Point dest, struct Building building);

/**
 * Calculate all adjacent squares to a given point so that the squares do not overpal a building and do not include the backpath.
 * @param map - the map showing the location of buildings.
 * @param p1 - the point to calculate possible moves for
 * @param backpath - the previous point we visited on the path we travelled so we will exclude travelling backwards.
 * @returns - a collection of adjacent points we could potentially move to.
 */
struct Route getPossibleMoves(const struct Map *map, const struct Point p1, const struct Point backpath);

/**
 * Compare two points for equality.
 * @param p1 - the first point
 * @param p2 - the second point
 * @returns - true if p1 is equal to p2
 */
int eqPt(const struct Point p1, const struct Point p2);

/**
 * Calculates the Euclidian distance from every point in a route to a single point and returns the
 * index of the point in the route which is closest to the point.
 * @param route - the route to use to find the closest point
 * @param pt - the point to to find the member of the route which is closest to this point
 * @returns - the index of the closest point on the route to the point or -1 if the route is empty.
 */
int getClosestPoint(const struct Route *route, const struct Point pt, struct Building building);

/**********************
 * Functions I added
 *********************/
/**
 * Converts a letter to its corresponding index number.
 * 'A' becomes 0, 'B' becomes 1, etc.
 * Assumes the input is an uppercase letter. If not, it first converts
 * it to uppercase.
 *
 * @param letter The letter to convert.
 * @return The index of the letter in the alphabet starting from 0, or -1 if the input is not a letter.
 */
int letterToIndex(char letter);

/**
 * Converts an index number to its corresponding letter.
 * 0 becomes 'A', 1 becomes 'B', etc., up to 25 becoming 'Z'.
 * This function assumes the index is within the range of 0 to 25, inclusive.
 * If the index is outside of this range, it returns '?' as an indicator of an invalid index.
 *
 * @param index The index number to convert to a letter.
 * @return The letter corresponding to the given index, or '?' if the index is not valid.
 */
char indexToLetter(int index);

/**
 * Checks if a given point is adjacent to the destination point on a grid.
 * A point is considered adjacent to the destination if it is either directly
 * to the left, right, above, or below the destination point, not including
 * diagonal adjacency.
 *
 * This function calculates the absolute difference in column and row values
 * to determine adjacency. For two points to be considered adjacent, they must
 * either be in the same row and adjacent columns, or in the same column and
 * adjacent rows.
 *
 * @param p1 The point from which adjacency to the destination is being checked.
 * @param des The destination point to check adjacency against.
 * @return Returns 1 (true) if the point is adjacent to the destination, or
 *         0 (false) if it is not.
 */
int isNextToDes(struct Point p1, struct Point des);

/**
 * Checks if a point is on the specified route.
 *
 * This function iterates through all points in the given route and
 * compares each with the specified point. If the point matches any
 * point in the route based on the row and column values, the function
 * returns 1, indicating the point is on the route. Otherwise, it returns 0.
 *
 * @param pt The point to check, defined by its row and column coordinates.
 * @param route The route to check against, containing a collection of points.
 * @return Returns 1 if the point is on the route, and 0 if it is not.
 */
int pointOnRoute(struct Point pt, struct Route route);

/**
 * Prints all the points along a given route.
 * This function iterates through the points in the route and prints each point's
 * row and column. The row is presented as a 1-based index, and the column is
 * converted from an index to a letter (e.g., 0 becomes 'A', 1 becomes 'B', etc.).
 * This is designed to provide a human-readable display of the route points on a grid.
 *
 * @param route The route whose points are to be printed.
 *              It is expected that the route contains a valid number of points
 *              and that each point's column index is within the range 0 to 25, inclusive.
 */
void printPointOnRoute(const struct Route route);

struct Building findBuildingBoundaries(struct Map map, struct Point point);

int pointAtBuildBottom(struct Point pt, struct Building building);
int willReachEdgeCanNotGoUp(struct Point pt, struct Building building);
#endif
