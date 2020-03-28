#if !defined( S_FRACTAL_SCENARIO_H )
#define S_FRACTAL_SCENARIO_H 1

// Sofia (Sofia_aleph)
//
// Sofia, my way for developing knowledge
//
// (c) 2004 Ludovic LIEVRE aka Ludorg

// fractal generator : XML scenario for fractal generator
// 
// 0.0.1 2004/07/10 : file creation

#include <list>

#include "sofia.h"

#include "s_fractal.h"

SOFIA_NS_BEGIN

class FractalScenario
{
private:
    std::list<MandelbrotParams>     mandelbrotParams_;
    std::list<JuliaParams>          juliaParams_;

    bool                            isLoaded_;

public:
    FractalScenario();
    FractalScenario( const char* fileName );

    bool load( const char* fileName );
    void run();

};

SOFIA_NS_END

#endif //S_FRACTAL_SCENARIO_H
