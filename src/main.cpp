#include <App.h>
using namespace std;
using namespace aw;
int main(int argc, char **argv)
{
    try
    {
        APP.init(argc, argv);
        APP.loop();
    }
    catch (const exception &err)
    {
        printf("An exception occured: %s", err.what());
    }
}