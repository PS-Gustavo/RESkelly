/**
 * Dynamic Library API
 **
 * Script addapted off of Ted Lyngmo's stackoverflow contribution @
 * https://stackoverflow.com/questions/56932785/automatically-creating-wrappers-for-classes-loaded-with-dlopen
 * 
*/

#pragma once

using dynlib_error = std::runtime_error;

namespace dlapi {

    class DLLink {
        public:
            DLLink(const char* filename);
            DLLink(const DLLink&) = delete;
            DLLink(DLLink&&);
            DLLink& operator=(const DLLink&) = delete;
            DLLink& operator=(DLLink&&);
            virtual ~DLLink();

        protected:
            template<typename T>
            T load(const char* symbol) const {
                static_cast<void>(dlerror());
                return reinterpret_cast<T>(dlsym(m_handle,symbol));
            }

        private:
            void* m_handle;
    };
}

