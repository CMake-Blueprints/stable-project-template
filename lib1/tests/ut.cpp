#include <cassert>
#include "MyProject/lib1/lib1.h"
#include "lib1_private.h"

int main() {
    MyProject::lib1::Interface interface;
    assert(interface.getTruth() == 42);
    MyProject::lib1::InterfaceImpl impl;
    assert(impl.calculateAnswer() == 42);
    return 0;
}
