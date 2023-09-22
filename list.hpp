#ifndef LIST_H
#define LIST_H

#include <stdint.h>

#include "buf_list.h"

template<typename T>
class List
{
public:
    uint32_t       m_size;

    int32_t        m_dummy_head;
    BufferList<T> *m_free_buf;

    List(BufferList<T> *free_buf);
    ~List();

    // TODO
    List& operator = (const List &rhs) = delete;
    List(const List &rhs) = delete;

    int32_t     InsertBefore (const T &val, int32_t anch);
    int32_t     InsertAfter  (const T &val, int32_t anch);
    void        Erase        (              int32_t anch);

    int32_t     PushBack     (const T &val);
    int32_t     PushFront    (const T &val);

    void        PopBack      ();
    void        PopFront     ();

    uint32_t    GetSize      ();

    int32_t     GetTail      ();

    inline Node<T>* Get(int32_t anch)
    {
        return m_free_buf->Get(anch);
    }
         
    inline int32_t GetHead()
    {
        return m_free_buf->m_buf[m_dummy_head].next;
    }
};

#endif  // LIST_H
 
