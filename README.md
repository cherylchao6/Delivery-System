# Local Delivery Routing System
Design a shortest pathway algorithm for package delivery

## Project Description

I have been engaged to create a routing system for a local delivery company that operates within a city depicted as a 25x25 grid. Our headquarters are located at square 1A, which is also the starting point for our three delivery vans. These vans follow a common path initially and then branch out to cover different areas of the city. The routes are color-coded on the map: blue, yellow, and green for the different trucks. Buildings are marked as black rectangles and must be navigated around, while white spaces are free for travel.

<img width="831" alt="截圖 2024-04-12 上午11 02 08" src="https://github.com/cherylchao6/Delivery-System/assets/77141019/de328849-9c04-41fe-aba6-aa0a3fcc991e">


### Features

- **Truck Capacity:** Each truck can carry up to 1200 kilograms and 50 cubic meters in various box sizes (0.5, 1, and 5 cubic meters), all square in dimension.
- **Dynamic Routing:** When a shipment comes in, I determine which truck has sufficient capacity and is closest to the destination to minimize route diversion.
- **Path Calculation:** Using the A* algorithm, the trucks can alter their paths minimally to deliver packages, navigating around the black building obstacles and through white spaces.

### The Shortest Path Algorithm

The A* algorithm, which utilizes Euclidean distance as a heuristic, is employed to navigate efficiently around obstacles and find the shortest path to the delivery points.

### Challenge Handling

Deciding the nearest truck for a delivery involves calculating distances from potential delivery points on their routes. For example, delivery at 7F, accessible by both the green and blue routes, will depend on which truck has more space. For remote points like 8P, precise calculations are necessary to determine the closest approach while avoiding obstacles.


### Operational Workflow

1. **Routing:** Each truck follows its predefined route, calculating the shortest Euclidean distance to the destination at every square.
2. **Decision Making:** If a truck's path to the destination is obstructed, an alternative truck is considered.
3. **Load Management:** The truck closest to the destination with enough space will be prioritized. If it's at capacity, the next closest truck is considered.
4. **Fallback:** Packages that cannot be delivered immediately are stored and scheduled for shipment the following day with the notice "Ships tomorrow".

## Daily Operations

This algorithm operates daily, accepting items until the trucks reach capacity or no more items arrive. My role includes determining the appropriate truck for each package, managing the delivery routes, and handling any necessary route adjustments.

## Example Output
<img width="824" alt="截圖 2024-04-12 上午11 06 41" src="https://github.com/cherylchao6/Delivery-System/assets/77141019/175cd17e-0718-48fc-ab3d-eb6d3988df36">


