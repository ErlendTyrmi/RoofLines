#include <stdio.h>
#include <stdbool.h>

typedef struct line{
    // Left (x,y)
    double X1;
    double Y1;
    // Right (x,y)
    double X2;
    double Y2;
    int drip;
    int checked;
} Line;

int n;

double getWidth(Line line){
    return line.X2- line.X1;
}

double getCoveredPart(Line line, Line *lines){
    // returns the length of x values that are covered from above by another line
    double covered;
    Line exposedLine = line;
    for (int i = 0; i < n; i++){
        Line otherLine = lines[i];
        if (otherLine.X1 < line.X1 && otherLine.X2 > line.X1){
            // return as soon as the whoe line is covered
            // Add covered x range of not in range
        } else if (line.X1 < otherLine.X1 && line.X2 > otherLine.X1){

        }

    }
    if (covered > 0){
        return covered;
    } else {
        return 0;
    }
}

double getYofX(Line line, double x){
    // Calculating ax + b based on Left coordinate(X1, Y1)
    double a = (line.Y2 - line.Y1) / (line.X2 - line.X1);
    double b = line.Y1 - a * line.X1;
    return a*x + b;
}

bool isLowerLine(Line low, Line high){
    // Find x value to test with. Takes highest right x. Works if x-values overlap, and lines never cross.
    int x = (low.X1 < high.X1? high.X1 : low.X1);
    return getYofX(low, x) < getYofX(high, x)? true : false;
}

double getRainSurface(Line line, Line lines[n]){
    return getWidth(line) - getCoveredPart(line, lines);
}

double getDrip(Line line, Line lines[]){
    return 0;
}

double getAccumulatedRain(Line line, Line lines[n]){
    return getRainSurface(line, lines) + getDrip(line, lines);
}

Line findHighestUncheckedLine(Line *lines){
    Line highest = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i<n;i++){
        if (lines[i].checked = 0)
        if (isLowerLine(highest, lines[i])){
            highest = lines[i];
        }
    }
    return highest;
}

int main() {

    printf("Hello! This program prints the total water flow from each roof, represented by a line. "
           "First: Please input the following info:\nNumber of lines to check, followed by enter.\n"
           "For all subsequent lines: Four coordinates separated by spaces, followed by enter.\n->");

    // Get number of lines: n
    scanf("%d", &n);
    Line lines[n];

    // Make array of lines:
    for (int i = 0; i < n; i++){
        scanf("%lf %lf %lf %lf %d %d", &lines[i].X1, &lines[i].Y1, &lines[i].X2, &lines[i].Y2, 0, 0);
    }


    printf("TEST: Printing last element: Left coord: (%lf,%lf) Right coord: (%lf,%lf)\n",
            lines[n-1].X1, lines[n-1].Y1, lines[n-1].X2, lines[n-1].Y2);



    return 0;
}