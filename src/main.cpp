#include <App.h>
using namespace std;
int main(int argc, char **argv)
{
    try
    {
        APP.init(argc, argv);
        APP.loop();
        APP.terminate();
    }
    catch (exception e)
    {
        printf("An exception occured %s", e.what());
    }
}