// Sofia (Sofia_aleph)
//
// Sofia, my way for developing knowledge
//
// (c) 2004 Ludovic LIEVRE aka Ludorg

// fractal generator : XML scenario for fractal generator
// 
// 0.0.1 2004/07/10 : file creation

#include <iostream>

#include "s_fractal_scenario.h"

#include "s_xml_doc.h"
#include "s_xml_element.h"

SOFIA_NS_BEGIN

void Dump( const MandelbrotParams& params );
void Dump( const JuliaParams& params );

FractalScenario::FractalScenario() : isLoaded_( false )
{
}

FractalScenario::FractalScenario( const char* fileName ) : isLoaded_( false )
{
    load( fileName );
}

bool FractalScenario::load( const char* fileName )
{
    if( true == isLoaded_ )
        return true;

    XMLDoc doc;
    doc.parse( fileName );

    XMLElement root( doc.getRootNode() );

    std::vector<XMLElement*> images = root.getElementsByPath( "Scenario/Image" );

    for( std::vector<XMLElement*>::const_iterator it = images.begin();
        it != images.end();
        it++ )
    {
        std::string type        = (*(*it))[ "Type" ]->toString();
        std::string paramsId    = (*(*it))[ "ParamsId" ]->toString();

        std::cout << "Image/Type : " << type << std::endl;
        std::cout << "Image/ParamsId : " << paramsId << std::endl;

        if( 'M' == type[ 0 ] ) // Mandelbrot
        {
            std::vector<XMLElement*> mandelbrot = 
                root.getElementsByPath( "MandelbrotParams" );

            for( std::vector<XMLElement*>::const_iterator itParams = mandelbrot.begin();
                itParams != mandelbrot.end();
                itParams++ )
            {
                if( paramsId == (*(*itParams)).getAttribute( "id" ) )
                {
                    MandelbrotParams params;

                    params.width_           =   (*(*itParams))[ "width" ]->toUInt();
                    params.height_          =   (*(*itParams))[ "height" ]->toUInt();

                    params.maxIterations_   =   (*(*itParams))[ "maxIterations" ]->toUInt();

                    params.minC_.real(          (*(*itParams))[ "minC/real" ]->toDouble() ); 
                    params.minC_.imag(          (*(*itParams))[ "minC/imag" ]->toDouble() ); 
                    
                    params.maxC_.real(          (*(*itParams))[ "maxC/real" ]->toDouble() ); 
                    params.maxC_.imag(          (*(*itParams))[ "maxC/imag" ]->toDouble() ); 

                    params.minColor_.r_     =   (*(*itParams))[ "minColor/red" ]->toByte();
                    params.minColor_.g_     =   (*(*itParams))[ "minColor/green" ]->toByte();
                    params.minColor_.b_     =   (*(*itParams))[ "minColor/blue" ]->toByte();
                    
                    params.maxColor_.r_     =   (*(*itParams))[ "maxColor/red" ]->toByte();
                    params.maxColor_.g_     =   (*(*itParams))[ "maxColor/green" ]->toByte();
                    params.maxColor_.b_     =   (*(*itParams))[ "maxColor/blue" ]->toByte();

                    params.outputFile_      =   (*(*itParams))[ "outputFile" ]->toString().c_str(); 
                    
                    Dump( params );
                    
                    mandelbrotParams_.push_back( params );
                }
            }
        }
        else if( 'J' == type[ 0 ] ) // Julia
        {
            std::vector<XMLElement*> julia = 
                root.getElementsByPath( "JuliaParams" );

            for( std::vector<XMLElement*>::const_iterator itParams = julia.begin();
                itParams != julia.end();
                itParams++ )
            {
                if( paramsId == (*(*itParams)).getAttribute( "id" ) )
                {
                    JuliaParams params;

                    params.width_           =   (*(*itParams))[ "width" ]->toUInt();
                    params.height_          =   (*(*itParams))[ "height" ]->toUInt();

                    params.maxIterations_   =   (*(*itParams))[ "maxIterations" ]->toUInt();

                    params.minZ_.real(          (*(*itParams))[ "minZ/real" ]->toDouble() ); 
                    params.minZ_.imag(          (*(*itParams))[ "minZ/imag" ]->toDouble() ); 
                    
                    params.maxZ_.real(          (*(*itParams))[ "maxZ/real" ]->toDouble() ); 
                    params.maxZ_.imag(          (*(*itParams))[ "maxZ/imag" ]->toDouble() ); 
                    
                    params.c_.real(             (*(*itParams))[ "c/real" ]->toDouble() ); 
                    params.c_.imag(             (*(*itParams))[ "c/imag" ]->toDouble() ); 

                    params.minColor_.r_     =   (*(*itParams))[ "minColor/red" ]->toByte();
                    params.minColor_.g_     =   (*(*itParams))[ "minColor/green" ]->toByte();
                    params.minColor_.b_     =   (*(*itParams))[ "minColor/blue" ]->toByte();
                    
                    params.maxColor_.r_     =   (*(*itParams))[ "maxColor/red" ]->toByte();
                    params.maxColor_.g_     =   (*(*itParams))[ "maxColor/green" ]->toByte();
                    params.maxColor_.b_     =   (*(*itParams))[ "maxColor/blue" ]->toByte();

                    params.outputFile_      =   (*(*itParams))[ "outputFile" ]->toString().c_str(); 
                    
                    Dump( params );
                    
                    juliaParams_.push_back( params );
                }
            }
        }
        else
        {
            return isLoaded_;
        }
    }

    isLoaded_ = true;

    return isLoaded_;
}

void FractalScenario::run()
{
    
    for( std::list<MandelbrotParams>::const_iterator it = mandelbrotParams_.begin();
        it != mandelbrotParams_.end();
        it++ )
    {               
        std::cout << "Processing " << it->outputFile_.c_str() << std::endl;     

        ImageData* img;
        img = Mandelbrot( *it );
        img->writeTGA( it->outputFile_.c_str() );
        delete img;

        std::cout << "Completed " << std::endl;
    }

    for( std::list<JuliaParams>::const_iterator it = juliaParams_.begin();
        it != juliaParams_.end();
        it++ )
    {        
        std::cout << "Processing " << it->outputFile_.c_str() << std::endl;
        
        ImageData* img;
        img = Julia( *it );
        img->writeTGA( it->outputFile_.c_str() );

        delete img;

        std::cout << "Completed " << std::endl;
    }

}

void Dump( const MandelbrotParams& params )
{
    std::cout << "MandelbrotParams"                                         << std::endl;
    std::cout << "\t width          "   << params.width_                    << std::endl;
    std::cout << "\t height         "   << params.height_                   << std::endl;

    std::cout << "\t maxIterations  "   << params.maxIterations_            << std::endl;

    std::cout << "\t minC"                                                  << std::endl;
    std::cout << "\t\t real         "   << params.minC_.real()              << std::endl;
    std::cout << "\t\t imag         "   << params.minC_.imag()              << std::endl;
    
    std::cout << "\t maxC"                                                  << std::endl;
    std::cout << "\t\t real         "   << params.maxC_.real()              << std::endl;
    std::cout << "\t\t imag         "   << params.maxC_.imag()              << std::endl;

    std::cout << "\t minColor"                                              << std::endl;
    std::cout << "\t\t red          "   << (uint) params.minColor_.r_       << std::endl;
    std::cout << "\t\t green        "   << (uint) params.minColor_.g_       << std::endl;
    std::cout << "\t\t blue         "   << (uint) params.minColor_.b_       << std::endl;
    
    std::cout << "\t maxColor"                                              << std::endl;
    std::cout << "\t\t red          "   << (uint) params.maxColor_.r_       << std::endl;
    std::cout << "\t\t green        "   << (uint) params.maxColor_.g_       << std::endl;
    std::cout << "\t\t blue         "   << (uint) params.maxColor_.b_       << std::endl;

    std::cout << "\t fileName       "   << params.outputFile_               << std::endl;

}

void Dump( const JuliaParams& params )
{
    std::cout << "JuliaParams"                                              << std::endl;
    std::cout << "\t width          "   << params.width_                    << std::endl;
    std::cout << "\t height         "   << params.height_                   << std::endl;

    std::cout << "\t maxIterations  "   << params.maxIterations_            << std::endl;

    std::cout << "\t minZ"                                                  << std::endl;
    std::cout << "\t\t real         "   << params.minZ_.real()              << std::endl;
    std::cout << "\t\t imag         "   << params.minZ_.imag()              << std::endl;
    
    std::cout << "\t maxZ"                                                  << std::endl;
    std::cout << "\t\t real         "   << params.maxZ_.real()              << std::endl;
    std::cout << "\t\t imag         "   << params.maxZ_.imag()              << std::endl;

    std::cout << "\t c"                                                     << std::endl;
    std::cout << "\t\t real         "   << params.c_.real()                 << std::endl;
    std::cout << "\t\t imag         "   << params.c_.imag()                 << std::endl;

    std::cout << "\t minColor"                                              << std::endl;
    std::cout << "\t\t red          "   << (uint) params.minColor_.r_       << std::endl;
    std::cout << "\t\t green        "   << (uint) params.minColor_.g_       << std::endl;
    std::cout << "\t\t blue         "   << (uint) params.minColor_.b_       << std::endl;
    
    std::cout << "\t maxColor"                                              << std::endl;
    std::cout << "\t\t red          "   << (uint) params.maxColor_.r_       << std::endl;
    std::cout << "\t\t green        "   << (uint) params.maxColor_.g_       << std::endl;
    std::cout << "\t\t blue         "   << (uint) params.maxColor_.b_       << std::endl;

    std::cout << "\t fileName       "   << params.outputFile_               << std::endl;


}


SOFIA_NS_END
