#include <App.h>
using namespace std;
using namespace aw;
int main()
{
    try
    {
        if (APP.init())
            APP.loop();
        return 0;
    }
    catch (const exception &err)
    {
        printf("An exception occured: %s", err.what());
    }
}