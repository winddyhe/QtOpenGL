/*
 filename: debugnew.cpp
 This is used to substitute a version of the new operator that
 can be used for debugging memory leaks. In any (all?) code
 files #include debugnew.h. Add debugnew.cpp to the project.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <malloc.h>
#include <map>
using namespace std;
// This disables macro expansion of "new".
// This statement should only appear in this file.
#define DEBUGNEW_CPP
#include "dbg.h"
DebugNewTracer::DebugNewTracer () : _lockCount (0)
{
    // Once this object is constructed all calls to
    // new should be traced.
    Ready = true;
    _totalsize = 0;
#if defined(LOG_FILE)
    if( (_logfp=fopen(LOG_FILE_NAME,"wt")) == NULL )
    {
        printf(" Error! file: debugnew.log can not open@!\n");
        return;
    }
    fprintf(_logfp,"new, delete list:\n");
    fflush(_logfp);
#endif

}

void DebugNewTracer::Add (void* p, const char* file, int line)
{
    // Tracing must not be done a second time
    // while it is already
    // in the middle of executing
    if (_lockCount > 0)
        return;
    // Tracing must be disabled while the map
    // is in use in case it calls new.
    DebugNewTracer::Lock lock (*this);
    _map [p] = Entry (file, line);
}
void DebugNewTracer::Add (void* p, const char* file, int line, size_t size)
{
    // Tracing must not be done a second time
    // while it is already
    // in the middle of executing
    if (_lockCount > 0)
        return;
    // Tracing must be disabled while the map
    // is in use in case it calls new.
    DebugNewTracer::Lock lock (*this);
#if 1
    file = strrchr(file,'\\')== NULL?file:strrchr(file,'\\')+1;
#endif
    _map [p] = Entry (file, line, size);
    _totalsize += size;
#if defined(LOG_FILE)
    fprintf(_logfp,"*N p = 0x%08x, size = %6d,  %-22s, Line: %4d.  totalsize =%8d\n", p, size, file, line, _totalsize);
    fflush(_logfp);
#endif
}

void DebugNewTracer::Remove (void* p)
{
    // Tracing must not be done a second time
    // while it is already
    // in the middle of executing
    if (_lockCount > 0)
        return;
    // Tracing must be disabled while the map
    // is in use in case it calls new.
    DebugNewTracer::Lock lock (*this);
    iterator it = _map.find (p);
    if (it != _map.end ())
    {
        size_t size = (*it).second.Size();
        _totalsize -= size;
#if defined(LOG_FILE)
        fprintf(_logfp,"#D p = 0x%08x, size = %6u.%39stotalsize =%8d\n", p, size, "-----------------------------------  ", _totalsize );
        fflush(_logfp);
#endif
        _map.erase (it);
    }
    else
    {
#if defined(LOG_FILE)
        fprintf(_logfp,"#D p = 0x%08x. error point!!!\n", p );
        fflush(_logfp);
#endif
    }
}
DebugNewTracer::~DebugNewTracer ()
{
    // Trace must not be called if Dump indirectly
    // invokes new, so it must be disabled before
    // Dump is called. After this destructor executes
    // any other global objects that get destructed
    // should not do any tracing.
    Ready = false;
    Dump ();
#if defined(LOG_FILE)
    fclose(_logfp);
#endif
}
// If some global object is destructed after DebugNewTracer
// and if that object calls new, it should not trace that
// call to new.
void DebugNewTracer::Dump ()
{
    if (_map.size () != 0)
    {
        std::cout << _map.size () << " memory leaks detected\n";
#if defined(LOG_FILE)
        fprintf(_logfp, "\n\n***%d memory leaks detected\n", _map.size ());
        fflush(_logfp);
#endif
        for (iterator it = _map.begin (); it != _map.end (); ++it)
        {
            char const * file = it->second.File ();
            int line = it->second.Line ();
            int size = it->second.Size ();
            std::cout << file << ", "  << line << std::endl;
#if defined(LOG_FILE)
            fprintf(_logfp,"%s, %d, size=%d\n", file, line, size);
            fflush(_logfp);
#endif
        }
    }
    else
    {
        std::cout << "no leaks detected\n";
#if defined(LOG_FILE)
        fprintf(_logfp,"no leaks detected\n");
        fflush(_logfp);
#endif
    }
}
// If some global object is constructed before DebugNewTracer
// and if that object calls new, it should not trace that
// call to new.
bool DebugNewTracer::Ready = false;
void* operator new (size_t size, const char* file, int line)
{
    void * p = malloc (size);
    if (DebugNewTracer::Ready)
        DebugNewTrace.Add (p, file, line, size);
    return p;
}
void operator delete (void* p, const char* file, int line)
{
    file = 0; // avoid a warning about argument not used in function
    line = 0; // avoid a warning about argument not used in function

    if (DebugNewTracer::Ready)
        DebugNewTrace.Remove (p);
    free (p);
}

void* operator new [] (size_t size, const char*  file, int line)
{
    void * p = malloc (size);
    if (DebugNewTracer::Ready)
        DebugNewTrace.Add (p, file, line, size);
    return p;
}
void operator delete [] (void* p, const char* file, int line)
{
    file = 0; // avoid a warning about argument not used in function
    line = 0; // avoid a warning about argument not used in function

    if (DebugNewTracer::Ready)
        DebugNewTrace.Remove (p);
    free (p);
}

void* operator new (size_t size)
{
    void * p = malloc (size);
    // When uncommented these lines cause entries in the map for calls to new
    // that were not altered to the debugnew version. These are likely calls
    // in library functions and the presence in the dump of these entries
    // is usually misleading.
    // if (DebugNewTracer::Ready)
    //   DebugNewTrace.Add (p, "?", 0);
    return p;
}

void operator delete (void* p)
{
    if (DebugNewTracer::Ready)
        DebugNewTrace.Remove (p);
    free (p);
}
//add by yugang
void operator delete [] (void* p)
{
    if (DebugNewTracer::Ready)
        DebugNewTrace.Remove (p);
    free (p);
}
