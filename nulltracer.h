#ifndef __TRACER_H_
#define __TRACER_H_

#include <iostream>

inline void _real_assert(bool b,const char *file,int line,
                         const char *func, const char *msg) 
{
    if (!b) {
	cerr << endl << "! " << msg << " failed : " << file 
             << " : " << line << " : " << func << endl;
	exit(1);
    }
}

inline void _real_message(const char *file,int line,
                          const char *func, const char *msg) 
{
    cerr << "$ Message : " << file << " : "
         << line << " : " << func << " : " << msg << endl;
}

// Macros to help debug that call the above functions

#define _must_assert(__f__) _real_assert((__f__),__FILE__,__LINE__, \
 __PRETTY_FUNCTION__,"_assert " #__f__)

#define _assert(__f__) {};

#define _nullChk(__p__) _real_assert(NULL!=(__p__),__FILE__,__LINE__, \
 __PRETTY_FUNCTION__,"_nullChk " #__p__)

#define _messsage(__m__) {};

#define _never_get_here _real_assert(false,__FILE__,__LINE__, \
 __PRETTY_FUNCTION__,"_never_get_here")

// Execution tracing macros for debugging
#define _you_are_here {}

#define _show_args0() {}

#define _show_args1(Arg1) {}

#define _show_args2(Arg1,Arg2) {}

#define _show_args3(Arg1,Arg2,Arg3) {}

#define _show_args4(Arg1,Arg2,Arg3,Arg4) {}

#define _show_args5(Arg1,Arg2,Arg3,Arg4,Arg5) {}

/*
Chris Kuklewicz's Log (initials CEK)

When removing alot from playlist, see occasional segfault
*/


#endif
