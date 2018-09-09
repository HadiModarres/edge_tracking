#include <stdio.h>
#include <string.h>
#include <math.h>


static const unsigned Width = 320, Height = 200, MaxIter = 768;
static const double cre = -1.36022, cim = 0.0653316, diam = 0.035;
static const double minr = cre - diam * .5, mini = cim - diam * .5;
static const double maxr = cre + diam * .5, maxi = cim + diam * .5;
static const double stepr = (maxr-minr)/ Width;
static const double stepi = (maxi-mini)/Height;

enum {
    Loaded = 1, Queued = 2
};
static int Data[Width * Height] = {0};
static unsigned char Done[Width * Height] = {0};
static const unsigned QueueSize = (Width + Height) * 4;
static unsigned Queue[QueueSize];
static unsigned QueueHead = 0, QueueTail = 0;


static int Iterate(double x, double y) {
    int iter;
    double r = x, i = y;
    for (iter = 0; iter < MaxIter; ++iter) {
        double r2 = r * r, i2 = i * i;
        if (r2 + i2 >= 4.0)
            break;
        double ri = r * i;
        i = ri + ri + y;
        r = r2 - i2 + x;
    }
    return iter;
}

static void AddQueue(unsigned p) {
    if (Done[p] & Queued) return;
    Done[p] |= Queued;
    Queue[QueueHead++] = p;
    if (QueueHead == QueueSize) QueueHead = 0;
}

static int Load(unsigned p) {
    if (Done[p] & Loaded) return Data[p];
    unsigned x = p % Width, y = p / Width;
    int result = Iterate(minr + x * stepr, mini + y * stepi);
    //PutPixel(x, y, result);
    Done[p] |= Loaded;
    return Data[p] = result;
}


static void Scan(unsigned p) {
    unsigned x = p % Width, y = p / Width;
    int center = Load(p);
    int ll = x >= 1, rr = x < Width - 1;
    int uu = y >= 1, dd = y < Height - 1;
/* ^These are booleans, but bc31 does
* not support the "bool" type */
/* If a neighbor color differs from
* the center, scan the neighbor in turn */
    int l = ll && Load(p - 1) != center;
    int r = rr && Load(p + 1) != center;
    int u = uu && Load(p - Width) != center;
    int d = dd && Load(p + Width) != center;
    if (l) AddQueue(p - 1);
    if (r) AddQueue(p + 1);
    if (u) AddQueue(p - Width);
    if (d) AddQueue(p + Width);
/* The corner pixels (nw,ne,sw,se) are also neighbors */
    if ((uu && ll) && (l || u)) AddQueue(p - Width - 1);
    if ((uu && rr) && (r || u)) AddQueue(p - Width + 1);
    if ((dd && ll) && (l || d)) AddQueue(p + Width - 1);
    if ((dd && rr) && (r || d)) AddQueue(p + Width + 1);
}
//
int pointsInRegion(double minr, double maxr,mini,maxi){

}


int main() {
    for (unsigned y = 0; y < Height; ++y) {
        AddQueue(y * Width + 0);
        AddQueue(y * Width + (Width - 1));
    }
    for (unsigned x = 1; x < Width - 1; ++x) {
        AddQueue(0 * Width + x);
        AddQueue((Height - 1) * Width + x);
    }
    unsigned flag = 0;
    while (QueueTail != QueueHead) {
        unsigned p;
        if (QueueHead <= QueueTail || ++flag & 3) {
            p = Queue[QueueTail++];
            if (QueueTail == QueueSize) QueueTail = 0;
        } else p = Queue[--QueueHead];
        Scan(p);
    }

    for (unsigned p = 0; p < Width * Height; ++p) {
        if (Done[p] & Loaded)
            if (!(Done[p + 1] & Loaded))
               // VRAM[p + 1] = VRAM[p],
                        Done[p + 1] |= Loaded;
    }
    printf("computed");
    for (int i=0;i<Width;i++){
        for (int j=0;j<Height;j++){
            printf("Data: %d\n",Data[Width*j+i]);
        }
    }
    getchar();
    return 0;


}

