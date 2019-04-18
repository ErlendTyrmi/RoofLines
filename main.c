#include <stdio.h>
#include <stdbool.h>

typedef struct line {
    // Left (x,y)
    int X1;
    int Y1;
    // Right (x,y)
    int X2;
    int Y2;
    int totalWater;
    int childLineID;
    bool isChild;
    bool isChecked;
} Line;

int n, highestX = 0, newRain = 0;

double getYofX(Line line, int x) {
    // Calculates y value for a given line and point.
    double a = (double) (line.Y2 - line.Y1) / (double) (line.X2 - line.X1);
    double b = (double) line.Y1 - a * (double) line.X1;
    return a * x + b;
}

bool firstIsLowest(Line low, Line high) {
    // Find x value to test with. Takes highest right x. Only works if x-values overlap!
    int x = (low.X1 <= high.X1 ? high.X1 : low.X1);
    return getYofX(low, x) < getYofX(high, x) ? true : false;
}

bool overlapsPoint(Line line, int x) {
    // returns whether a line overlaps a point, start point included.
    if (line.X1 <= x && line.X2 > x) {
        return true;
    } else {
        return false;
    }
}

bool overlapsPointIncludingX2(Line line, int x) {
    // returns whether a line overlaps a point, start and end point included.
    if (line.X1 <= x && line.X2 >= x) {
        return true;
    } else {
        return false;
    }
}

int getHighestLineAtXCoordinate(Line *lines, int x) {
    // Returns id of highest line at a certain point on the x-axis.
    int lineNumber = 0;
    for (int i = 1; i <= n; i++) {
        if (overlapsPoint(lines[i], x)) {
            if (firstIsLowest(lines[lineNumber], lines[i]) || lineNumber == 0) {
                lineNumber = i;
            }
        }
    }
    return lineNumber;
}

void updateRain(Line *lines) {
    // Updates the initial totalWater attribute in place (on the line struct).
    int rainPoint, lineNumber;
    for (int i = 0; i <= highestX; i++) {
        rainPoint = i;
        lineNumber = getHighestLineAtXCoordinate(lines, rainPoint);

        if (lineNumber != 0) {
            lines[lineNumber].totalWater += 1;
        }
    }
}

int getDripPoint(Line line) {
    // Returns x value of lowest y coordinate, as 'drip-point'.
    return (line.Y1 < line.Y2 ? line.X1 : line.X2);
}

void updateChildRoofs(Line *lines) {
    // Adds child roofs to all relevant lines.
    for (int i = 1; i < n + 1; i++) {
        int topLineID = 0;
        if (lines[i].totalWater != 0) {

            for (int j = 1; j < n + 1; j++) {
                if (overlapsPointIncludingX2(lines[j], getDripPoint(lines[i])) && firstIsLowest(lines[j], lines[i])) {
                    if (topLineID == 0) {
                        topLineID = j;
                    } else if (firstIsLowest(lines[topLineID], lines[j])) {
                        topLineID = j;
                    }
                }
            }
        }

        // Adding child roof to parent and marking child with 'isChild'.
        if (topLineID != 0) {
            lines[i].childLineID = topLineID;
            lines[topLineID].isChild = true;
        }
    }
}


void inheritRain(int lineID, Line *lines) {
    // Makes all descendants inherit rain from parent.
    newRain = lines[lineID].totalWater;

    while (lines[lineID].childLineID != 0) {
        lines[lines[lineID].childLineID].totalWater += newRain;

        if (!lines[lines[lineID].childLineID].isChecked) {
            lines[lines[lineID].childLineID].isChecked = true;
            newRain = lines[lines[lineID].childLineID].totalWater;
        }

        lineID = lines[lineID].childLineID;
    }
}


void getAccumulatedDrip(Line *lines) {
    // Selects roofs with no parent, and lets descendant roofs inherit.
    for (int i = 1; i < n + 1; i++) {
        if (!lines[i].isChild) {
            inheritRain(i, lines);
        }
    }
}

int main() {

    //printf("Hello! This program prints the total water flow from each roof, represented by a line.\n"
    //       "First: Please input the following info: Number of lines to check, followed by enter.\n"
    //       "For all subsequent lines: Four coordinates separated by spaces, followed by enter.\n->");

    // Get number of lines: n
    scanf("%d", &n);
    Line lines[n + 1];

    // Make array of lines:
    for (int i = 1; i < n + 1; i++) {
        scanf("%d %d %d %d", &lines[i].X1, &lines[i].Y1, &lines[i].X2, &lines[i].Y2);
        lines[i].totalWater = 0;
        lines[i].childLineID = 0;
        lines[i].isChild = false;
        lines[i].isChecked = false;

        // The one x value to rule them all..
        if (lines[i].X2 > highestX) {
            highestX = lines[i].X2;
        }
    }

    updateRain(lines);
    updateChildRoofs(lines);
    getAccumulatedDrip(lines);

    // Printing results
    for (int i = 1; i < n + 1; i++) {
        printf("%d \n", lines[i].totalWater);
    }

    return 0;
}