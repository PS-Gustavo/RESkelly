#pragma once

namespace Skelly {

    class SkellyApi {
    public:
        SkellyApi();
        virtual ~SkellyApi();
        virtual void print();
    };

    // Class factory types

    typedef SkellyApi* create_t();
    typedef void destroy_t (SkellyApi*);
}
