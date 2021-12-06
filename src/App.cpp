#include<App.h>
using namespace aw;
App::App(){}
App& App::instance(){
    static App app;
    return app;
}
void App::init(int argc, char **argv){

}
void App::terminate(){

}
void App::loop(){

}