#pragma once
#ifndef DELIVERY_SCHEDULER_H
#define DELIVERY_SCHEDULER_H

#include "mapping.h"

#define MAX_WEIGHT 1200
#define MAX_VOLUME 50

// Represents the status of a truck in terms of available weight and volume.
struct TruckStatus
{
  double availableWeight;
  double availableVolume;
};

// Represents the package to be delivered.
struct Package
{
  double weight;
  double volume;
  struct Point destination;
  struct Building building;
};

// Represents the overall status of the delivery operation.
struct DeliveryStatus
{
  struct TruckStatus blueTruckStatus;
  struct TruckStatus greenTruckStatus;
  struct TruckStatus yellowTruckStatus;
};

/**
 * Initialize the truck statuses with the maximum weight and volume.
 */
struct DeliveryStatus initializeDeliveryStatus();

/**
 * Validate the weight of the package.
 * @param weight - the weight of the package to validate
 * @returns - true if the weight is valid, false otherwise.
 */
int validatePackageWeight(double weight);

/**
 * Validate the volume of the package.
 * @param volume - the volume of the package to validate
 * @returns - true if the volume is valid, false otherwise.
 */
int validatePackageVolume(double volume);

/**
 * Validate the destination of the package.
 * @param map - the map showing the location of buildings and routes.
 * @param destination - the destination point to validate.
 * @returns - true if the destination is valid, false otherwise.
 */
int validateDestination(const struct Map *map, const struct Point destination);

/**
 * Check if the truck is available to fit the package based on its weight and
 * volume.
 * @param package - the package to check
 * @param status - the current status of the trucks
 * @param truckColor - the color of the truck to check
 * @returns - true if there the truck is available, false otherwise.
 */
int isTruckAvailable(const struct Package package,
                     const struct DeliveryStatus status, char truckColor);

/**
 * Get user input for the shipment details.
 * @param package - pointer to a Package struct where input will be stored.
 * @param map - pointer to the Map struct representing the delivery area.
 * @returns - 1 if the user chooses to stop input, 0 otherwise.
 */
int getUserInput(struct Package *package, const struct Map *map);

/**
 * Decides which truck should be used for delivery based on the shortest path to the destination,
 * the availability of each truck, and their capacities. If trucks have paths of equal length,
 * the tie is broken based on the trucks' available capacity. If no truck is available, it attempts
 * to find the next best option based on the criteria of shortest path and capacity.
 *
 * @param package The package to be delivered, containing its weight, volume, and destination.
 * @param status The current status of all trucks, including their available weight and volume.
 * @param map The map of the city with buildings and routes for the trucks.
 * @param routes An array of routes for each truck (index 0 for blue, 1 for green, 2 for yellow).
 *
 * @return The index of the truck that should deliver the package (0 for blue, 1 for green, 2 for yellow).
 *         It also prints the delivery route for the chosen truck.
 */
int decideTruckForDelivery(const struct Package package,
                           struct DeliveryStatus status, const struct Map *map, const struct Route routes[3]);

/**
 * Calculates the shortest path from any point in a given truck route to a specified destination,
 * considering obstacles as defined in the map. It returns the shortest path information, including
 * the starting point of the shortest path on the truck route, the destination, and the route itself.
 *
 * The function iterates through each point on the truck route, calculates the shortest path from
 * that point to the destination using the shortestPath function, and keeps track of the shortest
 * path found. It updates the shortest path information whenever a shorter path is discovered.
 *
 * @param truckRoute The route of the truck, including all its points.
 * @param map The map of the area, including obstacles, to calculate the path within.
 * @param destination The point to which the shortest path is sought.
 * @return A struct containing information about the shortest route found. This includes:
 *         - The starting point of the shortest route on the truck's route.
 *         - The end point of the shortest route (the destination).
 *         - The shortest route itself as a sequence of points.
 */
struct ShortestRouteInfo truckShortestPath(struct Route truckRoute, const struct Map *map, const struct Point destination, const struct Building building);

/**
 * Update the truck status based on the package to be delivered.
 * @param truckIndex - the index of the truck (0 for blue, 1 for green, 2 for
 * yellow)
 * @param package - the package that is being added to the truck
 * @param status - the current delivery status
 */
void updateTruckStatus(int truckIndex, const struct Package package,
                       struct DeliveryStatus *status);

/**
 * Compares the remaining capacity (both weight and volume) of two trucks to determine
 * which truck has more available capacity. The comparison is based on the usage percentage
 * of the truck's maximum weight and volume capacities.
 *
 * @param truck1 A pointer to the TruckStatus struct representing the first truck.
 * @param truck2 A pointer to the TruckStatus struct representing the second truck.
 * @return int Returns 1 if the first truck has more available capacity, -1 if the second
 *         truck has more available capacity, or 0 if both trucks have the same available capacity.
 */
int compareTruckCapacity(const struct TruckStatus *truck1, const struct TruckStatus *truck2);

/**
 * Prints the delivery route information for a package, indicating which truck line to use
 * and the path for any necessary diversion from the truck's regular route to reach the destination.
 * The function identifies the truck line based on the index provided and prints the diversion path
 * starting from the initial diversion point on the truck's route, through any intermediate points, to the destination.
 *
 * The function supports three truck lines identified by their indices: 0 for the blue line,
 * 1 for the green line, and 2 for the yellow line. It prints an error message for any other index values.
 *
 * @param truckIndex The index of the truck line to use for delivery (0 for blue, 1 for green, 2 for yellow).
 * @param routeInfo The structure containing information about the shortest route for delivery,
 *                  including the start point on the truck route, the end point (destination),
 *                  and the sequence of points constituting the shortest path.
 */
void printDeliveryRoute(int truckIndex, struct ShortestRouteInfo routeInfo);

/**
 * Finds the index of the shortest length in an array.
 * Assumes the array has exactly three elements and returns the index
 * of the element with the smallest value.
 *
 * @param lengthArray An array of integers representing lengths.
 * @return The index of the shortest length in the array.
 */
int shorstestIndex(int *lenghtArray);

/**
 * Checks if there is a tie for the shortest length in an array of three integers.
 * A tie occurs if any two lengths are equal. This function assumes the array has
 * exactly three elements.
 *
 * @param lengthArray An array of integers representing lengths.
 * @return Returns 1 (true) if there is a tie for the shortest length, or
 *         0 (false) if all lengths are distinct.
 */
int tieOnTheShortest(int *lenghtArray);

#endif
