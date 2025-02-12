#ifndef RUSH_BINARYBUNDLE_H
#define RUSH_BINARYBUNDLE_H

#include <global.h>
#include <game/system/allocator.h>
#include <game/graphics/renderCore.h>

#ifdef __cplusplus
extern "C"
{
#endif

// --------------------
// CONSTANTS
// --------------------

#define BINARYBUNDLE_AUTO_ALLOC_HEAD ((void *)(size_t)0)
#define BINARYBUNDLE_AUTO_ALLOC_TAIL ((void *)(size_t) - 1)

// --------------------
// STRUCTS
// --------------------

typedef struct BBHeader_
{
    u32 signature;
    u32 fileCount;
    // BBFile files[fileCount];
} BBHeader;

typedef struct BBFile_
{
    u32 offset;
    u32 size;
} BBFile;

// --------------------
// FUNCTIONS
// --------------------

void InitBinaryBundleSystem(void);
u32 GetBundleFileSize(const char *path, u16 id);
void *ReadFileFromBundle(const char *path, u16 id, void *memory);

// --------------------
// INLINE FUNCTIONS
// --------------------

RUSH_INLINE void GetCompressedFileFromBundle(const char *bundlePath, u16 fileID, void **memory, BOOL loadFromTail, BOOL allocFromTail)
{
    void *compressedData = ReadFileFromBundle(bundlePath, fileID, loadFromTail ? BINARYBUNDLE_AUTO_ALLOC_TAIL : BINARYBUNDLE_AUTO_ALLOC_HEAD);
    if (allocFromTail)
    {
        (*memory) = (NNSiFndArchiveHeader *)HeapAllocTail(HEAP_USER, MI_GetUncompressedSize(compressedData));
    }
    else
    {
        (*memory) = (NNSiFndArchiveHeader *)HeapAllocHead(HEAP_USER, MI_GetUncompressedSize(compressedData));
    }
    RenderCore_CPUCopyCompressed(compressedData, (*memory));
    HeapFree(HEAP_USER, compressedData);
}

RUSH_INLINE void GetCompressedFileFromBundleEx(const char *bundlePath, u16 fileID, void **memory, u32 *fileSize, BOOL loadFromTail, BOOL allocFromTail)
{
    void *compressedData = ReadFileFromBundle(bundlePath, fileID, loadFromTail ? BINARYBUNDLE_AUTO_ALLOC_TAIL : BINARYBUNDLE_AUTO_ALLOC_HEAD);

    (*fileSize) = MI_GetUncompressedSize(compressedData);
    if (allocFromTail)
    {
        (*memory) = (NNSiFndArchiveHeader *)HeapAllocTail(HEAP_USER, (*fileSize));
    }
    else
    {
        (*memory) = (NNSiFndArchiveHeader *)HeapAllocHead(HEAP_USER, (*fileSize));
    }
    RenderCore_CPUCopyCompressed(compressedData, (*memory));
    HeapFree(HEAP_USER, compressedData);
}

#ifdef __cplusplus
}
#endif

#endif // RUSH_BINARYBUNDLE_H
