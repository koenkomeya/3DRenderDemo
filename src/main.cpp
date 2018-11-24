/**
 * @file main.cpp
 * This simply calls the main function of the target.
 * Temporary workaround for a CMake quirk.
 *
 * @date November 17, 2018 22:32
 * @author Koen Komeya 
 */

#include "k.hpp"
#include <stdexcept>
#include <cstdio>

#ifdef TARGET_SERVER
int main_server(int argc, char **argv);

int main(int argc, char **argv) {
    return main_server(argc,argv);
}
#else
int main_client(int argc, char **argv);

int main(int argc, char **argv) {
#ifdef TARGET_DEBUG
    try{
#endif
        return main_client(argc,argv);

#ifdef TARGET_DEBUG
    } catch (std::exception &ex){
        std::puts(ex.what());
    }
#endif
}
#endif

