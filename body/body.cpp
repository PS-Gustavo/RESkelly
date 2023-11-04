#include <body.h>

#ifdef TEST_ENABLED
    #include <functionalTest.h>
#endif

int main() {
    try {           
        /**
         * Functional test regression suit.
         * This can be removed if no regression is necessary for your project.
        */        
        #ifdef TEST_ENABLED
            std::pair<bool, std::string> testOutput;
            testOutput = test::functionalRegression();
            (testOutput.first) ?
                std::cout << "Test regression successful.\n" :
                std::cout << testOutput.second << "\n";
            return testOutput.first;
        #endif

        body::Body app("body");
        app.run();
    }
    catch(const std::exception& e) {
        std::clog << e.what() << '\n';
        return -1;
    }
        
    return 0;
}