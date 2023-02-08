#include <string>
#include <map>
#include <string>
#include <skellyapi.h>

// function pointer for the skelly application - to be updated
typedef void (*funcPtr)();

namespace DLApi {

    // return construct with the pointer to lib and dictionary of fetched functions
    //template <typename create_T, typename destroy_T> 
    struct DLLink{
        void* _dl_ptr;
        std::map<std::string, funcPtr> _dl_func_map;
        std::map<std::string, Skelly::create_t*> _dl_class_creators;
        std::map<std::string, Skelly::destroy_t*> _dl_class_destructors;
    };

    DLLink dl_open (std::string lib_path);
    bool dl_fetch (DLLink& dl_object, std::string function_id);
    bool dl_class_fetch(DLLink& dl_object, std::string class_id);
    void dl_close (DLLink& dl_object);

}

