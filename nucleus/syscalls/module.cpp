/**
 * (c) 2014 Nucleus project. All rights reserved.
 * Released under GPL v2 license. Read LICENSE for more details.
 */

#include "module.h"
#include "nucleus/emulator.h"

#include "modules/libsysmodule.h"

ModuleManager::ModuleManager()
{
    m_modules.emplace_back(Module("cellSysutil", {
       {0x0BAE8772, wrap(cellVideoOutConfigure)},
       {0xE558748D, wrap(cellVideoOutGetResolution)},
       {0x887572D5, wrap(cellVideoOutGetState)}
    }));
}

bool ModuleManager::find(const std::string& libraryName, u32 functionId)
{
    for (const auto& module : m_modules) {
        if (module.name != libraryName) {
            continue;
        }
        for (const auto& function : module.functions) {
            if (function.first != functionId) {
                continue;
            }
            return true;
        }
    }
    return false;
}

void ModuleManager::call(PPUThread& thread)
{
    const u32 fnid = thread.gpr[11];

    for (const auto& module : m_modules) {
        for (const auto& function : module.functions) {
            if (function.first == fnid) {
                function.second->call(thread, nucleus.memory.getBaseAddr());
                return;
            }
        }
    }
    nucleus.log.warning(LOG_HLE, "Unknown Function ID: 0x%X", fnid);
}
