#include <iostream>
#include <cstdlib>

#include "system/system.hpp"

int main(int argc, char* argv[]) {
    System sys; // criando objeto que controla o sistema

    //

    sys.Initialize();
    sys.Run();
    sys.Shutdown();

    return EXIT_SUCCESS;
}
