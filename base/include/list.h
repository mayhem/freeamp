/*____________________________________________________________________________
	
	FreeAmp - The Free MP3 Player

	Portions Copyright (C) 1998 GoodNoise

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hoitem that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
	
	$Id: list.h,v 1.3 1999/03/07 08:37:51 elrod Exp $
____________________________________________________________________________*/

#ifndef _LIST_H_
#define _LIST_H_

#include <iostream.h>
#include <string.h>
#include <stdio.h>
#include "config.h"



template<class T>
class List {
 public:
    List(int32 th = 10); // set m_threshhold to its arg
    ~List();

    T FirstItem();
    T LastItem();

    T ItemAt(int32 index);
    int32 IndexOf(T &item);
    bool HasItem(T &item);
    bool IsEmpty();

    int32 CountItems();
    
    bool AddItem(T &item);
    bool AddItem(T &item, int32 index);

    bool AddList(List<T> &list);
    bool AddList(List<T> &list,int32 index);

    bool RemoveItem(T &item);
    bool DeleteItem(T &item);

    bool RemoveItems(int32 begin, int32 end);
    bool DeleteItems(int32 begin, int32 end);

    T RemoveItem(int32 index);
    bool DeleteItem(int32 index);

    bool RemoveAll();
    bool DeleteAll();
    
    T RandomItem();

    void Swap(int32 index1, int32 index2);
    
    void DoForEach(bool (*func)(T &));
    void DoForEach(bool (*func)(T &, void *), void *);

    T *Items() const { return m_pObjs; }

    // cmp returns true if first arg is 'greater' than the second ; 
    // sorts list smallest to largest according to cmp
    void SortItems(int32 (*cmp)(const T &, const T &)); 

 private:
    T *m_pObjs;  // indexer to array of objects
    int32 m_threshhold;
    int32 m_insertionPoint;
    int32 m_currentLength;
 
};

template<class T> 
List<T>::
List(int32 threshold) 
{
    m_threshhold = threshold;
    m_pObjs = new T[m_threshhold];

    for (int32 i=0;i<m_threshhold;i++) 
        m_pObjs[i] = NULL;

    m_insertionPoint = 0;
    m_currentLength = m_threshhold;
}

template<class T> 
List<T>::
~List() 
{
    delete [] m_pObjs;
}


template<class T> 
T 
List<T>::
FirstItem() 
{
    if(m_insertionPoint > 0) 
    {
	    return m_pObjs[0];
    } 
    else 
    {
	    return NULL;
    }
}

template<class T> 
T 
List<T>::
LastItem() 
{
    if(m_insertionPoint > 0) 
    {
	    return m_pObjs[m_insertionPoint - 1];
    } 
    else 
    {
	    return NULL;
    }
}

template<class T> 
T 
List<T>::
ItemAt(int32 index) 
{
    if((index >= m_insertionPoint) || (index < 0)) 
    {
	    return NULL;
    }

    return m_pObjs[index];
}

template<class T> 
int32 
List<T>::
IndexOf(T &mem) 
{
    int32 result = -1;

    for(int32 i=0;i<m_insertionPoint;i++) 
    {
	    if(m_pObjs[i] == mem) 
        {
	        result = i;
	        break;
	    }
    }

    return result;
}

template<class T> 
bool 
List<T>::
HasItem(T &item) 
{
    if(IndexOf(item) >= 0) 
    {
	    return true;
    } 
    else 
    {
	    return false;
    }
}

template<class T> 
bool 
List<T>::
IsEmpty() 
{
    return !m_insertionPoint;
}

template<class T> 
int32 
List<T>::
CountItems() 
{
    return m_insertionPoint;
}

template<class T> 
bool 
List<T>::
AddItem(T &item) 
{
    bool result = false;

    if(item) 
    {
	    if (m_insertionPoint == (m_currentLength-1)) 
        {
	        // add more and copy over
	        T *pNewObjs = new T[m_currentLength+m_threshhold];
	        memcpy(pNewObjs,m_pObjs,(sizeof (T))*m_currentLength);

	        delete [] m_pObjs;

	        m_pObjs = pNewObjs;

	        memset(&(m_pObjs[m_currentLength]),0,m_threshhold);
	        m_currentLength = m_currentLength + m_threshhold;
	    }

	    m_pObjs[m_insertionPoint] = item;
	    m_insertionPoint++;

	    result = true;
    } 
   
    return result;
}

template<class T> 
bool 
List<T>::
AddItem(T &item, int32 index) 
{
    bool result = false;

    if (item) 
    {
	    if ((index<=m_insertionPoint) && (index >= 0)) 
        {
	        if (m_insertionPoint == (m_currentLength-1)) 
            {
		        T *pNewObjs = new T[m_currentLength+m_threshhold];

		        memcpy(pNewObjs,m_pObjs,(sizeof (T))*index);
		        pNewObjs[index] = item;

		        if (index < m_insertionPoint) 
                {
		            memcpy(&(pNewObjs[index+1]), &(m_pObjs[index]),(sizeof (T))*(m_insertionPoint-index));
		        }

		        delete [] m_pObjs;

		        m_pObjs = pNewObjs;
		        memset(&(m_pObjs[m_insertionPoint+1]),0,m_insertionPoint + m_threshhold - 2);
		        m_currentLength += m_threshhold;
	        } 
            else 
            {
		        memmove(&(m_pObjs[index+1]),&(m_pObjs[index]), (m_insertionPoint - index) * sizeof(T));
		        m_pObjs[index] = item;
	        }

	        m_insertionPoint++;
	        result = true;
	    }
    }

    return result;
}

// FIXME: how to back out if one of the Adds fails?
template<class T> 
bool 
List<T>::
AddList(List<T> &list) 
{
    bool result = true;

    for(int32 i = 0; i < list.CountItems(); i++) 
    {
	    if (!AddItem(list.ItemAt(i))) 
        {
	        result = false;
	        break;
	    }
    }

    return result;
}

// FIXME: how to back out if one of the Adds fails?
template<class T> 
bool 
List<T>::
AddList(List<T> &list,int32 index) 
{
    bool result = true;

    for(int32 i = 0; i < list.CountItems(); i++) 
    {
        T foo = list.ItemAt(i);

	    if (!AddItem(foo, index + i)) 
        {
	        result = false;
	        break;
	    }
    }

    return result;
}

template<class T> 
bool 
List<T>::
RemoveItem(T &item) 
{
    bool result = false;

    int32 index = IndexOf(item);

    if (index >= 0) 
    {
	    RemoveItem(index);
	    result = true;
    }

    return result;
}

template<class T> 
bool 
List<T>::
DeleteItem(T &item) 
{
    bool result = false;

    int32 index = IndexOf(item);

    if (index >= 0) 
    {
	    DeleteItem(index);
	    result = true;
    }

    return result;
}

template<class T> 
bool List<T>::
RemoveItems(int32 begin, int32 end) 
{
    bool result = false;

    if (!((begin >= m_insertionPoint)   || 
        (begin < 0) || (end > begin)    || 
        (end >= m_insertionPoint))) 
    {
	    memmove(&(m_pObjs[begin]),&(m_pObjs[end+1]),sizeof(T)*(m_insertionPoint-end-1));
	    m_insertionPoint -= end-begin+1;
	    result = true;
    }

    return result;
}

template<class T> 
bool 
List<T>::
DeleteItems(int32 begin, int32 end) 
{
    bool result = false;

    if (!((begin >= m_insertionPoint)   || 
        (begin < 0)                     || 
        (end > begin)                   || 
        (end >= m_insertionPoint))) 
    {
	    for(int32 i = begin; i <= end; i++) 
        {
	        delete m_pObjs[i];
	    }

	    result = RemoveItems(begin, end);
    }
    return result;
}

template<class T> 
T 
List<T>::
RemoveItem(int32 index) 
{
    if ((index >= m_insertionPoint) || (index < 0)) 
    {
	    return NULL;
    }

    T resultval = m_pObjs[index];

    if(index == m_insertionPoint - 1) // if it is the last one just NULL it
    {
        m_pObjs[index] = 0x00;
    }
    else // shift the other ones up 
    {
        memmove(&(m_pObjs[index]),&(m_pObjs[index+1]),sizeof(T)*(m_insertionPoint-index-1));
    }
   
    m_insertionPoint--;

    return resultval;
}

template<class T> 
bool 
List<T>::
DeleteItem(int32 index) 
{
    T p = RemoveItem(index);

    if (p) 
    {
	    delete p;
	    return true;
    } 
    else 
    {
	    return false;
    }
}

template<class T> 
bool 
List<T>::
RemoveAll() 
{
    for (int32 i = 0; i < m_insertionPoint; i++) 
        m_pObjs[i] = NULL;

    m_insertionPoint = 0;

    return true;
}

template<class T> 
bool 
List<T>::
DeleteAll() 
{
    for(int32 i = 0; i < m_insertionPoint; i++) 
    {
	    delete m_pObjs[i];
	    m_pObjs[i] = NULL;
    }

    m_insertionPoint = 0;

    return true;
}

template<class T> 
T 
List<T>::
RandomItem() 
{
    srand((unsigned int) time (NULL));
    int32 foo = (int32) (((double)m_insertionPoint * rand()) / (RAND_MAX+1.0));
    return m_pObjs[foo];
}

template<class T> 
void 
List<T>::
Swap(int32 s1, int32 s2) 
{
    if ((s1 < 0)                ||
	(s2 < 0)                    ||
	(s1 >= m_insertionPoint)    ||
	(s2 >= m_insertionPoint)    ||
	(s1 == s2)) 
    {
	    return;
    }

    T tmp = m_pObjs[s1];
    m_pObjs[s1] = m_pObjs[s2];
    m_pObjs[s2] = tmp;
}

template<class T> 
void 
List<T>::
DoForEach(bool (*func)(T &)) 
{
    for(int i=0;i<m_insertionPoint;i++) 
    {
	    *func(m_pObjs[i]);
    }
}

template<class T> 
void 
List<T>::
DoForEach(bool (*func)(T &, void *), void *arg) 
{
    for(int i=0;i<m_insertionPoint;i++) 
    {
	    *func(m_pObjs[i],arg);
    }
}

// FIXME: just a bubble sort for now
template<class T> 
void 
List<T>::
SortItems(int (*cmp)(const T &, const T &)) 
{
    for(int end = m_insertionPoint-2;i>= 0;end--) 
    {
	    for(int i=0;i<end;i++) 
        {
	        if (*cmp(m_pObjs[i],m_pObjs[i+1])) 
            {
		        Swap(i,i+1);
	        }
	    }
    }
}



#endif // _LIST_H_
