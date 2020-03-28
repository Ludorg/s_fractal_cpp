#if !defined( S_FRACTAL_H )
#define S_FRACTAL_H 1

// Sofia (Sofia_aleph)
//
// Sofia, my way for developing knowledge
//
// (c) 2004 Ludovic LIEVRE aka Ludorg

// fractal generator : Mandelbrot + Julia
// 
// 0.0.1 2004/07/05 : file creation
// 0.0.2 2004/07/07 : move ImageData to another file
// 0.0.3 2004/07/10 : add Julia fractal generation

//! \file s_fractal.h
//! \brief This file contains declarations for the Mandelbrot and Julia algorithms.
//! \author Ludovic LIEVRE aka Ludorg
//! \version 0.0.3
//! \date 10 July 2004

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

#include "sofia.h"

#include "s_image_data.h"

#include <complex>
#include <string>

SOFIA_NS_BEGIN

//! \struct MandelbrotParams
//! \brief Parameters for Mandelbrot algotithm
struct MandelbrotParams
{
    MandelbrotParams() : width_( 100 ), 
        height_( 100 ),
        maxIterations_( 50 ),
        minC_( -1.0, -1.0 ),
        maxC_( 1.0, 1.0 ),
        m_( 2.0, 0.0 ),
        minColor_( 0x00, 0x00, 0x00 ),
        maxColor_( 0xFF, 0x00, 0xFF ),
        outputFile_( "mandelbrot.tga" )
    {
    }    
    
    //! \brief Width in pixels, of the image to be generated
    uint                    width_;
    //! \brief Height in pixels, of the image to be generated
    uint                    height_;

    //! \brief Maximum number of iterations for the Mandelbrot algorithm
    uint                    maxIterations_;

    //! \brief Minimum complex number corresponding to the (0,0) point
    std::complex<double>    minC_; 
    //! \brief Maximum complex number corresponding to the (width_,height_) point
    std::complex<double>    maxC_;
    
    //! \brief Complex number for the power calculation
    std::complex<double>    m_;

    //! \brief Minimum color for the painting of the pixel
    TPixel                  minColor_;
    //! \brief Maximum color for the painting of the pixel
    TPixel                  maxColor_;
    
    //! \brief Output file for writing the Image
    std::string             outputFile_;

};

//! \brief Mandelbrot algotithm.
//! Let C a complex number.
//! C depends on the coordinates of the pixel.
//! Let Z(n) a complex number.
//! Z(n+1) = (Zn) * Z(n) + C 
//! if norm(Z(n)) > 2 then the color of C is f(n)
ImageData* Mandelbrot( const MandelbrotParams& params );

//! \struct JuliaParams
//! \brief Parameters for Mandelbrot algotithm
struct JuliaParams
{
    JuliaParams() : width_( 100 ), 
        height_( 100 ),
        maxIterations_( 50 ),
        minZ_( -1.5, -1.5 ),
        maxZ_( 1.5, 1.5 ),
        c_( 0.5, 0.5 ),
        minColor_( 0x00, 0x00, 0x00 ),
        maxColor_( 0xFF, 0x00, 0xFF ),
        outputFile_( "julia.tga" )
    {
    }    
    
    //! \brief Width in pixels, of the image to be generated
    uint                    width_;
    //! \brief Height in pixels, of the image to be generated
    uint                    height_;

    //! \brief Maximum number of iterations for the Julia algorithm
    uint                    maxIterations_;

    //! \brief Minimum complex number corresponding to the (0,0) point
    std::complex<double>    minZ_; 
    //! \brief Maximum complex number corresponding to the (width_,height_) point
    std::complex<double>    maxZ_;

    //! \brief Constant c of formula Zn+1 = Zn*Zn + c 
    std::complex<double>    c_;

    //! \brief Minimum color for the painting of the pixel
    TPixel                  minColor_;
    //! \brief Maximum color for the painting of the pixel
    TPixel                  maxColor_;
    
    //! \brief Output file for writing the Image
    std::string             outputFile_;

};    

//! \brief Julia algotithm.
ImageData* Julia( const JuliaParams& params );

SOFIA_NS_END

#endif // S_FRACTAL_H
