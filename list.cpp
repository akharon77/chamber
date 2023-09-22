#include <fcntl.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "list.h"

template<typename T>
List<T>::List(BufferList<T> *free_buf)
{
    m_free_buf   = free_buf;
    m_dummy_head = BufferListPop(free_buf);

    m_free_buf->m_buf[m_dummy_head] = Node<T>
        {
            T(),
            m_dummy_head,
            m_dummy_head             
        };

    m_size = 0;
}

template<typename T>
List<T>::~List()
{
    BufferListDtor(m_free_buf);

    m_free_buf   = NULL;
    m_dummy_head = -1;
    m_size       =  0;
}

template<typename T>
int32_t List<T>::InsertBefore(const T &val, int32_t anch)
{
    int32_t npos = m_free_buf.Pop();

    int32_t anch_prev = m_free_buf->m_buf[anch].prev;

    m_free_buf->m_buf[npos] = Node<T>
        {
            val,
            anch,
            anch_prev
        };

    m_free_buf->m_buf[anch_prev].next = npos;
    m_free_buf->m_buf[anch     ].prev = npos;
    
    ++m_size;

    return npos;
}

template<typename T>
int32_t List<T>::InsertAfter(const T &val, int32_t anch)
{
    return InsertBefore(val, m_free_buf->m_buf[anch].next);
}

template<typename T>
void List<T>::Erase(int32_t anch)
{
    int32_t prev_anch = m_free_buf->m_buf[anch].prev,
            next_anch = m_free_buf->m_buf[anch].next;

    m_free_buf->m_buf[prev_anch].next = next_anch;
    m_free_buf->m_buf[next_anch].prev = prev_anch;

    m_free_buf.Add(m_free_buf, anch);

    --m_size;
}

template<typename T>
int32_t List<T>::PushBack (const T &val)
{
    return InsertBefore(val, m_dummy_head);
}

template<typename T>
int32_t List<T>::PushFront(const T &val)
{
    return InsertAfter (val, m_dummy_head);
}

template<typename T>
void List<T>::PopBack()
{
    Erase(GetTail());
}

template<typename T>
void List<T>::PopFront()
{
    Erase(GetHead());
}

// int32_t ListGetHead(List *lst)
// {
//     ASSERT(lst != NULL);
//     return lst->free_buf->buf[lst->dummy_head].next;
// }

template<typename T>
int32_t List<T>::GetTail()
{
    return m_free_buf->m_buf[m_dummy_head].prev;
}

template<typename T>
uint32_t List<T>::GetSize()
{
    return m_size;
}

// Node* ListGet(List *lst, int32_t anch)
// {
//     return BufferListGet(lst->free_buf, anch);
// }

