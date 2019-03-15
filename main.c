#include <stdio.h>
#include <stdbool.h>

typedef struct line{
    // Right (x,y)
    double R_X;
    double R_Y;
    // Left (x,y)
    double L_X;
    double L_Y;
} Line;

int n;

double getWidth(Line line){
    return line.R_X - line.L_X;
}

double getCoveredPart(Line line, Line *lines){
    // returns the length of x values that are covered from above by another line
    double covered;
    for (int i = 0; i < n; i++){
        Line otherLine = lines[i];
        if (otherLine.R_X < line.R_X && otherLine.L_X > line.R_X){
            result = line.L_X - otherLine.L_X;
        } else if (line.R_X < otherLine.R_X && line.L_X > otherLine.R_X)){
            if
        }

    }
    return covered;
}

double getYofX(Line line, double x){
    // Calculating ax + b based on R(x,y)
    double a = (line.R_Y - line.L_Y) / (line.R_X - line.L_X);
    double b = line.R_Y - a * line.R_X;
    return a*x + b;
}

bool isLowerLine(Line low, Line high){
    // Find x value to test with. Takes highest right x. Works if x-values overlap, and lines never cross.
    int x = (low.R_X < high.R_X? high.R_X : low.R_X);
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

int main() {

    printf("Hello! Please input the following info:\nNumber of lines to check, followed by enter.\n"
           "For each line: four coordinates separated by spaces, followed by enter.\n->");

    // Get number of lines: n
    scanf("%d", &n);
    Line lines[n];
    // Make array of lines:
    for (int i = 0; i < n; i++){
        scanf("%lf %lf %lf %lf", &lines[i].R_X, &lines[i].R_Y, &lines[i].L_X, &lines[i].L_Y);
    }


    printf("TEST: Printing last element: Right coord: (%lf,%lf) Left coord: (%lf,%lf)\n",
            lines[n-1].R_X, lines[n-1].R_Y, lines[n-1].L_X, lines[n-1].L_Y);



    return 0;
}