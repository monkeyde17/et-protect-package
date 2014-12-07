//
//  ETProtectData.h
//  testcpp
//
//  Created by etond on 14/12/3.
//
//

#ifndef __ETPROTECTDATA__
#define __ETPROTECTDATA__

#include <stdlib.h>
#include <string>


class ETProtectData
{
public:
    ETProtectData()
    {
        /* init */
        m_uHashValue = 0;
        
        /* generate some dirty data */
        srand(time(NULL));
        for (int i = 0; i < sizeof(m_pDirtyBuf); i++)
        {
            m_pDirtyBuf[i] = rand() % 255;
        }
    }
    
    unsigned int getHashValue()
    {
        return m_uHashValue;
    }
    
    void setHashValue(unsigned int hash)
    {
        m_uHashValue = hash;
    }
    
    int getSize()
    {
        return sizeof(m_pDirtyBuf) + sizeof(m_uHashValue);
    }
    
private:
    /* the hash value */
    unsigned int m_uHashValue;
    /* dirty data */
    unsigned char m_pDirtyBuf[32];
};
#endif
