#ifndef SCX_PVBUFFER_HPP
#define SCX_PVBUFFER_HPP

#include <deque>
#include "Mutex.hpp"
#ifndef __MACH__
#include "SemVar.hpp"
#else
#include "FakeSemVar.hpp"
namespace scx {
typedef FakeSemVar SemVar;
}
#endif

namespace scx {

template <typename item_t>
class PVBuffer
{
public:
    PVBuffer():
        m_FreeListSemVar(0),
        m_DataListSemVar(0)
    {
    }

    ~PVBuffer()
    {
    }

    void AllocBuffer(size_t bufCount)
    {
        m_BufferQueue.resize(bufCount);

        m_FreeQueue.resize(bufCount);
        for (size_t i = 0; i < bufCount; ++i) {
            m_BufferQueue[i] = new item_t;
            m_FreeQueue[i] = m_BufferQueue[i];
            m_FreeListSemVar.Post(); 
        }

        m_DataListSemVar.Clear();
    }

    void ClearBuffer()
    {
        for (size_t i = 0; i < m_BufferQueue.size(); ++i) {
            delete m_BufferQueue[i];
        }
        m_BufferQueue.clear();

        m_FreeQueue.clear();
        m_DataQueue.clear();

        m_FreeListSemVar.Clear();
        m_DataListSemVar.Clear();
    }

    /**
     * This method should be called after both customer and producer
     * has been suspended by TakeFree()/TakeData().
     * After calling this method, 
     * the producer will begin to work again, then the customer.
     */
    void ResetPV()
    {
        const size_t bufCount = m_BufferQueue.size();

        // No mutex here, 
        // because we assume both thread has been suspended.
        m_DataQueue.clear();
        m_DataListSemVar.Clear();

        // Lock the FreeQueue first,
        // because after SemVar::Post() the producer will begin to work,
        // and it will take the first item in FreeQueue.
        //m_FreeListMutex.Lock();
        m_FreeQueue.resize(bufCount);
        m_FreeListSemVar.Clear();
        for (size_t i = 0; i < bufCount; ++i) {
            m_FreeQueue[i] = m_BufferQueue[i];
            m_FreeListSemVar.Post();
        }
        //m_FreeListMutex.Unlock();
    }

    size_t GetBufferCount() const
    {
        return m_BufferQueue.size();
    }

    size_t GetFreeCount() const
    {
        return m_FreeListSemVar.GetValue();
    }

    size_t GetDataCount() const
    {
        return m_DataListSemVar.GetValue();
    }

    /**
     * This method can be used for initialize buffer.
     */
    item_t* GetRawItem(size_t i)
    {
        return m_BufferQueue[i];
    }

    item_t* TakeFree()
    {
        m_FreeListSemVar.Wait(); 
        m_FreeListMutex.Lock();
        item_t* pItem = m_FreeQueue.front();
        m_FreeQueue.pop_front();
        m_FreeListMutex.Unlock();
        return pItem;
    }

    void RecycleFree(item_t* pItem)
    {
        m_DataListMutex.Lock();
        m_DataQueue.push_back(pItem);
        m_DataListMutex.Unlock();
        m_DataListSemVar.Post();
    }

    item_t* TakeData()
    {
        m_DataListSemVar.Wait(); 
        m_DataListMutex.Lock();
        item_t* pItem = m_DataQueue.front();
        m_DataQueue.pop_front();
        m_DataListMutex.Unlock();
        return pItem;
    }

    void RecycleData(item_t* pItem)
    {
        m_FreeListMutex.Lock();
        m_FreeQueue.push_back(pItem);
        m_FreeListMutex.Unlock();
        m_FreeListSemVar.Post();
    }

    /**
     * eg.
     * 1.Call ClearFree() in customer thread, then call ClearData() for customer itself.
     * Or Call ClearData() in producer thread, then call ClearFree() for producer it self.
     * 2.Finally, after prepared, we can call ResetPV() to wake the previous PV-loop again.
     */

    /**
     * Clear the empty-buffer, so that the producer can be blocked.
     */
    void ClearFree()
    {
        m_FreeListSemVar.Clear();
        m_FreeListMutex.Lock();
        m_FreeQueue.clear();
        m_FreeListMutex.Unlock();
    }

    /**
     * Clear the filled-data, so that the customer can be blocked.
     */
    void ClearData()
    {
        m_DataListSemVar.Clear();
        m_DataListMutex.Lock();
        m_DataQueue.clear();
        m_DataListMutex.Unlock();
    }

private:
    std::deque<item_t*> m_BufferQueue;

    std::deque<item_t*> m_FreeQueue;
    Mutex m_FreeListMutex;
    SemVar m_FreeListSemVar;

    std::deque<item_t*> m_DataQueue;
    Mutex m_DataListMutex;
    SemVar m_DataListSemVar;
};

}

#endif
