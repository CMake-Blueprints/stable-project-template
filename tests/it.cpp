#include <cassert> 
#include "MyProject/lib1/lib1.h"
#include "MyProject/lib2/lib2.h"

int main() {
    MyProject::lib1::Interface interface;
    assert(interface.getTruth() == 42);
    assert(MyProject::lib2::halfTruth() == 21);
    return 0;
}
