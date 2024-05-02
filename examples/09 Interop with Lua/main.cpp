#include "lua_bridge.hpp"

using namespace pkpy;

Str read_stdin(){
    SStream ss; char ch;
    while(std::cin.get(ch)) ss << ch;
    return ss.str();
}

int main(){
    VM* vm = new VM();

    // create lua state
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // initialize lua bridge
    initialize_lua_bridge(vm, L);

    vm->exec(read_stdin());
    
    delete vm;
    return 0;
}
