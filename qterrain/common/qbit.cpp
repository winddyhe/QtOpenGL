#include "qbit.h"

/*QBit*/
QBit::QBit()
{
    m_pBits = NULL;
    m_row = m_col = 0;
}

QBit::~QBit()
{
    safe_delete_array(m_pBits);
}

bool QBit::create(unsigned int row, unsigned int col)
{
    m_row = row;
    m_col = col;

    safe_delete_array(m_pBits);

    unsigned int size = row * col /32;

    if(row * col % 32)  size += 1;

    m_pBits = new unsigned int[size];

    memset(m_pBits, 0, size*4);

    return m_pBits != NULL;
}

void QBit::reset()
{
    unsigned int size = m_row * m_col / 32;

    if(m_row * m_col %32) size += 1;

    memset(m_pBits, 0, size*4);
}
