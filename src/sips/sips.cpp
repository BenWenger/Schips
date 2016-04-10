
#include <vector>
#include "sips.h"

namespace
{

class SipsImpl
{
public:
    SipsImpl()
    {
        info.originalData.ptr =     nullptr;
        info.originalData.size =    0;
        info.patchData.ptr =        nullptr;
        info.patchData.size =       0;
        info.modifiedData.ptr =     nullptr;
        info.modifiedData.size =    0;

        info.flags =                0;
        
        info.expectedCrc =          0;
        info.expectedSize =         0;
        info.patchCrc =             0;
        info.truncateSize =         0;
        
        info.patchName =            nullptr;
        info.originalName =         nullptr;
        info.errorMsg =             nullptr;

        info.userData =             nullptr;
        info.allocateProc =         nullptr;
        info.private_internal =     reinterpret_cast<void*>(this);
    }
    
    int calcOriginalCrc();
    int getPatchMetaData();
    int applyPatch();
    int generatePatch();

    static int handleException();


    sips_info info;


};


}

#define GETOBJ(info)    reinterpret_cast<SipsImpl*>(info->private_internal)

SIPSEXTERN sips_info*   SIPSSPEC    sips_create             (void)
{
    try
    {
        SipsImpl* obj = new SipsImpl();
        return &obj->info;
    }
    catch(...) {}

    return nullptr;
}

SIPSEXTERN int          SIPSSPEC    sips_destroy            (sips_info* info)
{
    try
    {
        if(!info)
            return SIPSERR_BADPARAM;
        delete GETOBJ(info);
        return SIPSERR_OK;
    }
    catch(...)
    {
        return SipsImpl::handleException();
    }
}

#define TIE_SIPS_FUNCTION(funcname)                                             \
    SIPSEXTERN int          SIPSSPEC    sips_##funcname    (sips_info* info)    \
    {                                                                           \
        try                                                                     \
        {                                                                       \
            if(!info)                                                           \
                return SIPSERR_BADPARAM;                                        \
            return GETOBJ(info)->funcname();                                    \
        }                                                                       \
        catch(...)                                                              \
        {                                                                       \
            return SipsImpl::handleException();                                 \
        }                                                                       \
    }


TIE_SIPS_FUNCTION( calcOriginalCrc  );
TIE_SIPS_FUNCTION( getPatchMetaData );
TIE_SIPS_FUNCTION( applyPatch       );
TIE_SIPS_FUNCTION( generatePatch    );
