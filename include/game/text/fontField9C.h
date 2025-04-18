
#ifndef RUSH_FONTFIELD9C_H
#define RUSH_FONTFIELD9C_H

#include <global.h>

#ifdef __cplusplus
extern "C"
{
#endif

// --------------------
// STRUCTS
// --------------------

typedef struct FontField_9C_
{
    u16 left;
    u16 top;
    u16 right;
    u16 bottom;
} FontField_9C;

// --------------------
// FUNCTIONS
// --------------------

NOT_DECOMPILED void FontField_9C__Init(FontField_9C *work);
NOT_DECOMPILED void FontField_9C__Func_2059670(void);
NOT_DECOMPILED BOOL FontField_9C__IsInvalid(FontField_9C *work);

#ifdef __cplusplus
}
#endif

#endif // RUSH_FONTFIELD9C_H
