#include <game/util/fontConversion.h>

// --------------------
// VARIABLES
// --------------------

static const u16 utfCharOffset[] = {
    0x20,   0x7D,   0xA1,   0xA9,   0xAE,   0xB0,   0xBF,   0xC4,   0xC7,   0xD1,   0xD6,   0xD9,   0xDF,   0xE4,   0xE7,   0xF1,   0xF6,   0xF9,   0x152,
    0x2C6,  0x2DC,  0x201C, 0x2022, 0x2026, 0x2033, 0x203B, 0x20AC, 0x2122, 0x2190, 0x221E, 0x2234, 0x25A0, 0x25B2, 0x25BC, 0x25C6, 0x25CB, 0x25CE, 0x2605,
    0x266A, 0x266D, 0x3000, 0x300C, 0x3012, 0x3041, 0x3092, 0x30A1, 0x30F2, 0x30FC, 0xE000, 0xE015, 0xE028, 0xFF01, 0xFF0F, 0xFF1F, 0xFF3C, 0xFF3E, 0xFF5B,
};

static const s32 fontCharOffset[] = { 0,    0x5C, 0x5E, 0x61, 0x62, 0x63, 0x65,  0x69,  0x6A,  0x73,  0x77,  0x79,  0x7D,  0x81,  0x82,  0x8B,  0x8F,  0x91,  0x95,
                                      0x97, 0x98, 0x99, 0x9B, 0x9C, 0x9D, 0x9E,  0x9F,  0xA0,  0xA1,  0xA5,  0xA6,  0xA7,  0xA9,  0xAB,  0xAD,  0xAF,  0xB0,  0xB2,
                                      0xB4, 0xB5, 0xB6, 0xB9, 0xBB, 0xBC, 0x10B, 0x10D, 0x15C, 0x161, 0x162, 0x176, 0x17E, 0x17F, 0x180, 0x181, 0x182, 0x183, 0x184 };

static const s32 fontCharPageSize[] = {
    92, 2, 3, 1, 1, 2, 4, 1, 9, 4, 2, 4, 4, 1, 9, 4, 2, 4, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 4, 1, 1, 2, 2, 2, 2, 1, 2, 2, 1, 1, 3, 2, 1, 79, 2, 79, 5, 1, 20, 8, 1, 1, 1, 1, 1, 1, 4,
};

// --------------------
// FUNCTIONS
// --------------------

s32 GetFontCharacterFromUTF(u32 character)
{
    // go through each page to find the font character
    s32 page  = 0;
    s32 count = 56;
    while (page < count)
    {
        s32 nextID = ((page + count) >> 1) + ((page + count) & 1);
        if (utfCharOffset[nextID] <= character)
            page = nextID;
        else
            count = nextID - 1;
    }

    // return font character
    s32 fontChar = character - utfCharOffset[page];
    if (fontChar >= fontCharPageSize[page])
        return 0;
    else
        return fontChar + fontCharOffset[page];
}