/**
 * (c) 2015 Alexandro Sanchez Bach. All rights reserved.
 * Released under GPL v2 license. Read LICENSE for more details.
 */

#pragma once

#include "nucleus/common.h"
#include "nucleus/cpu/backend/target.h"
#include "nucleus/cpu/hir/block.h"
#include "nucleus/cpu/hir/function.h"
#include "nucleus/cpu/hir/module.h"
#include "nucleus/cpu/hir/pass.h"

#include <memory>
#include <vector>

namespace cpu {
namespace backend {

class Compiler {
    // Compiler passes
    std::vector<std::unique_ptr<hir::Pass>> passes;

protected:
    // Optimize HIR
    virtual bool optimize(hir::Function* function);

public:
    // Generic target information
    TargetInfo targetInfo;

    // Constructor
    Compiler();

    // Add optimization passes
    virtual void addPass(std::unique_ptr<hir::Pass> pass);

    // Compile HIR
    virtual bool compile(hir::Block* block) = 0;
    virtual bool compile(hir::Function* function) = 0;
    virtual bool compile(hir::Module* module) = 0;
};

}  // namespace backend
}  // namespace cpu