#ifndef __CHARSTORE_H_
#define __CHARSTORE_H_

/* This is under the GPL
 * Author : Chris Kuklewiz
 *
 * Purpose : To act as a string manager, designed for freeamp
 */

#include <stdlib.h>  // calloc, free
#include <string.h>  // of course
#include <iostream>  // cerr
#include <hash_set>  // HashStore
#include <hash_map>  // HashStore
#include <list>      // HashStore and SortedStore
#include <map>       // SortedStore

#include "mutex.h"
#include "automutex.h"

/**
 * The abstract API that will be used.  Passing null for "char * s" is
 * always ignored.
 */
class AbstractStore {
public:
    // As a further optimization, the empty string is held separately.
    virtual const char * get_empty();
    // This was added to wrap insert_duplicate, returning the value in
    // dest.  The previous value in dest is unreferenced.
    virtual void set_entry(const char * & dest, const char * src);
    // Assumes s points to a string that will never be altered or
    // deallocated.  If there is a duplicate then ignore s and return
    // a pointer to the duplicate. If the duplicate is dynamic, it
    // will still be deallocated when the store is destroyed.
    // refcount set to zero.
    virtual const char * insert_static (const char* s)=0;
    // Assumes s is a dynamically allocated pointer. It will be
    // de-allocated via the virtual free_mem member function.  If
    // there is a duplicate then free s now and return a pointer to
    // the duplicate and ++refcount. Else store s with refcount set to
    // one and return s.
    virtual const char * insert_dynamic(const char * s)=0;
    // If there is a duplicate then return the existing pointer and
    // ++refcount. Else the string pointed to by s will be copied into
    // newly allocated memory (using the virtual allocate_mem
    // function) and return the new pointer (with refcount set to
    // one).
    virtual const char * insert_duplicate(const char * s)=0;
    // If s is in the store, ++refcount
    virtual void ref(const char * s)=0;
    // If s is in the store, --refcount, if now zero then free it
    virtual void unref(const char * s)=0;
    // Allocate length bytes and return the pointer or Null on failure.
    virtual char* allocate_mem(size_t length) const=0;
    // Deallocate s.
    virtual void free_mem(const char * s) const=0;
};

/**
 * Some binary predicates that we need
 */
struct EqualString
{
  bool operator()(const char* s1,const  char* s2) const
  {
    return strcmp(s1, s2) == 0;
  }
};

/**
 * LessString compares case insensitive, and if equal, then takes
 * case into account.
 */
struct LessString
{
    bool operator()(const char* s1, const char* s2) const
    {
        int comp(strcasecmp(s1,s2));
        if (0!=comp)
        {
            return comp < 0;
        } else {
            return strcmp(s1, s2) < 0;
        }
    }
};

/**
 * The Hash store uses some hash sets and maps to hold the strings.
 * It is a tad complex, but strings with refcount 1 are held more
 * efficiently.  To allow for adding static strings, a list of
 * dynamic strings with refcount zero is kept in klist so they can
 * be freed when the HashStore is destroyed.  Now thread safe
 * with Mutex and AutoMutex.  To be able to free the memory, it
 * is stored internally as 
 */

class HashStore {
protected:
    typedef hash_set<const char *, hash<const char *>, EqualString> HSet;
    typedef hash_map<const char *, unsigned int, hash<const char*>, EqualString> HMap;
    typedef list<const char*> KList;
    HSet hset;
    HMap hmap;
    KList *klist;
    unsigned int count,emptycount;
    const char empty[1];
    Mutex *lock;
public:
    explicit HashStore();
    virtual ~HashStore();
    virtual const char * get_empty() { return empty; };
    virtual void set_entry(char * * dest, const char * src);
    virtual const char * insert_static (const char* s);
    virtual const char * insert_dynamic(const char * s);
    virtual const char * insert_duplicate(const char * s);
    virtual void ref(const char * s);
    virtual void unref(const char * s);
    virtual char* allocate_mem(size_t length) const;
    virtual void free_mem(const char * s) const;
    ostream& print_stream(ostream& out);
    friend ostream& operator<< (ostream& out,HashStore& store);
protected:
    void toklist(const char* s);
private:
    explicit HashStore(const HashStore& other) {};
    HashStore& operator=(const HashStore& other) { return *this; };
};

/*
 *  SortedStore is based on an older version.  It needs a little work
 *  before use to make it as good as HashStore.
 */
/*
class SortedStore : public AbstractStore {
public:
    typedef map<char *,unsigned int, LessString> SMap;
protected:
    typedef list<char*> KList;
    SMap smap;
    KList *klist;
    unsigned int count;
public:
    explicit SortedStore();

    virtual ~SortedStore();
    virtual char * insert_static (char* s);
    virtual char * insert_dynamic(char * s);
    virtual char * insert_duplicate(const char * s);
    virtual void ref(char * s);
    virtual void unref(char * s);
    virtual char* allocate_mem(size_t length) const;
    virtual void free_mem(char * s) const;
    SMap::const_iterator begin() const {
        return smap.begin();
    };

    SMap::const_iterator end() const {
        return smap.end();
    };

    ostream& operator<< (ostream& out);
protected:
    void toklist(char* s);
private:
    explicit SortedStore(const SortedStore& other) {};
    SortedStore& operator=(const SortedStore& other) { return *this; };
};

*/
#endif
