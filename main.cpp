#include <stdio.h>
#include "edge_tracking.cpp"
#include <ctime>

int main(){



    time_t begin,end; // time_t is a datatype to store time values.

    time (&begin); // note time before execution
    EdgeTracker* et = new EdgeTracker();
    printf("total count: %d\n",et->pointsInRegion(-1.0,0.5,-0.6,0.6,10000,2000,2000));
    time (&end); // note time after execution

    double difference = difftime (end,begin);
    printf ("time taken for function() %.2lf seconds.\n", difference );

}