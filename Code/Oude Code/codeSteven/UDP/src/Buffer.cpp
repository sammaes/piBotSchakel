#include "Buffer.h"

using namespace std;
struct Package;
struct Udp_package;
struct Udp_header;
struct Info;

Package Buffer::package;

void Buffer::set_package(Udp_package udp_package, int nr){
    if (udp_package.info_b.robotx == -1){
        return;
    }
    package.nr = nr;
    package.udp_package=&udp_package;
}
Package Buffer::get_package(){
    return package;
}

