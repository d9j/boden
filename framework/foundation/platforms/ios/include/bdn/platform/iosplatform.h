#pragma once

#include <bdn/platform/Hooks.h>

namespace bdn
{
    namespace platform
    {
        class IOSHooks : public Hooks
        {
          public:
            static void init();

          public:
            void debuggerPrint(const std::string &text) override;
            bool debuggerPrintGoesToStdErr() override;
        };
    }
}
