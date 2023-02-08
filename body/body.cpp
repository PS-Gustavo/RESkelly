#include <body.h>

int main() {

    // create Skelly dynamic library
    DLApi::DLLink skelly_dl = DLApi::dl_open("./output/skelly.so");
    // if success, fetch Skelly class declaration and validate
    if ((!sizeof(skelly_dl)) || (!DLApi::dl_class_fetch(skelly_dl, "skelly"))) {
        return -1;
    }

    //Create Skelly instance
    Skelly::SkellyApi* skelly_api = skelly_dl._dl_class_creators["skelly"]();
    
    skelly_api->print();

    // fetch standalone function and validate
    if (!DLApi::dl_fetch(skelly_dl, "test")) {
        return -1;
    }

    skelly_dl._dl_func_map["test"]();

    // destroy Skelly instance
    skelly_dl._dl_class_destructors["skelly"](skelly_api);
    // close dynamic library link
    DLApi::dl_close(skelly_dl);

    return 0;
}