/**
 * Dynamic Library API
 **
 * Script addapted off of Ted Lyngmo's stackoverflow contribution @
 * https://stackoverflow.com/questions/56932785/automatically-creating-wrappers-for-classes-loaded-with-dlopen
 * 
*/

#pragma once

#include <string>
#include <map>
#include <iostream>
#include <dlfcn.h>
#include <stdexcept>
#include <utility>

using dynlib_error = std::runtime_error;

namespace dl_api {

    class dllink {
        public:
            dllink(const char* filename);
            dllink(const dllink&) = delete;
            dllink(dllink&&);
            dllink& operator=(const dllink&) = delete;
            dllink& operator=(dllink&&);
            virtual ~dllink();

        protected:
            template<typename T>
            T load(const char* symbol) const {
                static_cast<void>(dlerror());
                return reinterpret_cast<T>(dlsym(handle,symbol));
            }

        private:
            void* handle;
    };
}

