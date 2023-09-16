#include <functionalTest.h>

namespace test {

    void addFault(std::pair<bool, std::string>& regressionResult, const std::exception& e) {
        regressionResult.first = false;
        regressionResult.second += e.what();
        regressionResult.second += "\n";
    }

    std::pair<bool,std::string> functionalRegression() {
        std::pair<bool, std::string> regressionResult(true, "");
        

/**
 * Test 1 - Hello Triangle
 * 
 * This test sets up all base structures of Skelly and renders a basic triangle shape.
 * This is considered the basic Sanity test.
*/
        try {
            Test app("helloTriangle");
            test::HelloTriangle test;
            test.setup(app.getApplication());
            app.run();
        }
        catch(const std::exception& e) {
            addFault(regressionResult, e);
        }
        
        return regressionResult;
    }

}