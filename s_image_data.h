#if !defined(S_IMAGE_DATA_H)
#define S_IMAGE_DATA_H 1

// Sofia (Sofia_aleph)
//
// Sofia, my way for developing knowledge
//
// (c) 2004 Ludovic LIEVRE aka Ludorg

// fractal generator : ImageData
//
// 0.0.1 2004/07/07 : file creation
//

#include <vector>

#include "sofia.h"

SOFIA_NS_BEGIN

typedef byte TComponent;

struct TPixel
{
    TPixel(TComponent r, TComponent g, TComponent b) : r_(r), g_(g), b_(b), a_(0) {}
    TPixel() : r_(0), g_(0), b_(0), a_(0) {}
    TPixel(const uint p)
    {
        uint a = (0xFF000000 & p) >> 24;
        uint r = (0x00FF0000 & p) >> 16;
        uint g = (0x0000FF00 & p) >> 8;
        uint b = (0x000000FF & p);

        r_ = (TComponent)r;
        g_ = (TComponent)g;
        b_ = (TComponent)b;
        a_ = (TComponent)a;
    }

    operator const uint() const { return (uint)a_ << 24 | r_ << 16 | g_ << 8 | b_; }

    TComponent a_;
    TComponent r_;
    TComponent g_;
    TComponent b_;
};

class ImageData
{
private:
    size_t width_;
    size_t height_;

    std::vector<std::vector<TPixel>> data_;

    ImageData();

public:
    ImageData(size_t width, size_t height);

    void set(const uint x, const uint y, const TPixel pixel);
    TPixel get(const uint x, const uint y) const;

    void writeTGA(const char *fileName);
};

SOFIA_NS_END

#endif // S_IMAGE_DATA
