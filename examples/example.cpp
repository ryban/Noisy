#include "png.h"

#include <iostream>
// use the C library becuase I am to lazy to port the PNG writing function I am using
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cmath>
#include <memory>

#include "noisy/Noisy.h"

struct Pixel
{
    uint8_t r, g, b;
};

class Bitmap
{
private:
    int m_width;
    int m_height;
    Pixel *m_pixels;
public:
    Bitmap(int w, int h)
    {
        m_width = w;
        m_height = h;
        m_pixels = new Pixel[w*h];
    }
    ~Bitmap()
    {
        delete [] m_pixels;
    }

    Pixel *getPixel(int x, int y)
    {
        if(x >= 0 && x < m_width && y >= 0 && y < m_height)
            return &m_pixels[(x*m_width)+y];
        return NULL;
    }

    void setPixel(int x, int y, Pixel p)
    {
        if(x >= 0 && x < m_width && y >= 0 && y < m_height)
            m_pixels[(x*m_width)+y] = p;
    }

    int saveToFile(const char *path)
    {
        FILE * fp;
        png_structp png_ptr = NULL;
        png_infop info_ptr = NULL;
        size_t x, y;
        png_byte ** row_pointers = NULL;
        /* "status" contains the return value of this function. At first
           it is set to a value which means 'failure'. When the routine
           has finished its work, it is set to a value which means
           'success'. */
        int status = -1;
        /* The following number is set by trial and error only. I cannot
           see where it it is documented in the libpng manual.
        */
        int pixel_size = 3;
        int depth = 8;
        
        fp = fopen (path, "wb");
        if (! fp) {
            goto fopen_failed;
        }

        png_ptr = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if (png_ptr == NULL) {
            goto png_create_write_struct_failed;
        }
        
        info_ptr = png_create_info_struct (png_ptr);
        if (info_ptr == NULL) {
            goto png_create_info_struct_failed;
        }
        
        /* Set up error handling. */

        if (setjmp (png_jmpbuf (png_ptr))) {
            goto png_failure;
        }
        
        /* Set image attributes. */

        png_set_IHDR (png_ptr,
                      info_ptr,
                      m_width,
                      m_height,
                      depth,
                      PNG_COLOR_TYPE_RGB,
                      PNG_INTERLACE_NONE,
                      PNG_COMPRESSION_TYPE_DEFAULT,
                      PNG_FILTER_TYPE_DEFAULT);
        
        /* Initialize rows of PNG. */

        row_pointers = (png_byte**)png_malloc (png_ptr, m_height * sizeof (png_byte *));
        for (y = 0; y < m_height; ++y) {
            png_byte *row = (png_byte*)png_malloc (png_ptr, sizeof (uint8_t) * m_width * pixel_size);
            row_pointers[y] = row;
            for (x = 0; x < m_width; ++x) {
                Pixel *pixel = getPixel(x, y);
                *row++ = pixel->r;
                *row++ = pixel->g;
                *row++ = pixel->b;
            }
        }
        
        /* Write the image data to "fp". */

        png_init_io (png_ptr, fp);
        png_set_rows (png_ptr, info_ptr, row_pointers);
        png_write_png (png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

        /* The routine has successfully written the file, so we set
           "status" to a value which indicates success. */

        status = 0;
        
        for (y = 0; y < m_height; y++) {
            png_free (png_ptr, row_pointers[y]);
        }
        png_free (png_ptr, row_pointers);
        
         png_failure:
         png_create_info_struct_failed:
            png_destroy_write_struct (&png_ptr, &info_ptr);
         png_create_write_struct_failed:
            fclose (fp);
         fopen_failed:
        return status;
    }
};

int main()
{
    const int imgSize = 512;
    Bitmap bmp(imgSize, imgSize);

    noisy::pRidgedMulti ridge(new noisy::RidgedMulti(time(0), 24, 0.009, 1.9, 1.0, 0.75, 1.7));
    for(int x = 0; x < imgSize; x++)
    {
        for(int y = 0; y < imgSize; y++)
        {
            Pixel p;
            float n = ridge->getValue(float(x), float(y));
            // these are approximate bounds that makes for a good output
            n = noisy::utils::bound(n, 0.0, 1.0, -0.25, 2.25);
            n = noisy::utils::clamp(n, 0.0, 1.0);
            int grey = floor(255 * n);
            p.r = grey;
            p.g = grey;
            p.b = grey;
            bmp.setPixel(x, y, p);
        }
    }
    bmp.saveToFile("ridge.png");
    std::cout << "Ridged saved\n";

    noisy::pFBM fbm(new noisy::FBM(time(0), 16, 0.01, 0.5, 2.5));
    for(int x = 0; x < imgSize; x++)
    {
        for(int y = 0; y < imgSize; y++)
        {
            Pixel p;
            float n = fbm->getValue(float(x), float(y));
            n = noisy::utils::bound(n, 0.0, 1.0);
            int grey = floor(255 * n);
            p.r = grey;
            p.g = grey;
            p.b = grey;
            bmp.setPixel(x, y, p);
        }
    }
    bmp.saveToFile("fbm.png");
    std::cout << "FBM saved\n";

    noisy::pSimplex simplex(new noisy::Simplex(time(0)));
    for(int x = 0; x < imgSize; x++)
    {
        for(int y = 0; y < imgSize; y++)
        {
            Pixel p;
            float n = simplex->getValue(float(x)*0.02, float(y)*0.02);
            n = noisy::utils::bound(n, 0.0, 1.0, -1.0, 1.0);
            int grey = floor(255 * n);
            p.r = grey;
            p.g = grey;
            p.b = grey;
            bmp.setPixel(x, y, p);
        }
    }
    bmp.saveToFile("simplex.png");
    std::cout << "Simplex saved\n";

    noisy::pBillow billow(new noisy::Billow(time(0), 16, 0.007, 0.5, 2.5));
    for(int x = 0; x < imgSize; x++)
    {
        for(int y = 0; y < imgSize; y++)
        {
            Pixel p;
            float n = billow->getValue(float(x), float(y));
            n = noisy::utils::bound(n, 0.0, 1.0);
            int grey = floor(255 * n);
            p.r = grey;
            p.g = grey;
            p.b = grey;
            bmp.setPixel(x, y, p);
        }
    }
    bmp.saveToFile("billow.png");
    std::cout << "Billow saved\n";

    noisy::pVoronoi voronoi(new noisy::Voronoi(time(0), 0.05, 1.0));
    for(int x = 0; x < imgSize; x++)
    {
        for(int y = 0; y < imgSize; y++)
        {
            Pixel p;
            float n = voronoi->getValue(float(x), float(y));
            n = noisy::utils::bound(n, 0.0, 1.0);
            //n = noisy::utils::clamp(n, 0.0, 1.0);
            int grey = floor(255 * n);
            p.r = grey;
            p.g = grey;
            p.b = grey;
            bmp.setPixel(x, y, p);
        }
    }
    bmp.saveToFile("voronoi.png");
    std::cout << "Voronoi saved\n";
}
