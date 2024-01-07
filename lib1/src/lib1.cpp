#include "MyProject/lib1/lib1.h"

#include <iostream>
#include "lib1_private.h"

namespace MyProject {
namespace lib1 {

Interface::Interface() : m_impl{ new InterfaceImpl{} } {}
Interface::~Interface() { delete m_impl; }

int Interface::getTruth() {
    return m_impl->calculateAnswer();
}

} // namespace lib    
} // namespace MyProject
