#include <stdio.h>
#include <math.h>

int main() {
    int num_points = 100;
    double log_scale[num_points];

// generate log scale like this 
// bug correct ... +i/numpoints*...
// 0.1 and 100 are the endpoints of the ranges
    // Generate a logarithmic scale from 0.1 to 100
    for (int i = 0; i < num_points; i++) {
        log_scale[i] = pow(10.0, log10(0.1) + i * (log10(100) - log10(0.1)) / (num_points - 1));
    }

    // Print the generated logarithmic scale
    for (int i = 0; i < num_points; i++) {
        printf("%f\n", log_scale[i]);
    }

    return 0;
}
