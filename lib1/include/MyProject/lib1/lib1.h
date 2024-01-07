#pragma once

#include "lib1_export.h"

namespace MyProject {
namespace lib1 {

class InterfaceImpl;

class LIB1_EXPORT Interface {
public:
    Interface();
    virtual ~Interface();
    int getTruth();

private:
    InterfaceImpl* m_impl;
};

} // namespace lib    
} // namespace MyProject
