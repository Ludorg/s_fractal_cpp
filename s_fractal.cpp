// Sofia (Sofia_aleph)
//
// Sofia, my way for developing knowledge
//
// (c) 2004 Ludovic LIEVRE aka Ludorg

// fractal generator : Mandelbrot
// 
// 0.0.1 2004/07/05 : file creation
// 0.0.2 2004/07/07 : move ImageData to another file
// 0.0.3 2004/07/08 : add xml confguration for MandelbrotParams
// 0.0.4 2004/07/10 : add Julia fractal generation

// Let z and c complex numbers
//
// Mandelbrot algorithm
//
// c depends on the coordinates of the pixel
// z0 = 0+i0
// zn+1=zn2+c 
// if ||zn|| > 2 color of c is f(n)
//
// Julia algorithm
//
// z depends on the coordinates of the pixel
// c is a constant
// if ||zn|| > 2 color of z is f(n)


#include <cstdio>

#include "s_fractal.h"

#include "s_image_data.h"

SOFIA_NS_BEGIN

ImageData* Mandelbrot( const MandelbrotParams& params )
{    
    ImageData* res = new ImageData( params.width_, params.height_ );

    double w = params.maxC_.real() - params.minC_.real();
    double h = params.maxC_.imag() - params.minC_.real();

    double stepW = w / params.width_;
    double stepH = h / params.height_;

    TComponent stepR = ( params.maxColor_.r_ - params.minColor_.r_ ) / params.maxIterations_;
    TComponent stepG = ( params.maxColor_.g_ - params.minColor_.g_ ) / params.maxIterations_;
    TComponent stepB = ( params.maxColor_.b_ - params.minColor_.b_ ) / params.maxIterations_;


    std::complex<double> c;
    double normValue;

    c = params.minC_;

    for( uint imgH = 0; imgH < params.height_; imgH++ )
    {
        for( uint imgW = 0; imgW < params.width_; imgW++ )
        {
            std::complex<double> zn = std::complex<double>( 0, 0 );

            for( uint n = 0; n < params.maxIterations_; n++ )
            {                
                // zn+1 = zn ^ m + c
                
                zn = pow( zn, params.m_ );
                
                zn += c; 

                normValue = norm( zn );

                if( ( normValue - 2.0 ) > 0 )
                {                    
                    res->set( imgW, imgH, 
                        TPixel( params.minColor_.r_ + n * stepR, 
                        params.minColor_.g_ + n * stepG, 
                        params.minColor_.b_ + n * stepB ) );

                    n = params.maxIterations_;
                }

                //printf( "n=%6d c=%3.5lf +i%3.5lf \t w=%3d h=%3d\t norm %lf\n", n, c.real(), c.imag(), imgW, imgH, norm( zn ) );
            }
            c.real( c.real() + stepW ); 
        }
        c.imag( c.imag() + stepH ); 
        c.real( params.minC_.real() );
    }

    return res;
}

ImageData* Julia( const JuliaParams& params )
{
    ImageData* res = new ImageData( params.width_, params.height_ );

    double w = params.maxZ_.real() - params.minZ_.real();
    double h = params.maxZ_.imag() - params.minZ_.real();

    double stepW = w / params.width_;
    double stepH = h / params.height_;

    TComponent stepR = ( params.maxColor_.r_ - params.minColor_.r_ ) / params.maxIterations_;
    TComponent stepG = ( params.maxColor_.g_ - params.minColor_.g_ ) / params.maxIterations_;
    TComponent stepB = ( params.maxColor_.b_ - params.minColor_.b_ ) / params.maxIterations_;

    std::complex<double> c = params.c_;
    
    std::complex<double> z0 = params.minZ_;  
    std::complex<double> zn = z0;

    double normValue;

    for( uint imgH = 0; imgH < params.height_; imgH++ )
    {
        for( uint imgW = 0; imgW < params.width_; imgW++ )
        {
           
            for( uint n = 0; n < params.maxIterations_; n++ )
            {                
                // zn+1 = zn * zn + c
                zn *= zn;
                zn += c; 

                normValue = norm( zn );

                if( ( normValue - 2.0 ) > 0 )
                {                    
                    res->set( imgW, imgH, 
                        TPixel( params.minColor_.r_ + n * stepR, 
                        params.minColor_.g_ + n * stepG, 
                        params.minColor_.b_ + n * stepB ) );

                    n = params.maxIterations_;
                }

                //printf( "n=%6d z=%3.5lf +i%3.5lf \t w=%3d h=%3d\t norm zn %lf\n", n, z.real(), z.imag(), imgW, imgH, norm( zn ) );
            }
            z0.real( z0.real() + stepW );
            zn = z0;
            //printf( "z0=%3.5lf +i%3.5lf\n", z0.real(), z0.imag() );
        }
        z0.imag( z0.imag() + stepH ); 
        z0.real( params.minZ_.real() );
        zn = z0;
    }

    return res;

}

SOFIA_NS_END
