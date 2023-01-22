#pragma once

typedef void (*sanityF)();

typedef struct {
    void* handle;
    sanityF func;
} SOLink;

namespace SOOperations {

    SOLink so_fetch (char* function_id);
    void so_close (void* handle);

}

