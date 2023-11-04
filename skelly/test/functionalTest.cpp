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
            Test appHelloTriangle("helloTriangle");
            test::HelloTriangle testHelloTriangle;
            testHelloTriangle.setup(appHelloTriangle.getApplication());
            appHelloTriangle.testRun();

        }
        catch(const std::exception& e) {
            addFault(regressionResult, e);
        }
        

/**
 * Test 2 - Camera Test
 * 
 * Creates a camera matrix and modifies the HelloTriangle shape.
 * 
*/
        try {
            Test appTestCamera("testCamera");
            test::TestCamera testCamera;
            testCamera.setup(appTestCamera.getApplication());
            appTestCamera.testRun();
        }
        catch(const std::exception& e) {
            addFault(regressionResult, e);
        }

        return regressionResult;
    }

}