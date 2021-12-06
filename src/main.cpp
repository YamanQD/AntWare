#include <App.h>
int main(int argc, char **argv)
{
    APP.init(argc, argv);
    APP.loop();
    APP.terminate();
}