
#pragma once

#include <functional>

class InputTester
{
public:
    template<typename F, typename...Args>
    static void doTest(F&& f, Args && ...args){
        f(std::forward<Args>(args)...);
    }
};
