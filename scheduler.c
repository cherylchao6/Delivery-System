#include "scheduler.h"
#include "mapping.h"
#include <ctype.h>
#include <stdio.h>

struct DeliveryStatus initializeDeliveryStatus()
{
  struct DeliveryStatus status;
  status.blueTruckStatus.availableWeight = MAX_WEIGHT;
  status.blueTruckStatus.availableVolume = MAX_VOLUME;
  status.greenTruckStatus.availableWeight = MAX_WEIGHT;
  status.greenTruckStatus.availableVolume = MAX_VOLUME;
  status.yellowTruckStatus.availableWeight = MAX_WEIGHT;
  status.yellowTruckStatus.availableVolume = MAX_VOLUME;

  return status;
}

int validateDestination(const struct Map *map, const struct Point destination)
{
  // First, check if the destination is within the map boundaries.
  if (destination.row < 0 || destination.row >= map->numRows ||
      destination.col < 0 || destination.col >= map->numCols)
  {
    return 0; // Destination is out of map range.
  }

  // Check if the destination is not a building
  if (map->squares[destination.row][destination.col] != 1)
  {
    return 0;
  }

  return 1; // Destination is valid.
}

int validatePackageWeight(double weight)
{
  if (weight > 0 && weight <= MAX_WEIGHT)
  {
    return 1; // Valid weight
  }
  else
  {
    return 0; // Invalid weight
  }
}

int validatePackageVolume(double volume)
{
  if (volume == 0.5 || volume == 1.0 || volume == 5.0)
  {
    return 1; // Valid volume
  }
  else
  {
    return 0; // Invalid volume
  }
}

int isTruckAvailable(const struct Package package, const struct DeliveryStatus status, char truckColor)
{
  // Check if the specified truck is available
  switch (truckColor)
  {
  case 'B': // Blue truck
    return (status.blueTruckStatus.availableWeight - package.weight >= 0) &&
           (status.blueTruckStatus.availableVolume - package.volume >= 0);

  case 'G': // Green truck
    return (status.greenTruckStatus.availableWeight - package.weight >= 0) &&
           (status.greenTruckStatus.availableVolume - package.volume >= 0);

  case 'Y': // Yellow truck
    return (status.yellowTruckStatus.availableWeight - package.weight >= 0) &&
           (status.yellowTruckStatus.availableVolume - package.volume >= 0);

  default:
    // If an invalid color code is provided, return false.
    return 0;
  }
}

int getUserInput(struct Package *package, const struct Map *map)
{
  int weightIsValid, volumeIsValid, desIsvalid, inputIsValid = 0, end = 0;

  char input[10];
  while (!inputIsValid)
  {
    printf("Enter shipment weight, box size and destination (0 0 x to stop): ");

    if (scanf("%lf %lf %s", &package->weight, &package->volume, input) != 3)
    {
      // clear buffer
      while (getchar() != '\n')
        ;
      printf("Invalid input format.\n");
      continue;
    }

    // User opts to stop input.
    if (package->weight == 0 && package->volume == 0 && toupper(toupper(input[0]) == 'X'))
    {
      package->destination.row = -1; // Use a specific value to signify the input stop.
      package->destination.col = -1;
      end = 1;
      break; // Exit loop.
    }
    int row;
    char col;
    sscanf(input, "%d%c", &row, &col);
    int colNum = letterToIndex(col);
    package->destination.row = row - 1;
    package->destination.col = colNum;

    // Validate the input using the respective functions.
    weightIsValid = validatePackageWeight(package->weight);
    volumeIsValid = validatePackageVolume(package->volume);
    desIsvalid = validateDestination(map, package->destination);

    // If any validations fail, prompt the user and request re-entry.
    if (!weightIsValid)
    {
      printf("Invalid weight (must be 1-1200 Kg.)\n");
      while (getchar() != '\n')
        ;
      continue; // Skip the rest of the loop and prompt for input again
    }
    else if (!volumeIsValid)
    {
      printf("Invalid size\n");
      while (getchar() != '\n')
        ;
      continue; // Skip the rest of the loop and prompt for input again
    }
    else if (!desIsvalid)
    {
      printf("Invalid destination\n");
      while (getchar() != '\n')
        ;
      continue; // Skip the rest of the loop and prompt for input again
    }
    else
    {
      inputIsValid = 1; // Both validations passed, mark input as valid.
    }
  }

  package->building = findBuildingBoundaries(*map, package->destination);

  return end;
}

int decideTruckForDelivery(const struct Package package, struct DeliveryStatus status, const struct Map *map, const struct Route routes[3])
{
  int index = -1;
  struct Point destination = package.destination;

  // check weight and volumn
  int blueAvailable = isTruckAvailable(package, status, 'B');
  int greenAvailable = isTruckAvailable(package, status, 'G');
  int yellowAvailable = isTruckAvailable(package, status, 'Y');
  struct Building building = package.building;
  // get truck shortest route to the destination
  struct ShortestRouteInfo blueShortestRouteInfo = truckShortestPath(routes[0], map, destination, building);
  struct ShortestRouteInfo greenShortestRouteInfo = truckShortestPath(routes[1], map, destination, building);
  struct ShortestRouteInfo yellowShortestRouteInfo = truckShortestPath(routes[2], map, destination, building);
  int blueShortestLength = blueShortestRouteInfo.shortestRoute.numPoints;
  int greenShortestLength = greenShortestRouteInfo.shortestRoute.numPoints;
  int yellowShortestLength = yellowShortestRouteInfo.shortestRoute.numPoints;

  int lenghtArr[3] = {blueShortestLength,
                      greenShortestLength,
                      yellowShortestLength};

  int shortestIdx = shorstestIndex(lenghtArr);
  if (!tieOnTheShortest(lenghtArr))
  {
    // If blue is the shortest
    if (shortestIdx == 0)
    {
      if (blueAvailable)
      {
        index = 0;
      }
      else if (greenAvailable && greenShortestLength < yellowShortestLength)
      {
        index = 1;
      }
      else if (yellowAvailable)
      {
        index = 2;
      }
    } // If green is the shortest
    else if (shortestIdx == 1)
    {
      if (greenAvailable)
      {
        index = 1;
      }
      else if (blueAvailable && blueShortestLength < yellowShortestLength)
      {
        index = 0;
      }
      else if (yellowAvailable)
      {
        index = 2;
      }
    }
    // If yellow is the shortest
    else if (shortestIdx == 2)
    {
      if (yellowAvailable)
      {
        index = 2;
      }
      else if (blueAvailable && blueShortestLength < greenShortestLength)
      {
        index = 0;
      }
      else if (greenAvailable)
      {
        index = 1;
      }
    }
  }
  else
  {
    if (shortestIdx == 0 && !blueAvailable)
    {
      if (greenShortestLength == yellowShortestLength && greenAvailable && yellowAvailable)
      {
        int capacityComparison = compareTruckCapacity(&status.greenTruckStatus, &status.yellowTruckStatus);
        if (capacityComparison >= 0)
        {
          index = 1;
        }
        else
        {
          index = 0;
        }
      }
    }
    else if (shortestIdx == 1 && !greenAvailable)
    {
      if (blueShortestLength == yellowShortestLength && blueAvailable && yellowAvailable)
      {
        int capacityComparison = compareTruckCapacity(&status.blueTruckStatus, &status.yellowTruckStatus);
        if (capacityComparison >= 0)
        {
          index = 0;
        }
        else
        {
          index = 2;
        }
      }
    }
    else if (shortestIdx == 2 && !yellowAvailable)
    {
      if (blueShortestLength == greenShortestLength && blueAvailable && greenAvailable)
      {
        int capacityComparison = compareTruckCapacity(&status.blueTruckStatus, &status.greenTruckStatus);
        if (capacityComparison >= 0)
        {
          index = 0;
        }
        else
        {
          index = 1;
        }
      }
    }
    else if (blueShortestLength == greenShortestLength && greenShortestLength == yellowShortestLength && blueAvailable && greenAvailable && yellowAvailable)
    {
      int blueBiggerThanYellow = compareTruckCapacity(&status.blueTruckStatus, &status.yellowTruckStatus);
      int blueBiggerThanGreen = compareTruckCapacity(&status.blueTruckStatus, &status.greenTruckStatus);
      int greenBiggerThanYellow = compareTruckCapacity(&status.greenTruckStatus, &status.yellowTruckStatus);

      if (blueBiggerThanYellow > 0 && blueBiggerThanGreen > 0)
      {
        index = 0;
      }
      else if (blueBiggerThanGreen < 0 && greenBiggerThanYellow > 0)
      {
        index = 1;
      }
      else if (blueBiggerThanYellow < 0 && greenBiggerThanYellow < 0)
      {
        index = 2;
      }
      else if (blueBiggerThanGreen == 0 && blueBiggerThanYellow > 0)
      {
        index = 0;
      }
      else if (blueBiggerThanYellow == 0 && blueBiggerThanGreen > 0)
      {
        index = 0;
      }
      else if (greenBiggerThanYellow == 0 && blueBiggerThanGreen < 0)
      {
        index = 1;
      }
      else
      {
        index = 0;
      }
    }
    else if (blueAvailable && shortestIdx == 0)
    {
      if (blueShortestLength == greenShortestLength)
      {
        int capacityComparison = compareTruckCapacity(&status.blueTruckStatus, &status.greenTruckStatus);
        if (capacityComparison >= 0)
        {
          index = 0;
        }
        else
        {
          index = 1;
        }
      }
      else if (blueShortestLength == yellowShortestLength)
      {
        int capacityComparison = compareTruckCapacity(&status.blueTruckStatus, &status.yellowTruckStatus);
        if (capacityComparison >= 0)
        {
          index = 0;
        }
        else
        {
          index = 2;
        }
      }
      else
      {
        index = 0;
      }
    }
    else if (greenAvailable && shortestIdx == 1)
    {
      if (greenShortestLength == blueShortestLength)
      {
        int capacityComparison = compareTruckCapacity(&status.greenTruckStatus, &status.blueTruckStatus);
        if (capacityComparison >= 0)
        {
          index = 1;
        }
        else
        {
          index = 0;
        }
      }
      else if (greenShortestLength == yellowShortestLength)
      {
        int capacityComparison = compareTruckCapacity(&status.greenTruckStatus, &status.yellowTruckStatus);
        if (capacityComparison >= 0)
        {
          index = 1;
        }
        else
        {
          index = 2;
        }
      }
      else
      {
        index = 1;
      }
    }
    else if (yellowAvailable && shortestIdx == 2)
    {
      if (yellowShortestLength == blueShortestLength)
      {
        int capacityComparison = compareTruckCapacity(&status.yellowTruckStatus, &status.blueTruckStatus);
        if (capacityComparison >= 0)
        {
          index = 2;
        }
        else
        {
          index = 0;
        }
      }
      else if (yellowShortestLength == greenShortestLength)
      {
        int capacityComparison = compareTruckCapacity(&status.yellowTruckStatus, &status.greenTruckStatus);
        if (capacityComparison >= 0)
        {
          index = 2;
        }
        else
        {
          index = 1;
        }
      }
      else
      {
        index = 2;
      }
    }

    // If there's a tie on the shortest path length, check the available capacity
    else if (blueAvailable && yellowAvailable && blueShortestLength == yellowShortestLength && blueShortestLength < greenShortestLength)
    {
      int capacityComparison = compareTruckCapacity(&status.blueTruckStatus, &status.yellowTruckStatus);
      if (capacityComparison > 0)
      {
        index = 0; // Blue truck has more capacity remaining
      }
      else if (capacityComparison < 0)
      {
        index = 2; // Yellow truck has more capacity remaining
      }
    }

    if (greenAvailable && yellowAvailable && greenShortestLength == yellowShortestLength && greenShortestLength < blueShortestLength)
    {
      int capacityComparison = compareTruckCapacity(&status.greenTruckStatus, &status.yellowTruckStatus);
      if (capacityComparison > 0)
      {
        index = 1; // Green truck has more capacity remaining
      }
      else if (capacityComparison < 0)
      {
        index = 2; // Yellow truck has more capacity remaining
      }
    }

    if (greenAvailable && blueAvailable && greenShortestLength == blueShortestLength && greenShortestLength < yellowShortestLength)
    {
      int capacityComparison = compareTruckCapacity(&status.greenTruckStatus, &status.blueTruckStatus);
      if (capacityComparison > 0)
      {
        index = 1; // Green truck has more capacity remaining
      }
      else if (capacityComparison < 0)
      {
        index = 0; // blue truck has more capacity remaining
      }
    }
  }

  struct ShortestRouteInfo shortestRouteInfo;
  if (index == 0)
  {
    shortestRouteInfo = blueShortestRouteInfo;
  }
  else if (index == 1)
  {
    shortestRouteInfo = greenShortestRouteInfo;
  }
  else if (index == 2)
  {
    shortestRouteInfo = yellowShortestRouteInfo;
  }

  printDeliveryRoute(index, shortestRouteInfo);
  return index;
}

struct ShortestRouteInfo truckShortestPath(struct Route truckRoute, const struct Map *map, const struct Point destination, const struct Building building)
{
  struct ShortestRouteInfo ShortestRouteInfo;
  struct Route shortestRoute;
  shortestRoute.numPoints = 10000;
  int pointIndex = 0;

  for (int i = 0; i < truckRoute.numPoints; i++)
  {
    struct Route route = shortestPath(map, truckRoute.points[i], destination, building);
    if (route.numPoints < shortestRoute.numPoints && route.numPoints != -1)
    {
      shortestRoute = route;
      pointIndex = i;
    }
  }

  ShortestRouteInfo.start = truckRoute.points[pointIndex];
  ShortestRouteInfo.end = destination;
  ShortestRouteInfo.shortestRoute = shortestRoute;
  return ShortestRouteInfo;
}

void updateTruckStatus(int truckIndex, const struct Package package, struct DeliveryStatus *status)
{
  switch (truckIndex)
  {
  case 0: // Blue truck
    status->blueTruckStatus.availableWeight -= package.weight;
    status->blueTruckStatus.availableVolume -= package.volume;
    break;
  case 1: // Green truck
    status->greenTruckStatus.availableWeight -= package.weight;
    status->greenTruckStatus.availableVolume -= package.volume;
    break;
  case 2: // Yellow truck
    status->yellowTruckStatus.availableWeight -= package.weight;
    status->yellowTruckStatus.availableVolume -= package.volume;
    break;
  default:
    break;
  }
}

int compareTruckCapacity(const struct TruckStatus *truck1, const struct TruckStatus *truck2)
{
  double truck1WeightUsage = (MAX_WEIGHT - truck1->availableWeight) / MAX_WEIGHT;
  double truck1VolumeUsage = (MAX_VOLUME - truck1->availableVolume) / MAX_VOLUME;

  double truck2WeightUsage = (MAX_WEIGHT - truck2->availableWeight) / MAX_WEIGHT;
  double truck2VolumeUsage = (MAX_VOLUME - truck2->availableVolume) / MAX_VOLUME;

  // Calculate the higher usage percentage for each truck
  double truck1MaxUsage = (truck1WeightUsage > truck1VolumeUsage) ? truck1WeightUsage : truck1VolumeUsage;
  double truck2MaxUsage = (truck2WeightUsage > truck2VolumeUsage) ? truck2WeightUsage : truck2VolumeUsage;

  // Compare which truck has less percentage used, thus more capacity remaining
  if (truck1MaxUsage < truck2MaxUsage)
  {
    return 1; // Truck 1 has more capacity remaining
  }
  else if (truck1MaxUsage > truck2MaxUsage)
  {
    return -1; // Truck 2 has more capacity remaining
  }
  else
  {
    return 0; // Both trucks have the same capacity remaining
  }
}

void printDeliveryRoute(int truckIndex, struct ShortestRouteInfo routeInfo)
{
  switch (truckIndex)
  {
  case 0:
    printf("Ship on BLUE LINE, ");
    break;
  case 1:
    printf("Ship on GREEN LINE, ");
    break;
  case 2:
    printf("Ship on YELLOW LINE, ");
    break;
  default:
    printf("No truck is available now.\n");
    return;
  }

  struct Route route = routeInfo.shortestRoute;
  if (route.numPoints > 0)
  {
    printf("divert:");
    printf(" %d%c", routeInfo.start.row + 1, indexToLetter(routeInfo.start.col));
    for (int i = 0; i < route.numPoints; i++)
    {
      printf(" %d%c", route.points[i].row + 1, indexToLetter(route.points[i].col));
    }
    printf(" %d%c", routeInfo.end.row + 1, indexToLetter(routeInfo.end.col));
    printf("\n");
  }
  else
  {
    printf("no diversion\n");
  }
}

int shorstestIndex(int *lenghtArray)
{
  int shortest = lenghtArray[0];
  int shortestIdx = 0;
  for (int i = 0; i < 3; i++)
  {
    if (lenghtArray[i] < shortest)
    {
      shortestIdx = i;
    }
  }

  return shortestIdx;
}

int tieOnTheShortest(int *lenghtArray)
{
  if (lenghtArray[0] == lenghtArray[1] || lenghtArray[1] == lenghtArray[2] || lenghtArray[0] == lenghtArray[2])
  {
    return 1;
  }
  else
  {
    return 0;
  }
}