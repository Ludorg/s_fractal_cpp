// Sofia (Sofia_aleph)
//
// Sofia, my way for developing knowledge
//
// (c) 2004 Ludovic LIEVRE aka Ludorg

// fractal generator : ImageData
// 
// 0.0.1 2004/07/07 : file creation
//

#include <stdexcept>
#include <cstdio>

#include "s_image_data.h"

SOFIA_NS_BEGIN

ImageData::ImageData( size_t width, size_t height ) : 
width_( width ), 
height_( height )
{
    data_.resize( width_ );
    for( size_t i = 0; i < width_; i++ )
        data_[ i ].resize( height_ );
}

void ImageData::set( const uint x, const uint y, const TPixel pixel )
{
    if( x < width_ && y < height_ )
        data_[ x ][ y ] = pixel;
    else
        throw std::out_of_range( "ImageData::set|invalid access" );    
}

TPixel ImageData::get( const uint x, const uint y ) const
{
    if( x < width_ && y < height_ )
        return data_[ x ][ y ];
    else
        throw std::out_of_range( "ImageData::get|invalid access" );    

}

void ImageData::writeTGA( const char* fileName )
{    
    FILE* tgaFile;

    tgaFile = fopen( fileName, "wb" );

    byte tgaHeader[ 18 ];    

    // TGA field 1 ID Length
    tgaHeader[ 0 ] = 0;

    // TGA field 2 Color Map Type
    tgaHeader[ 1 ] = 0;    

    // TGA field 3 Image Type
    tgaHeader[ 2 ] = 2;    

    // TGA field 4 Color Map Specification (5 bytes)
    tgaHeader[ 3 ] = 0;
    tgaHeader[ 4 ] = 0;
    tgaHeader[ 5 ] = 0;
    tgaHeader[ 6 ] = 0;
    tgaHeader[ 7 ] = 0;

    // TGA field 5.1 X-origin of Image
    tgaHeader[ 8 ] = 0;
    tgaHeader[ 9 ] = 0;
    // TGA field 5.2 Y-origin of Image
    tgaHeader[ 10 ] = 0;
    tgaHeader[ 11 ] = 0;
    // TGA field 5.3 Image Width
    memcpy( &tgaHeader[ 12 ], &width_,  2 );
    // TGA field 5.4 Image Height
    memcpy( &tgaHeader[ 14 ], &height_,  2 );
    // TGA field 5.5 Pixel Depth
    tgaHeader[ 16 ] = 24;
    // TGA field 5.6 Image Descriptor
    tgaHeader[ 17 ] = 8;

    fwrite( tgaHeader, 18, 1, tgaFile );
        
    // TGA data

    TComponent* tgaData = new TComponent[ width_ * height_ * 3 ];

    size_t i = 0;
    size_t j = 0;

    size_t p = 0;
    
    size_t dataSize = width_ * height_ * 3; 

    TPixel pixel;

    while( p != dataSize )
    {        
        pixel = data_[ j ][ i ];
        
        tgaData[ p ] = pixel.b_;
        p++;

        tgaData[ p ] = pixel.g_;
        p++;

        tgaData[ p ] = pixel.r_;
        p++;
            

        j++;
        if( j == width_ )
        {
            j = 0;
            i++;
        }        
    }
    
    fwrite( tgaData, width_ * height_ * 3 , 1, tgaFile );

    const char* tgaFooter = "TRUEVISION-XFILE.";
    
    fwrite( tgaFooter, 18, 1, tgaFile );

    fclose( tgaFile );

}

SOFIA_NS_END
