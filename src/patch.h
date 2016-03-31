
#ifndef SCHIPS_PATCH_H_INCLUDED
#define SCHIPS_PATCH_H_INCLUDED

#include <iostream>
#include <cstdint>
#include <vector>
#include <stdexcept>

namespace schips
{
    typedef std::uint8_t        u8;
    typedef std::uint_fast32_t  number_t;
        
    class Patch
    {
    public:
        class Error : public std::runtime_error
        {
            public:   Error(const char* msg) : runtime_error(msg) {}
        };
        
        struct MetaData
        {
            std::vector<number_t>       Crcs;
            std::vector<number_t>       srcSizes;
            number_t                    dstSize;
        };
        
    private:
        struct Block
        {
            number_t    offset  = 0;
            number_t    size    = 0;
            u8          rleByte = 0;
            
            bool        isRle   = false;
            bool        isEof   = false;
        };
        
    private:
        static bool     readBytes(std::istream& strm, u8* buf, std::size_t size, bool failOnEof = true);
        static number_t read3(std::istream& strm);
        static number_t read2(std::istream& strm);
        static u8       read1(std::istream& strm);
        static Block    getBlock(std::istream& strm);
    
    private:
        
        std::istream&   patchFile;
        Block           lastBlock;
        u8              lastBlockData[6];   // enough to hold 'PATCH_'
    };
}

#endif
