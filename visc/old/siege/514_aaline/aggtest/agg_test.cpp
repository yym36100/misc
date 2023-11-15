#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "agg.h"


enum
{
    width  = 1400,
    height = 1300
};


double random(double min, double max)
{
    int r = (rand() << 15) | rand();
    return ((r & 0xFFFFFFF) / double(0xFFFFFFF + 1)) * (max - min) + min;
}

void draw_line(agg::rasterizer& ras,
               double x1, double y1, 
               double x2, double y2,
               double width)
{

    double dx = x2 - x1;
    double dy = y2 - y1;
    double d = sqrt(dx*dx + dy*dy);
    
    dx = width * (y2 - y1) / d;
    dy = width * (x2 - x1) / d;

    ras.move_to_d(x1 - dx,  y1 + dy);
    ras.line_to_d(x2 - dx,  y2 + dy);
    ras.line_to_d(x2 + dx,  y2 - dy);
    ras.line_to_d(x1 + dx,  y1 - dy);
}


int main()
{
    // Allocate the framebuffer
    unsigned char* buf = new unsigned char[width * height * 3];

    // Create the rendering buffer 
    agg::rendering_buffer rbuf(buf, width, height, width * 3);

    // Create the renderer and the rasterizer
    agg::renderer<agg::span_rgb24> ren(rbuf);
    agg::rasterizer ras;

    // Setup the rasterizer
    ras.gamma(1.3);
    ras.filling_rule(agg::fill_even_odd);

    ren.clear(agg::rgba8(255, 255, 255));

    int i;

    // Draw random straight lines
    for(i = 0; i < 20; i++)
    {
        draw_line(ras, 
                  random(-30, rbuf.width()  + 30), 
                  random(-30, rbuf.height() + 30),
                  random(-30, rbuf.width()  + 30), 
                  random(-30, rbuf.height() + 30),
                  0.5);

        ras.render(ren, agg::rgba8(0,0,0));
    }

    // Write a .ppm file
    FILE* fd = fopen("agg_test.ppm", "wb");
    fprintf(fd, "P6\n%d %d\n255\n", rbuf.width(), rbuf.height());
    fwrite(buf, 1, rbuf.width() * rbuf.height() * 3, fd);
    fclose(fd);

    delete [] buf;
    return 0;
}

