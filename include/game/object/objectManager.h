#ifndef RUSH2_OBJECT_MANAGER_H
#define RUSH2_OBJECT_MANAGER_H

#include <game/object/objData.h>
#include <game/graphics/drawReqTask.h>

// --------------------
// ENUMS
// --------------------

enum ObjectManagerFlag_
{
    OBJECTMANAGER_FLAG_NONE = 0,

    OBJECTMANAGER_FLAG_1                    = 1 << 0,
    OBJECTMANAGER_FLAG_2                    = 1 << 1,
    OBJECTMANAGER_FLAG_4                    = 1 << 2,
    OBJECTMANAGER_FLAG_8                    = 1 << 3,
    OBJECTMANAGER_FLAG_USE_BLOCK_COLLISIONS = 1 << 4,
    OBJECTMANAGER_FLAG_20                   = 1 << 5,
    OBJECTMANAGER_FLAG_40                   = 1 << 6,
    OBJECTMANAGER_FLAG_80                   = 1 << 7,
    OBJECTMANAGER_FLAG_100                  = 1 << 8,
    OBJECTMANAGER_FLAG_200                  = 1 << 9,
    OBJECTMANAGER_FLAG_400                  = 1 << 10,
    OBJECTMANAGER_FLAG_800                  = 1 << 11,
    OBJECTMANAGER_FLAG_1000                 = 1 << 12,
    OBJECTMANAGER_FLAG_2000                 = 1 << 13,
    OBJECTMANAGER_FLAG_4000                 = 1 << 14,
    OBJECTMANAGER_FLAG_8000                 = 1 << 15,
    OBJECTMANAGER_FLAG_10000                = 1 << 16,
    OBJECTMANAGER_FLAG_20000                = 1 << 17,
    OBJECTMANAGER_FLAG_40000                = 1 << 18,
    OBJECTMANAGER_FLAG_80000                = 1 << 19,
};
typedef u32 ObjectManagerFlag;

enum ObjectDataWorkID
{
    OBJDATAWORK_0,
    OBJDATAWORK_1,
    OBJDATAWORK_2,
    OBJDATAWORK_3,
    OBJDATAWORK_4,
    OBJDATAWORK_5,
    OBJDATAWORK_6,
    OBJDATAWORK_7,
    OBJDATAWORK_8,
    OBJDATAWORK_9,
    OBJDATAWORK_10,
    OBJDATAWORK_11,
    OBJDATAWORK_12,
    OBJDATAWORK_13,
    OBJDATAWORK_14,
    OBJDATAWORK_15,
    OBJDATAWORK_16,
    OBJDATAWORK_17,
    OBJDATAWORK_18,
    OBJDATAWORK_19,
    OBJDATAWORK_20,
    OBJDATAWORK_21,
    OBJDATAWORK_22,
    OBJDATAWORK_23,
    OBJDATAWORK_24,
    OBJDATAWORK_25,
    OBJDATAWORK_26,
    OBJDATAWORK_27,
    OBJDATAWORK_28,
    OBJDATAWORK_29,
    OBJDATAWORK_30,
    OBJDATAWORK_31,
    OBJDATAWORK_32,
    OBJDATAWORK_33,
    OBJDATAWORK_34,
    OBJDATAWORK_35,
    OBJDATAWORK_36,
    OBJDATAWORK_37,
    OBJDATAWORK_38,
    OBJDATAWORK_39,
    OBJDATAWORK_40,
    OBJDATAWORK_41,
    OBJDATAWORK_42,
    OBJDATAWORK_43,
    OBJDATAWORK_44,
    OBJDATAWORK_45,
    OBJDATAWORK_46,
    OBJDATAWORK_47,
    OBJDATAWORK_48,
    OBJDATAWORK_49,
    OBJDATAWORK_50,
    OBJDATAWORK_51,
    OBJDATAWORK_52,
    OBJDATAWORK_53,
    OBJDATAWORK_54,
    OBJDATAWORK_55,
    OBJDATAWORK_56,
    OBJDATAWORK_57,
    OBJDATAWORK_58,
    OBJDATAWORK_59,
    OBJDATAWORK_60,
    OBJDATAWORK_61,
    OBJDATAWORK_62,
    OBJDATAWORK_63,
    OBJDATAWORK_64,
    OBJDATAWORK_65,
    OBJDATAWORK_66,
    OBJDATAWORK_67,
    OBJDATAWORK_68,
    OBJDATAWORK_69,
    OBJDATAWORK_70,
    OBJDATAWORK_71,
    OBJDATAWORK_72,
    OBJDATAWORK_73,
    OBJDATAWORK_74,
    OBJDATAWORK_75,
    OBJDATAWORK_76,
    OBJDATAWORK_77,
    OBJDATAWORK_78,
    OBJDATAWORK_79,
    OBJDATAWORK_80,
    OBJDATAWORK_81,
    OBJDATAWORK_82,
    OBJDATAWORK_83,
    OBJDATAWORK_84,
    OBJDATAWORK_85,
    OBJDATAWORK_86,
    OBJDATAWORK_87,
    OBJDATAWORK_88,
    OBJDATAWORK_89,
    OBJDATAWORK_90,
    OBJDATAWORK_91,
    OBJDATAWORK_92,
    OBJDATAWORK_93,
    OBJDATAWORK_94,
    OBJDATAWORK_95,
    OBJDATAWORK_96,
    OBJDATAWORK_97,
    OBJDATAWORK_98,
    OBJDATAWORK_99,
    OBJDATAWORK_100,
    OBJDATAWORK_101,
    OBJDATAWORK_102,
    OBJDATAWORK_103,
    OBJDATAWORK_104,
    OBJDATAWORK_105,
    OBJDATAWORK_106,
    OBJDATAWORK_107,
    OBJDATAWORK_108,
    OBJDATAWORK_109,
    OBJDATAWORK_110,
    OBJDATAWORK_111,
    OBJDATAWORK_112,
    OBJDATAWORK_113,
    OBJDATAWORK_114,
    OBJDATAWORK_115,
    OBJDATAWORK_116,
    OBJDATAWORK_117,
    OBJDATAWORK_118,
    OBJDATAWORK_119,
    OBJDATAWORK_120,
    OBJDATAWORK_121,
    OBJDATAWORK_122,
    OBJDATAWORK_123,
    OBJDATAWORK_124,
    OBJDATAWORK_125,
    OBJDATAWORK_126,
    OBJDATAWORK_127,
    OBJDATAWORK_128,
    OBJDATAWORK_129,
    OBJDATAWORK_130,
    OBJDATAWORK_131,
    OBJDATAWORK_132,
    OBJDATAWORK_133,
    OBJDATAWORK_134,
    OBJDATAWORK_135,
    OBJDATAWORK_136,
    OBJDATAWORK_137,
    OBJDATAWORK_138,
    OBJDATAWORK_139,
    OBJDATAWORK_140,
    OBJDATAWORK_141,
    OBJDATAWORK_142,
    OBJDATAWORK_143,
    OBJDATAWORK_144,
    OBJDATAWORK_145,
    OBJDATAWORK_146,
    OBJDATAWORK_147,
    OBJDATAWORK_148,
    OBJDATAWORK_149,
    OBJDATAWORK_150,
    OBJDATAWORK_151,
    OBJDATAWORK_152,
    OBJDATAWORK_153,
    OBJDATAWORK_154,
    OBJDATAWORK_155,
    OBJDATAWORK_156,
    OBJDATAWORK_157,
    OBJDATAWORK_158,
    OBJDATAWORK_159,
    OBJDATAWORK_160,
    OBJDATAWORK_161,
    OBJDATAWORK_162,
    OBJDATAWORK_163,
    OBJDATAWORK_164,
    OBJDATAWORK_165,
    OBJDATAWORK_166,
    OBJDATAWORK_167,
    OBJDATAWORK_168,
    OBJDATAWORK_169,
    OBJDATAWORK_170,
    OBJDATAWORK_171,
    OBJDATAWORK_172,
    OBJDATAWORK_173,
    OBJDATAWORK_174,
    OBJDATAWORK_175,
    OBJDATAWORK_176,
    OBJDATAWORK_177,
    OBJDATAWORK_178,
    OBJDATAWORK_179,
    OBJDATAWORK_180,
    OBJDATAWORK_181,
    OBJDATAWORK_182,
    OBJDATAWORK_183,
    OBJDATAWORK_184,
    OBJDATAWORK_185,
    OBJDATAWORK_186,
    OBJDATAWORK_187,
    OBJDATAWORK_188,
    OBJDATAWORK_189,
    OBJDATAWORK_190,
    OBJDATAWORK_191,
    OBJDATAWORK_192,
    OBJDATAWORK_193,
    OBJDATAWORK_194,
    OBJDATAWORK_195,
    OBJDATAWORK_196,
    OBJDATAWORK_197,
    OBJDATAWORK_198,
    OBJDATAWORK_199,
    OBJDATAWORK_200,
    OBJDATAWORK_201,
    OBJDATAWORK_202,
    OBJDATAWORK_203,
    OBJDATAWORK_204,
};

// --------------------
// STRUCTS
// --------------------

struct ObjectManager
{
    VecFx32 scale;
    fx16 offset[2];
    fx32 speed;
    Vec2Fx32 scroll;
    s32 depth;
    fx32 timer;
    fx32 timer_fx;
    ObjectManagerFlag flag;
    Vec2Fx32 camera[2];
    Camera3D *cameraConfig;
    void (*cameraFunc)(fx32 *x, fx32 *y);
    VecFx16 lightDirs[4];
    u16 lightCount;
    u16 spriteMode;
    u8 col_through_dot;
    OBS_DATA_WORK *pData;
    s32 data_max;
};

// --------------------
// VARIABLES
// --------------------

extern struct ObjectManager g_obj;

// --------------------
// FUNCTIONS
// --------------------

void CreateObjectManager(void);

void EnableObjectManagerFlag2(void);
void DisableObjectManagerFlag2(void);
BOOL ObjectPauseCheck(u32 flag);
void AllocObjectFileWork(u32 count);
void *GetObjectFileWork(s32 id);
void ReleaseObjectFileWork(void);
void SetObjOffset(s16 x, s16 y);
void SetObjSpeed(fx32 speed);
fx32 GetObjSpeed(void);
void SetObjCameraPosition(fx32 x1, fx32 y1, fx32 x2, fx32 y2);

// --------------------
// INLINE FUNCTIONS
// --------------------

#define GetObjectDataWork(id)   ((OBS_DATA_WORK *)GetObjectFileWork(id))
#define GetObjectSpriteRef(id)  ((OBS_SPRITE_REF *)GetObjectFileWork(id))
#define GetObjectTextureRef(id) ((OBS_TEXTURE_REF *)GetObjectFileWork(id))

#endif // RUSH2_OBJECT_MANAGER_H
