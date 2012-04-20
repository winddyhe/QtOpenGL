#ifndef QBIT_H
#define QBIT_H

#include <QtGlobal>
#include "qcommon.h"

class QBit
{
public:
    QBit();
    ~QBit();

    bool create(unsigned int row, unsigned int col);

    inline void set(unsigned int row, unsigned int col, bool bFlag = true)
    {
        Q_ASSERT(m_pBits);

        bFlag ? m_pBits[(row*m_col + col)/32] |=  (1<<(row*m_col + col)%32)
                :m_pBits[(row*m_col + col)/32] &= ~(1<<(row*m_col + col)%32);
    }

    void reset();

    inline bool isTrue(unsigned int row, unsigned int col)
    {
        Q_ASSERT(m_pBits);

        return (m_pBits[(row*m_col + col)/32] & (1<<(row*m_col + col)%32)) != 0;
    }

private:
    unsigned int*       m_pBits;
    unsigned int        m_row;
    unsigned int        m_col;
};

#endif // QBIT_H
