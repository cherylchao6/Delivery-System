#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mapping.h"
#include "scheduler.h"

int main(void)
{
	struct Map baseMap = populateMap();

	struct Route blueRoute = getBlueRoute();
	struct Route greenRoute = getGreenRoute();
	struct Route yellowRoute = getYellowRoute();

	printf("=================\n");
	printf("Seneca College Deliveries\n");
	printf("=================\n");

	int end = 0;
	struct Package package;

	struct Route routes[3] = {blueRoute, greenRoute, yellowRoute};
	struct DeliveryStatus deliveryStat = initializeDeliveryStatus();

	while (!end)
	{
		end = getUserInput(&package, &baseMap);
		if (!end)
		{
			int truckIndex = decideTruckForDelivery(package, deliveryStat, &baseMap, routes);
			if (truckIndex != -1)
			{
				updateTruckStatus(truckIndex, package, &deliveryStat);
			}
			else
			{
				break;
			}
		}
	}
	printf("Thanks for shipping with Seneca!\n");

	return 0;
}