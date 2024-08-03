#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

// Define a Point structure
typedef struct Point {
    int x, y;
} Point;

// A utility function to find the distance between two points
float dist(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                (p1.y - p2.y) * (p1.y - p2.y));
}

// A utility function to find the minimum of two float values
float min(float x, float y) {
    return (x < y) ? x : y;
}

// A utility function to compare two points by their x-coordinates
int compareX(const void* a, const void* b) {
    Point* p1 = (Point*)a;
    Point* p2 = (Point*)b;
    return (p1->x - p2->x);
}

// A utility function to compare two points by their y-coordinates
int compareY(const void* a, const void* b) {
    Point* p1 = (Point*)a;
    Point* p2 = (Point*)b;
    return (p1->y - p2->y);
}

// A function to find the distance between the closest points of a strip of a given size.
// All points in the strip are sorted according to their y-coordinates.
float stripClosest(Point strip[], int size, float d) {
    float minDist = d; // Initialize the minimum distance as d

    qsort(strip, size, sizeof(Point), compareY); // Sort the strip according to the y-coordinate

    // Pick all points one by one and try the next points till the difference
    // between y-coordinates is smaller than d.
    // This loop runs at most 6 times
    for (int i = 0; i < size; ++i)
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < minDist; ++j)
            if (dist(strip[i], strip[j]) < minDist)
                minDist = dist(strip[i], strip[j]);

    return minDist;
}

// A recursive function to find the smallest distance.
float closestUtil(Point Px[], Point Py[], int n) {
    // If there are 2 or 3 points, then use a brute-force approach
    if (n <= 3) {
        float minDist = FLT_MAX;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (dist(Px[i], Px[j]) < minDist)
                    minDist = dist(Px[i], Px[j]);
        return minDist;
    }

    // Find the middle point
    int mid = n / 2;
    Point midPoint = Px[mid];

    // Divide points in y sorted array around the vertical line.
    Point Pyl[mid]; // y sorted points on the left of the vertical line
    Point Pyr[n - mid]; // y sorted points on the right of the vertical line
    int li = 0, ri = 0; // indexes of left and right subarrays
    for (int i = 0; i < n; i++) {
        if (Py[i].x <= midPoint.x)
            Pyl[li++] = Py[i];
        else
            Pyr[ri++] = Py[i];
    }

    // Consider the vertical line passing through the middle point
    // Calculate the smallest distance dl in the left half and dr in the right half
    float dl = closestUtil(Px, Pyl, mid);
    float dr = closestUtil(Px + mid, Pyr, n - mid);

    // Find the smaller of two distances
    float d = min(dl, dr);

    // Build an array strip[] that contains points close (closer than d) to the line
    // passing through the middle point
    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++)
        if (abs(Py[i].x - midPoint.x) < d)
            strip[j] = Py[i], j++;

    // Find the closest points in strip.
    // Return the minimum of d and the closest distance in strip[]
    return min(d, stripClosest(strip, j, d));
}

// The main function that finds the smallest distance
float closest(Point P[], int n) {
    Point Px[n];
    Point Py[n];
    for (int i = 0; i < n; i++) {
        Px[i] = P[i];
        Py[i] = P[i];
    }

    qsort(Px, n, sizeof(Point), compareX);
    qsort(Py, n, sizeof(Point), compareY);

    return closestUtil(Px, Py, n);
}

int main() {
    Point P[] = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    int n = sizeof(P) / sizeof(P[0]);
    printf("The smallest distance is %f\n", closest(P, n));
    return 0;
}
