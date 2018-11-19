/**
 * @file emscripten.cpp
 * @brief "OS-specific" stuff for Emscripten
 *
 * This handles windowing-related things for Emscripten.
 * Since Emscripten simulates windowing within a web environment,
 * this does likewise.
 *
 * @date Nov 17, 2018 15:27
 * @author Koen Komeya
 */

#include "k.hpp"
#ifdef TARGET_ATTR_TOOL_EM
#include <emscripten.h>
#include "../../gwindow.hpp"
#include "generic/client/window/base/base_req.hpp"

const char *safeToClose   = "window.onbeforeunload = function(e){return \"Game is presently running!\";}";
const char *unsafeToClose = "window.onbeforeunload = null;}";

namespace kGenWindow{
    void initModule(){
        kGenWinOSBase::osSafeToClose(false);
        kGenWinOSBase::initSubmodule();
    }
}

namespace kGenWinOSBase{
    void osSafeToClose(bool safe){
        if (safe){
            emscripten_run_script(safeToClose);
        } else {
            emscripten_run_script(unsafeToClose);
        }
    }
}


#endif
