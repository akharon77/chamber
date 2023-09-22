#ifndef BUF_LIST_H
#define BUF_LIST_H

#include <unistd.h>

#include "node_struct.hpp"

template<typename T>
class BufferList
{
public:
    uint32_t m_size;
    uint32_t m_cap;

    int32_t  m_head;
    Node<T> *m_buf;

    BufferList (uint32_t cap = 1);
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

template<typename T>
BufferList<T>::BufferList(uint32_t cap) :
    m_size (cap),
    m_cap  (cap),
    m_head (0),
    m_buf  (new Node<T>[cap])
{
    Clear();
}

template<typename T>
BufferList<T>::~BufferList()
{
    delete[] m_buf;

    m_buf  = NULL;
    m_size = 0;
    m_cap  = 0;
}

template<typename T>
void BufferList<T>::Add(int32_t anch)
{
    m_buf[anch].next = m_head;
    m_head           = anch;

    ++m_size;
}

template<typename T>
void BufferList<T>::Realloc(uint32_t new_cap)
{
    Node<T> *new_buf = new Node<T>[new_cap];  // (Node*) realloc(lst->buf, new_cap * sizeof(Node));
    for (uint32_t i = 0; i < m_cap; ++i)
        new_buf[i] = m_buf[i];

    delete[] m_buf;

    m_buf = new_buf;
    
    uint32_t ind = m_cap;

    m_buf[m_cap - 1].next = ind;

    while (ind < new_cap)
    {
        m_buf[ind] = Node<T>
            {
                T(),
                ind + 1,
                -1
            };
            //     .val  = NULL,
            //     .next = ind + 1,
            //     .prev = -1 
            // };

        ++ind;
    }

    m_buf[new_cap - 1].next = -1;

    m_size += new_cap - m_cap;
    m_cap   = new_cap;
}

template<typename T>
int32_t BufferList<T>::Pop()
{
    if (m_size == 1)
        Realloc(m_cap * 2);

    int32_t res = m_head;
    m_head = m_buf[m_head].next;

    --m_size;

    return res;
}

template<typename T>
void BufferList<T>::Clear()
{
    uint32_t cap = m_cap;

    for (uint32_t ind = 0; ind < cap; ++ind)
        m_buf[ind] = Node<T>
            {
                T(),
                ind + 1,
                -1
            };
            //     .val  = NULL,
            //     .next = ind + 1,
            //     .prev = -1
            // };

    m_buf[cap - 1].next = -1;
}

// Node* BufferListGet(BufferList *lst, int32_t anch)
// {
//     return lst->buf + anch;
// }

#endif  // BUF_LIST_H

