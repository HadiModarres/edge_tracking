#include <stdio.h>
#include "edge_tracking.cpp"

int main(){
    EdgeTracker* et = new EdgeTracker();
    printf("total count: %d\n",et->pointsInRegion(-1.0,0.5,-0.6,0.6,10000,1000,1000));
}