
#include "patch.h"

namespace schips
{
    bool Patch::readBytes(std::istream& strm, u8* buf, std::size_t size, bool failOnEof)
    {
        strm.read(reinterpret_cast<char*>(buf),size);
        if(strm.gcount() != size)
        {
            if(strm.eof())
            {
                if(failOnEof)
                    throw Patch::Error("Unexpected EOF");
                return false;
            }
            throw Patch::Error("Stream entered a bad state during reading");
        }
        return true;
    }
    
    number_t Patch::read3(std::istream& strm)
    {
        u8 buf[3];
        readBytes(strm, buf, 3);
        
        return (buf[0] << 16) | (buf[1] << 8) | buf[2];
    }
    
    number_t Patch::read2(std::istream& strm)
    {
        u8 buf[2];
        readBytes(strm, buf, 2);
        
        return (buf[0] << 8) | buf[1];
    }
    
    u8 Patch::read1(std::istream& strm)
    {
        u8 v;
        readBytes(strm, &v, 1);
        return v;
    }
    
    
    Patch::Block Patch::getBlock(std::istream& strm)
    {
        Block blk;
        
        blk.offset = read3(strm);
        if( blk.offset == 0x00454F46 )   // special 'EOF' marker
        {
            blk.isEof = true;
            return blk;
        }
        
        // otherwise, not eof, just get the size
        blk.size = read2(strm);
        
        // is it RLE?
        if(blk.size == 0)
        {
            blk.isRle = true;
            blk.size = read2(strm);
            blk.rleByte = read1(strm);
        }
        
        return blk;
    }
    
}

