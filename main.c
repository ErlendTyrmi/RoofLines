#include <stdio.h>
#include <stdbool.h>

typedef struct line {
    // Left (x,y)
    int X1;
    int Y1;
    // Right (x,y)
    int X2;
    int Y2;
    int totalDrip;
    int childRoof;
    bool isChild;
    bool checked;
} Line;

int n, highestX = 0;

double getYofX(Line line, int x) {
    // Calculating ax + b based on Left coordinate(X1, Y1)
    double a = (double)(line.Y2 - line.Y1) / (double)(line.X2 - line.X1);
    double b = (double)line.Y1 - a * (double)line.X1;
    return a * x + b;
}

bool firstIsLowest(Line low, Line high) {
    // Find x value to test with. Takes highest right x. Works if x-values overlap!
    int x = (low.X1 <= high.X1 ? high.X1 : low.X1);
    return getYofX(low, x) < getYofX(high, x) ? true : false;
}

bool overlapsPoint(Line line, int x) {
    if (line.X1 <= x && line.X2 > x) {
        return true;
    } else {
        return false;
    }
}

bool overlapsPointIncludingX2(Line line, int x) {
    if (line.X1 <= x && line.X2 >= x) {
        return true;
    } else {
        return false;
    }
}

int getHighestLineAtXCoordinate(Line *lines, int x) {
    // Method to return id of highest line at a certain point on the x-axis.
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
    // This method updates the totalDrip attribute in place (on the line struct).
    double rainPoint;
    int lineNumber;
    for (int i = 0; i <= highestX; i++) {
        rainPoint = i;
        lineNumber = getHighestLineAtXCoordinate(lines, rainPoint);

        if (lineNumber != 0) {
            lines[lineNumber].totalDrip += 1;
        }
    }
}

int getDripPoint(Line line) {
    return (line.Y1 < line.Y2 ? line.X1 : line.X2);
}

void updateChildRoofs(Line *lines) {
    for (int i = 1; i < n + 1; i++) {
        int topLineID = 0;
        if (lines[i].totalDrip != 0) {

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
        if (topLineID != 0){
                lines[i].childRoof = topLineID;
                lines[topLineID].isChild = true;
        }
    }
}

void inheritRain(int lineID, Line *lines){
    // Lines pass on flow to child roof
        lines[lines[lineID].childRoof].totalDrip += lines[lineID].totalDrip;
}


void getAccumulatedDrip(Line *lines) {
    for (int i = 1; i < n+1; i++){
        if (!lines[i].isChild && !lines[i].checked){
            inheritRain(i, lines);
        }
    }
}

int main() {

    printf("Hello! This program prints the total water flow from each roof, represented by a line. "
           "First: Please input the following info: Number of lines to check, followed by enter.\n"
           "For all subsequent lines: Four coordinates separated by spaces, followed by enter.\n->");

    // Get number of lines: n
    scanf("%d", &n);
    Line lines[n + 1];

    // Make array of lines:
    for (int i = 1; i < n+1; i++) {
        scanf("%d %d %d %d", &lines[i].X1, &lines[i].Y1, &lines[i].X2, &lines[i].Y2);
        lines[i].totalDrip = 0;
        lines[i].childRoof = 0;
        lines[i].isChild = false;
        lines[i].checked = false;

        // The one x value to rule them all..
        if (lines[i].X2 > highestX) {
            highestX = lines[i].X2;
        }
    }

    updateRain(lines);
    updateChildRoofs(lines);
    getAccumulatedDrip(lines);

    // Printing results
    for (int i = 1; i < n+1; i++){
        printf("%d \n", lines[i].totalDrip);
    }

    return 0;
}