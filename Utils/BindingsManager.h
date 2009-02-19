#ifndef _BINDINGS_MANAGER_H_
#define _BINDINGS_MANAGER_H_

#include <Logging/Logger.h>
#include <typeinfo>
#include <string>
#include <map>

namespace OpenEngine {
namespace Utils {

using namespace std;

class BindingsManager {
private:
    map<string, pair<string, void* > > pointers;
    map<string, string> metaInfo;
public:

    BindingsManager() {}
    template <typename T> void SetPointer(T* p, string key) {
        pointers[key] = make_pair( typeid(T).name(), (void*)p);
    }

    template <typename T> T* GetPointer(string key) {
        if (pointers.find(key) == pointers.end())
            throw string("not found");
        pair<string, void* > p = pointers[key];
        if (typeid(T).name() != p.first) 
            throw string("wrong type");

        return (T*)(p.second);
    }

    void PrintInfo() {
        for(map<string, pair<string, void* > >::iterator itr = pointers.begin();
            itr != pointers.end();
            itr++) {
            
            logger.info << (*itr).first << " is a: "
                        << (*itr).second.first
                        << logger.end;
                }
    }
    
    string TypeFor(string key) {
        return pointers[key].first;
    }

    string MetaFor(string key) {
        return metaInfo[key];
    }

    void SetMetaFor(string key, string meta) {
        metaInfo[key] = meta;
    }

};



}
}


#endif
