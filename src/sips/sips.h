
#ifndef SIPS_H_INCLUDED
#define SIPS_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef SIPSSPEC
#define SIPSSPEC
#endif
    
#ifndef SIPSEXTERN
#define SIPSEXTERN
#endif

    /************************************************/
    typedef unsigned char byte_t;
    struct sips_info_t;

    typedef struct
    {
        byte_t*     ptr;
        unsigned    size;
    } sips_buffer;

    typedef void (*schipsAllocator_t)(struct sips_info_t* info, sips_buffer* buf, unsigned size);

#define SIPS_CRC                0x0001U
#define SIPS_ORIGINALSIZE       0x0002U
#define SIPS_TARGETSIZE         0x0004U
#define SIPS_PATCHNAME          0x0008U
#define SIPS_ORIGINALNAME       0x0010U

    /************************************************/
    typedef struct sips_info_t
    {
        sips_buffer         originalData;
        sips_buffer         patchData;
        sips_buffer         modifiedData;

        unsigned            flags;
        
        unsigned            expectedCrc;
        unsigned            expectedSize;
        unsigned            patchCrc;
        unsigned            truncateSize;

        const char*         patchName;
        const char*         originalName;
        const char*         errorMsg;

        void*               userData;
        schipsAllocator_t   allocateProc;

        void*               private_internal;
    } sips_info;


    /***********************************************************/
#define SIPSERR_OK              0
#define SIPSERR_MEMORY          1
#define SIPSERR_BADPARAM        2
#define SIPSERR_UNKNOWN         3
    
    SIPSEXTERN sips_info*   SIPSSPEC    sips_create             (void);
    SIPSEXTERN int          SIPSSPEC    sips_destroy            (sips_info* info);
    SIPSEXTERN int          SIPSSPEC    sips_calcOriginalCrc    (sips_info* info);
    SIPSEXTERN int          SIPSSPEC    sips_getPatchMetaData   (sips_info* info);
    SIPSEXTERN int          SIPSSPEC    sips_applyPatch         (sips_info* info);
    SIPSEXTERN int          SIPSSPEC    sips_generatePatch      (sips_info* info);

#ifdef __cplusplus
}
#endif


#endif  // SIPS_H_INCLUDED