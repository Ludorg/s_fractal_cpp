// Sofia (Sofia_aleph)
//
// Sofia, my way for developing knowledge
//
// (c) 2004 Ludovic LIEVRE aka Ludorg

// 
// 0.0.1 2004/07/05 : file creation
//

// fractal generator

#include <iostream>

#include "sofia.h"

#include "s_fractal_scenario.h"

SOFIA_NS_USE

int main( int argc, char** argv )
{    
    std::cout << "fractal v1.0.0 (c) 2004 Ludovic LIEVRE aka Ludorg" << std::endl;
    
    FractalScenario scenario;

    if( argc == 1 )
    {
        if( false == scenario.load( "fractal.xml" ) )
        {
            std::cerr << "Error while loading fractal.xml" << std::endl 
                << "Aborting..." << std::endl;
            return -1;
        }
    }
    else
    {
        if( false == scenario.load( argv[ 1 ] ) )
        {
            std::cerr << "Error while loading " << argv[ 1 ] << std::endl 
                << "Aborting..." << std::endl;
            return -1;
        }
    }

    scenario.run();
}

