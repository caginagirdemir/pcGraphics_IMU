#include <math.h>
#include <iostream>

using namespace std;
int x,y;

float Q_rsqrt( float number )
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F; //threehalfs variable equal to 1.5 float

    x2 = number * 0.5F;
    y  = number;
    i  = * ( long * ) &y;
    i  = 0x5f3759df - ( i >> 1 );
    y  = * ( float * ) &i;
    y  = y * ( threehalfs - ( x2 * y * y ) );

    return y;
}

int main()
{
    while(1)
    {
    cin >> x;
    cout << InvSqrt(x);

    }
    return 0;
}
