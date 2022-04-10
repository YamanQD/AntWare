#include <App.h>
using namespace std;
using namespace aw;
int main(int argc, char **argv)
{
    try
    {
        if (APP.init(argc, argv))
            //APP.loop();
            return 0;
    }
    catch (const exception &err)
    {
        printf("An exception occured: %s", err.what());
    }
}