/* This is under the GPL
 * Author : Chris Kuklewiz
 *
 * Purpose : To act as a string manager, designed for freeamp
 */

#include "charstore.h"

HashStore::HashStore() : hset(),
                         hmap(),
                         klist(NULL),
                         count(0),
                         emptycount(0),
                         empty(""),
                         lock(new Mutex()) 
{};

HashStore::~HashStore() {
    if (lock)
    {
        lock->Acquire();
        cerr << "\n~HashStore : locked" << endl;
    }
    this->print_stream(cerr);
    HSet::iterator itset(hset.begin());
    for(; hset.end()!=itset; ++itset)
    {
        cerr << '.';
        free_mem(*itset);
    }
    hset.clear();
    cerr << "\n~HashStore : hset gone" << endl;
    HMap::iterator itmap(hmap.begin());
    for(; hmap.end()!=itmap; ++itmap)
    {
        if (0 < itmap->second)
        {
            cerr << '.';
            free_mem(itmap->first);
        }
    }
    hmap.clear();
    cerr << "\n~HashStore : hmap gone" << endl;
    if (klist)
    {
        KList::iterator itlist(klist->begin());
        for(; klist->end()!=itlist; ++itlist)
        {
            cerr << '.';
            free_mem(*itlist);
        }
        klist->clear();
        delete klist;
        klist=NULL;
        cerr << "\n~HashStore : klist gone" << endl;
    }
    if (lock)
    {
        Mutex * temp=lock;
        lock=NULL;
        temp->Release();
        delete lock;
        cerr << "~HashStore : unlocked" << endl;
    }
};

const char * HashStore::insert_static (const char* s) {
    if (s)
    {
        AutoMutex acquire_(lock);
        ++count;
        if (0==strlen(s))
        {
            ++emptycount;
            return empty;
        }
        HSet::iterator itset(hset.find(s));
        if (hset.end()!=itset)
        {
            HMap::value_type value(*itset,0);
            toklist(*itset);
            hset.erase(itset);
            pair<HMap::iterator,bool> result(hmap.insert(value));
            if (!result.second)
            {
                cerr << "Error: hmap already had " << s << endl;
            }
            return (result.first)->first;
        } else {
            HMap::iterator itmap(hmap.find(s));
            if (hmap.end()!=itmap)
            {
                itmap->second=0;
                toklist(itmap->first);
                return itmap->first;
            }
            else
            {
                HMap::value_type value(s,0);
                pair<HMap::iterator,bool> result(hmap.insert(value));
                if (!result.second)
                {
                    cerr << "Error: hmap already had " << s << endl;
                }
                return (result.first)->first;
            }
        }
    }
    return NULL;
};

const char * HashStore::insert_dynamic(const char * s) {
    if (s)
    {
        AutoMutex acquire_(lock);
        ++count;
        if (0==strlen(s))
        {
            ++emptycount;
            free_mem(s);
            return empty;
        }
        HSet::iterator itset(hset.find(s));
        if (hset.end()!=itset)
        {
            HMap::value_type value(*itset,2);
            hset.erase(itset);
            pair<HMap::iterator,bool> result(hmap.insert(value));
            if (!result.second)
            {
                cerr << "Error: hmap already had " << s << endl;
            }
            free_mem(s);
            return (result.first)->first;
        } else {
            HMap::iterator itmap(hmap.find(s));
            if (hmap.end()!=itmap)
            {
                unsigned int& refcount(itmap->second);
                if (0<refcount)
                {
                    ++refcount;
                }
                free_mem(s);
                return itmap->first;
            }
            else
            {
                pair<HSet::iterator,bool> result(hset.insert(s));
                if (!result.second)
                {
                    cerr << "Error: hset already had " << s << endl;
                }
                return *(result.first);
            }
        }
    }
    return NULL;
};

const char * HashStore::insert_duplicate(const char * s) {
    // Just skip HSet. period.
    if (s)
    {
        AutoMutex acquire_(lock);
        ++count;
        if (0==strlen(s))
        {
            ++emptycount;
            return empty;
        }
        HSet::iterator itset(hset.find((char*)s));
        if (hset.end()!=itset)
        {
            /* Skip HSet, so fault */
            cerr << "Error: HSet should have been empty! ("
                 << *itset << "," << s << ")" << endl;
            s=NULL;
            cerr << *s;  // Force segfault
            /* end */
            HMap::value_type value(*itset,2);
            hset.erase(itset);
            pair<HMap::iterator,bool> result(hmap.insert(value));
            if (!result.second)
            {
                cerr << "Error: hmap already had " << s << endl;
            }
            return (result.first)->first;
        } else {
            HMap::iterator itmap(hmap.find((char*)s));
            if (hmap.end()!=itmap)
            {
                unsigned int& refcount(itmap->second);
                if (0<refcount)
                {
                    ++refcount;
                }
                return itmap->first;
            }
            else
            {
                int length = strlen(s);
                char *dup = allocate_mem(length+1);
                if (dup)
                {
                    dup=strncpy(dup,s,length+1);
                }
                if (dup)
                {
                    HMap::value_type value(dup,1);
                    pair<HMap::iterator,bool> result(hmap.insert(value));
                    if (!result.second)
                    {
                        cerr << "Error: hmap already had " << s << endl;
                    }
                    return (result.first)->first;
                    /* Skip HSet
                    pair<HSet::iterator,bool> result(hset.insert(dup));
                    if (!result.second)
                    {
                        cerr << "Error: hset already had " << s << endl;
                    }
                    return *(result.first);
                    */
                } else {
                    assert(dup);  // Error.
                }
            }
        }
    }
    return NULL;
}

void HashStore::ref(const char * s) {
    if (s)
    {
        AutoMutex acquire_(lock);
        if (0==strlen(s))
        {
            if (emptycount)
            {
                ++count;
                ++emptycount;
            }
            return;
        }
        HSet::iterator itset(hset.find(s));
        if (hset.end()!=itset)
        {
            /* Skip HSet, so fault */
            cerr << "Error: HSet should have been empty! ("
                 << *itset << "," << s << ")" << endl;
            s=NULL;
            cerr << *s;  // Force segfault
            /* end */
            ++count;
            HMap::value_type value(*itset,2);
            pair<HMap::iterator,bool> result(hmap.insert(value));
            if (!result.second)
            {
                cerr << "Error: hset and hmap both had " << s << endl;
            }
        } else {
            HMap::iterator itmap(hmap.find(s));
            if (hmap.end()!=itmap)
            {
                unsigned int& refcount(itmap->second);
                if (0<refcount)
                {
                    ++count;
                    ++refcount;
                }
            }
        }
    }
};

void HashStore::unref(const char * s) {
    if (s)
    {
        AutoMutex acquire_(lock);
        if (0==strlen(s))
        {
            if (emptycount)
            {
                --emptycount;
            }
            if (count)
            {
                --count;
            }
            return;
        }
        HSet::iterator itset(hset.find(s));
        if (hset.end()!=itset)
        {
            /* Skip HSet, so fault */
            cerr << "Error: HSet should have been empty! ("
                 << *itset << "," << s << ")" << endl;
            s=NULL;
            cerr << *s;  // Force segfault
            /* end */
            if (count)
            {
                --count;
            }
            const char * temp=*itset;
            hset.erase(itset);
            free_mem(temp);
        } else {
            HMap::iterator itmap(hmap.find(s));
            if (hmap.end()!=itmap)
            {
                if (count)
                {
                    --count;
                }
                unsigned int& refcount(itmap->second);
                if (1<refcount)
                {
                    --refcount;
                }
                else if (1==refcount)
                {
                    const char * temp=itmap->first;
                    hmap.erase(itmap);
                    free_mem(temp);
                }
            }
        }
    }
};

char* HashStore::allocate_mem(size_t length) const {
    // Add 1 for paranoia. Also calloc will set to zero, so the
    // string is more likely to terminate with a null if something
    // bad happens.
    char * newmem=(char*)calloc(length+1,sizeof(char));
    if (!newmem)
    {
        cerr << "Error: allocate_mem failed" << endl;
        assert(0);
    }
    return newmem;
};

void HashStore::free_mem(const char * s) const {
    if (s)
    {
        if (s!=empty)
        {
            free(const_cast<char*>(s));
        }
    }
};

void HashStore::toklist(const char* s) {
    if (s)
    {
        // Only call with lock acquired, so don't bother to acquire here.
        if (s==empty)
        {
            return;
        }
        if (!klist)
        {
            klist=new KList();
        }
        assert(klist);
        klist->push_back(s);
    }
};

void HashStore::set_entry(char * * dest, const char * src)
{
    if (dest)
    {
        AutoMutex acquire_(lock);
        if (*dest && (0 < strlen(*dest)))
        {
            unref(*dest);
            *dest=(char*)empty;
        }
        if (src && (0 < strlen(src)))
        {
            // Nested mutex acquisition...
            *dest = (char *)insert_duplicate(src);
        }
        else
        {
            ++count;
            ++emptycount;
        *dest=(char*)empty;
        }
    }
};

ostream& HashStore::print_stream(ostream& out)
{
    AutoMutex acquire_(lock);
    out << "HashStore report" << endl;
    out << "Logical Strings held: " << count << endl;
    out << "Empty String count: " << emptycount << endl;
    out << "Strings in HSet: " << hset.size() << endl;
    out << "Strings in HMap: " << hmap.size() << endl;
    if (klist)
    {
        out << "Strings marked in KList: " << klist->size() << endl;
    } else {
        out << "Strings marked in KList: " << 0 << endl;
    }
    return out;
}

ostream& operator<< (ostream& out,HashStore& store) {
    return store.print_stream(out);
}

//////////////////////////////////////////////////////////////////////

/*

SortedStore::SortedStore() : smap(),klist(NULL),count(0) {};

SortedStore::~SortedStore() {
    SMap::iterator itmap(smap.begin());
    for (; smap.end()!=itmap; ++itmap)
    {
        if (0 < itmap->second)
        {
            free_mem(itmap->first);
        }
    }
    if (klist)
    {
        KList::iterator itlist(klist->begin());
        for(; klist->end()!=itlist; ++itlist)
        {
            free_mem(*itlist);
        }
        delete klist;
        klist=NULL;
    }
};

char * SortedStore::insert_static (char* s) {
    if (s)
    {
        ++count;
        SMap::iterator itmap(smap.find(s));
        if (smap.end()!=itmap)
        {
            unsigned int& refcount(itmap->second);
            if (0 < refcount)
            {
                toklist(itmap->first);
                refcount=0;
            }
            return itmap->first;
        } else {
            SMap::value_type value(s,0);
            pair<SMap::iterator,bool> result(smap.insert(value));
            if (!result.second)
            {
                cerr << "Error: smap already had " << s << endl;
            }
            return (result.first)->first;
        }
    }
    return NULL;
};

char * SortedStore::insert_dynamic(char * s) {
    if (s)
    {
        ++count;
        SMap::iterator itmap(smap.find(s));
        if (smap.end()!=itmap)
        {
            free_mem(s);
            unsigned int& refcount(itmap->second);
            if (0 < refcount)
            {
                ++refcount;
            }
            return itmap->first;
        } else {
            SMap::value_type value(s,1);
            pair<SMap::iterator,bool> result(smap.insert(value));
            if (!result.second)
            {
                cerr << "Error: smap already had " << s;
            }
            return (result.first)->first;
        }
    }
    return NULL;
};

char * SortedStore::insert_duplicate(const char * s) {
    if (s)
    {
        ++count;
        SMap::iterator itmap(smap.find((char*)(s)));
        if (smap.end()!=itmap)
        {
            unsigned int& refcount(itmap->second);
            if (0 < refcount)
            {
                ++refcount;
            }
            return itmap->first;
        } else {
            char *dup=allocate_mem(strlen(s)+1);
            if (dup)
            {
                dup=strncpy(dup,s,strlen(s)+1);
            }
            if (dup)
            {
                SMap::value_type value(dup,1);
                pair<SMap::iterator,bool> result(smap.insert(value));
                if (!result.second)
                {
                    cerr << "Error: smap already had " << s << endl;
                }
                return (result.first)->first;
            } else {
                assert(dup); // Error
            }
        }
    }
    return NULL;
};

void SortedStore::ref(char * s) {
    if (s)
    {
        SMap::iterator itmap(smap.find(s));
        if (smap.end()!=itmap)
        {
            ++count;
            unsigned int& refcount(itmap->second);
            if (0 < refcount)
            {
                ++refcount;
            }
        }
    }
};

void SortedStore::unref(char * s) {
    if (s)
    {
        SMap::iterator itmap(smap.find(s));
        if (smap.end()!=itmap)
        {
            --count;
            unsigned int& refcount(itmap->second);
            if (1 < refcount)
            {
                --refcount;
            } 
            else if(1==refcount)
            {
                free_mem(itmap->first);
                smap.erase(itmap);
            }
        }
    }
};

char* SortedStore::allocate_mem(size_t length) const {
    char * newmem=(char *) calloc(length,sizeof(char));
    if (!newmem)
    {
        cerr << "Error: allocate_mem failed" << endl;
        assert(0);
    }
    return newmem;
};

void SortedStore::free_mem(char * s) const {
    free(s);
};

ostream& SortedStore::operator<< (ostream& out)
{
    out << "SortedStore report" << endl;
    out << "Logical Strings held: " << count << endl;
    out << "Strings in SMap: " << smap.size() << endl;
    if (klist)
        out << "Strings marked in KList: " << klist->size() << endl;
    return out;
};

void SortedStore::toklist(char* s)
{
    if (!klist)
    {
        klist=new KList();
    }
    klist->push_back(s);
};

*/
