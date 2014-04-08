
#include <iostream>
#include <math.h>

int main(int argc, const char * argv[])
{
    int h, v, result;

    scanf ("%i %i", &h, &v);
    
    result = (h / sin(v * M_PI/180)) + 1;
    
    printf("%i\n", result);
    
    return 0;
}

