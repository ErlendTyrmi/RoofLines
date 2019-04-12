#include <stdio.h>
#include <stdbool.h>

typedef struct line {
    // Left (x,y)
    double X1;
    double Y1;
    // Right (x,y)
    double X2;
    double Y2;
    // Accumulated rain dripping from this roof.
    int totalDrip;
    int parents[25];
    bool checked;
} Line;

int n, highestX = 0;
Line lines[];

double getWidth(Line line) {
    return line.X2 - line.X1;
}

double getYofX(Line line, double x) {
    // Calculating ax + b based on Left coordinate(X1, Y1)
    double a = (line.Y2 - line.Y1) / (line.X2 - line.X1);
    double b = line.Y1 - a * line.X1;
    return a * x + b;
}

bool firstIsLowest(Line low, Line high) {
    // Find x value to test with. Takes highest right x. Works if x-values overlap!
    int x = (low.X1 < high.X1 ? high.X1 : low.X1);
    return getYofX(low, x) < getYofX(high, x) ? true : false;
}

bool overlapsLine(Line a, Line b) {
    int x = (a.X1 < b.X1 ? b.X1 : a.X1);
}

bool overlapsPoint(Line line, int x) {
    if (line.X1 < x && line.X2 > x) {
        return true;
    } else {
        return false;
    }
}

int getHighestLineAtXCoordinate(Line *liLine nes, int x) {
    // Method to return id of highest line at a certain point on the x-axis.
    int lineNumber = 0;
    for (int i = 1; i <= n; i++) {
        if (overlapsPoint(lines[i], x)) {
            if (firstIsLowest(lines[lineNumber], lines[i])) {
                lineNumber = i;
            }
        }
    }
    return lineNumber;
}

void updateRain(Line *lines) {
    // This method updates the totalDrip attribute in place (on the actual line struct).
    double rainPoint;
    Line highestLine;
    for (int i = 0; i < highestX; i++) {
        rainPoint = i + 0.5;
        int lineNumber = getHighestLineAtXCoordinate(lines, rainPoint);

        if (lineNumber != 0) {
            lines[lineNumber].totalDrip += 1;
        }
    }
}

int getDripPoint(Line line) {
    return (line.Y1 < line.Y2 ? line.X1 : line.X1);
}

void updateParents(Line *lines) {
    for (int i = 1; i < n + 1; i++) {
        int topLineID = 0;
        if (lines[i].totalDrip != 0) {

            for (int j = 1; j < n + 1; j++) {
                if (overlapsLine(lines[i], lines[j]) && firstIsLowest(lines[j], lines[i])) {
                    if (topLineID == 0) {
                        topLineID = j;
                    } else if (firstIsLowest(lines[topLineID], lines[j])) {
                        topLineID = j;
                    }

                }
            }
        }
        // Adding parent (i) to first empty slot in the array of the line with an ID of topLineID
        if (topLineID != 0){
            for (int k = 0; k < 25; k++) {
                if (lines[topLineID].parents[k] == 0) {
                    lines[topLineID].parents[k] = i;
                    break;
                }
            }
        }
    }
}

int inheritRain(int lineID, Line *lines){
    for (int i = 0; i < 25; i++){
        if (lines[lineID].parents[i] != 0){
            lines[lineID].totalDrip += inheritRain(i, lines);
            lines[lineID].checked = true;
        }
    }
}

void getAccumulatedDrip(Line *lines){
    for (int i = 1; i < n+1; i++){
        if (!lines[i].checked){
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
    lines[n + 1];

    // Make array of lines:
    for (int i = 1; i < n+1; i++) {
        scanf("%lf %lf %lf %lf", &lines[i].X1, &lines[i].Y1, &lines[i].X2, &lines[i].Y2);

        // The one x value to rule them all..
        if (lines[i].X2 > highestX) {
            highestX = lines[i].X2;
        }


    }
    updateRain(lines);
    updateParents(lines);
    getAccumulatedDrip(lines);

    // Printing results
    for (int i = 1; i < n+1; i++){
        printf("%d", lines[i].totalDrip);
    }

    return 0;
}