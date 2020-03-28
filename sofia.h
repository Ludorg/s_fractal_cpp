// Sofia (Sofia_aleph)
//
// Sofia, my way for developing knowledge
//
// (c) 2004 Ludovic LIEVRE aka Ludorg

// 0.0.1 2004/05/02 : file creation
// 0.0.2 2004/06/03 : add version data

#if !defined(SOFIA_H)
#define SOFIA_H

// Namespace macros

#define SOFIA_NS_NAME Sofia_aleph
#define SOFIA_NS_BEGIN      \
    namespace SOFIA_NS_NAME \
    {
#define SOFIA_NS_END }
#define SOFIA_NS_USE using namespace SOFIA_NS_NAME;

// Version data

#define SOFIA_VERSION_MAJOR 1
#define SOFIA_VERSION_MINOR 0
#define SOFIA_VERSION_REVISION 4

#define SOFIA_VERSION_STRING "1.0.4"
#define SOFIA_TITLE "Sofia_aleph"

SOFIA_NS_BEGIN

// Basic types

typedef unsigned long ulong;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char byte;

SOFIA_NS_END

#endif
