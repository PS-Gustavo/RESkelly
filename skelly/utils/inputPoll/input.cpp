
/****************************************************************************************
 * 
 * Lacrimal
 * Input Polling Module
 * 
 ****************************************************************************************
 * 
 * Changelog:
 * 
 * - 0.1.0: Initial implementation; Key and Mouse polling. Agnostic interface and OpenGL.
 * 
 **************************************************************************************** 
 * 
 * Description:
 * 
 * Input module allows polling whether input events are triggered or not;
 * Currently events supported are keyboard and mouse input events
 * 
 ***************************************************************************************/

#include <input.h>
#include <opengl.h>

namespace skelly {

    APITarget Input::_s_targetAPI = APITarget::OpenGL;

    Input* Input::create() {
        switch (Input::getTargetAPI()) {
            case APITarget::OpenGL:
                return new OpenGLInput();
            default:
                SKELLY_ASSERT(false, "Input::create: No Rendering API Found!");
                return nullptr;
        }

        SKELLY_ASSERT(false, "Input::create: unknown behavior.");
    }    

    

}