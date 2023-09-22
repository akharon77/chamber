#ifndef BUF_LIST_H
#define BUF_LIST_H

#include <unistd.h>

#include "node_struct.hpp"

template<typename T>
class BufferList
{
    uint32_t m_size;
    uint32_t m_cap;

    int32_t  m_head;
    Node<T> *m_buf;

public:
    BufferList (uint32_t cap = 0);
    ~BufferList();

    // TODO
    BufferList(const BufferList &rhs) = delete;
    BufferList& operator = (const BufferList &rhs) = delete;

    void    Add(int32_t  anch);
    int32_t Pop();

    // Node*   BufferListGet     (BufferList *lst, int32_t anch);

    void    Realloc(uint32_t new_cap);

    void    Clear();

    inline Node<T>* Get(int32_t anch)
    {
        return m_buf + anch;
    }
};

#endif  // BUF_LIST_H

