/**
 * (c) 2015 Nucleus project. All rights reserved.
 * Released under GPL v2 license. Read LICENSE for more details.
 */

#pragma once

#include "nucleus/common.h"
#include "nucleus/cpu/hir/block.h"
#include "nucleus/cpu/hir/function.h"
#include "nucleus/cpu/hir/type.h"
#include "nucleus/cpu/hir/value.h"

#include "llvm/IR/IRBuilder.h"

#include <string>
#include <vector>

namespace cpu {
namespace hir {

class Builder
{
    llvm::IRBuilder<> builder;

public:
    Builder();

    /**
     * HIR insertion
     */
    void SetInsertPoint(Block block);
    void SetInsertPoint(Block block, llvm::BasicBlock::iterator ip);

    /**
     * HIR constants
     */
    template <typename T>
    Value<T> get(typename T::type constant) {
        static_assert(std::is_integral<T::type>::value,
            "Builder::get accepts only integer values.");
        return builder.getIntN(T::size, constant);
    }

    /**
     * HIR symbol generation
     */
    Value<I8> CreateGlobalString(const std::string& str) {
        return builder.CreateGlobalString(str);
    }

    /**
     * HIR instruction generation
     */
    // Arithmetic operations
    template <typename T, int N>
    Value<T, N> CreateAdd(Value<T, N> lhs, Value<T, N> rhs) {
        static_assert(std::is_integral<T::type>::value,
            "Builder::CreateAdd accepts only integer values.");
        return builder.CreateAdd(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<T, N> CreateSub(Value<T, N> lhs, Value<T, N> rhs) {
        static_assert(std::is_integral<T::type>::value,
            "Builder::CreateSub accepts only integer values.");
        return builder.CreateSub(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<T, N> CreateMul(Value<T, N> lhs, Value<T, N> rhs) {
        static_assert(std::is_integral<T::type>::value,
            "Builder::CreateMul accepts only integer values.");
        return builder.CreateMul(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<T, N> CreateDiv(Value<T, N> lhs, Value<T, N> rhs) {
        static_assert(std::is_integral<T::type>::value,
            "Builder::CreateDiv accepts only integer values.");
        return builder.CreateDiv(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<T, N> CreateNeg(Value<T, N> v) {
        static_assert(std::is_integral<T::type>::value,
            "Builder::CreateNot accepts only integer values.");
        return builder.CreateNeg(v.value);
    }

    // Binary operations
    template <typename T, int N>
    Value<T, N> CreateAnd(Value<T, N> lhs, Value<T, N> rhs) {
        static_assert(std::is_integral<T::type>::value,
            "Builder::CreateAnd accepts only integer values.");
        return builder.CreateAnd(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<T, N> CreateOr(Value<T, N> lhs, Value<T, N> rhs) {
        static_assert(std::is_integral<T::type>::value,
            "Builder::CreateOr accepts only integer values.");
        return builder.CreateOr(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<T, N> CreateXor(Value<T, N> lhs, Value<T, N> rhs) {
        static_assert(std::is_integral<T::type>::value,
            "Builder::CreateXor accepts only integer values.");
        return builder.CreateXor(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<T, N> CreateNot(Value<T, N> v) {
        static_assert(std::is_integral<T::type>::value,
            "Builder::CreateNot accepts only integer values.");
        return builder.CreateNot(v.value);
    }

    // Floating-point arithmetic operations
    template <typename T, int N>
    Value<T, N> CreateFAdd(Value<T, N> lhs, Value<T, N> rhs) {
        static_assert(std::is_floating_point<T::type>::value,
            "Builder::CreateFAdd accepts only floating-point values.");
        return builder.CreateFAdd(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<T, N> CreateFSub(Value<T, N> lhs, Value<T, N> rhs) {
        static_assert(std::is_floating_point<T::type>::value,
            "Builder::CreateFSub accepts only floating-point values.");
        return builder.CreateFSub(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<T, N> CreateFMul(Value<T, N> lhs, Value<T, N> rhs) {
        static_assert(std::is_floating_point<T::type>::value,
            "Builder::CreateFMul accepts only floating-point values.");
        return builder.CreateFMul(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<T, N> CreateFDiv(Value<T, N> lhs, Value<T, N> rhs) {
        static_assert(std::is_floating_point<T::type>::value,
            "Builder::CreateFDiv accepts only floating-point values.");
        return builder.CreateFDiv(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<T, N> CreateFNeg(Value<T, N> v) {
        static_assert(std::is_floating_point<T::type>::value,
            "Builder::CreateFNeg accepts only floating-point values.");
        return builder.CreateFNeg(v.value);
    }

    // Conversion operations
    template <typename TO, typename TI, int N>
    Value<TO, N> CreateTrunc(Value<TI, N> v) {
        static_assert(std::is_integral<TI::type>::value && std::is_integral<TO::type>::value,
            "Builder::CreateTrunc accepts only integer values.");
        static_assert(TI::size < TO::size,
            "Builder::CreateTrunc converts only to smaller integer types.");
        return builder.CreateTrunc(v, TO::type().type);
    }

    template <typename TO, typename TI, int N>
    Value<TO, N> CreateSExt(Value<TI, N> v) {
        static_assert(std::is_integral<TI::type>::value && std::is_integral<TO::type>::value,
            "Builder::CreateSExt accepts only integer values.");
        static_assert(TI::size < TO::size,
            "Builder::CreateSExt converts only to larger integer types.");
        return builder.CreateSExt(v, TO::type().type);
    }

    template <typename TO, typename TI, int N>
    Value<TO, N> CreateZExt(Value<TI, N> v) {
        static_assert(std::is_integral<TI::type>::value && std::is_integral<TO::type>::value,
            "Builder::CreateZExt accepts only integer values.");
        static_assert(TI::size < TO::size,
            "Builder::CreateZExt converts only to larger integer types.");
        return builder.CreateZExt(v, TO::type().type);
    }

    template <typename TO, typename TI>
    Value<TO> CreateFPTrunc(Value<TI> v) {
        static_assert(std::is_floating_point<TI::type>::value && std::is_floating_point<TO::type>::value,
            "Builder::CreateFPTrunc accepts only floating-point values.");
        static_assert(TI::size > TO::size,
            "Builder::CreateFPTrunc converts only to smaller floating-point types.");
        return builder.CreateFPTruc(v, TO::type().type);
    }

    template <typename TO, typename TI>
    Value<TO> CreateFPExt(Value<TI> v) {
        static_assert(std::is_floating_point<TI::type>::value && std::is_floating_point<TO::type>::value,
            "Builder::CreateFPExt accepts only floating-point values.");
        static_assert(TI::size < TO::size,
            "Builder::CreateFPExt converts only to larger floating-point types.");
        return builder.CreateFPExt(v, TO::type().type);
    }
    
    template <typename TO, int NO=1, typename TI, int NI>
    Value<TO, NO> CreateBitCast(Value<TI, NI> v) {
        static_assert(TI::size == TO::size,
            "Builder::CreateFPExt converts only to larger floating-point types.");
        return builder.CreateBitCast(v, TO::type().type);
    }

    // Vector operations
    template <typename TVec, int N, typename TIdx>
    Value<TVec> CreateExtractElement(Value<TVec, N> vec, Value<TIdx> idx) {
        static_assert(std::is_integral<TIdx::type>::value,
            "Builder::CreateExtractElement accepts only integer indices.");
        return builder.CreateExtractElement(vec.value, idx.value);
    }

    // Aggregate operations
    template <int N, typename... TMembers>
    Value<typename std::tuple_element<N, std::tuple<TMembers...>>::type> CreateExtractValue(Value<Struct<TMembers...>> agg) {
        return builder.CreateExtractValue(vec.value, N);
    }

    // Memory access operations
    template <typename T, int N=1>
    Value<T*, N> CreateAlloca(const std::string& name) {
        // TODO: Support vectors (i.e. use the template parameter N)
        return builder.CreateAlloca(T::getType(), nullptr, name);
    }

    template <typename T>
    Value<T> CreateLoad(Value<T*> ptr) {
        return builder.CreateLoad(ptr.value);
    }

    template <typename T>
    void CreateStore(Value<T> val, Value<T*> ptr) {
        builder.CreateStore(val.value, ptr.value);
    }

    // Comparison operations
    template <typename T, int N>
    Value<I1, N> CreateICmpEQ(Value<T, N> lhs, Value<T, N> rhs) {
        return builder.CreateICmpEQ(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<I1, N> CreateICmpNE(Value<T, N> lhs, Value<T, N> rhs) {
        return builder.CreateICmpNE(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<I1, N> CreateICmpSLT(Value<T, N> lhs, Value<T, N> rhs) {
        return builder.CreateICmpSLT(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<I1, N> CreateICmpSLE(Value<T, N> lhs, Value<T, N> rhs) {
        return builder.CreateICmpSLE(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<I1, N> CreateICmpSGE(Value<T, N> lhs, Value<T, N> rhs) {
        return builder.CreateICmpSGE(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<I1, N> CreateICmpSGT(Value<T, N> lhs, Value<T, N> rhs) {
        return builder.CreateICmpSGT(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<I1, N> CreateICmpULT(Value<T, N> lhs, Value<T, N> rhs) {
        return builder.CreateICmpULT(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<I1, N> CreateICmpULE(Value<T, N> lhs, Value<T, N> rhs) {
        return builder.CreateICmpULE(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<I1, N> CreateICmpUGE(Value<T, N> lhs, Value<T, N> rhs) {
        return builder.CreateICmpUGE(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<I1, N> CreateICmpUGT(Value<T, N> lhs, Value<T, N> rhs) {
        return builder.CreateICmpUGT(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<I1, N> CreateFCmpOEQ(Value<T, N> lhs, Value<T, N> rhs) {
        return builder.CreateFCmpOEQ(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<I1, N> CreateFCmpONE(Value<T, N> lhs, Value<T, N> rhs) {
        return builder.CreateFCmpONE(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<I1, N> CreateFCmpOLT(Value<T, N> lhs, Value<T, N> rhs) {
        return builder.CreateFCmpOLT(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<I1, N> CreateFCmpOLE(Value<T, N> lhs, Value<T, N> rhs) {
        return builder.CreateFCmpOLE(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<I1, N> CreateFCmpOGE(Value<T, N> lhs, Value<T, N> rhs) {
        return builder.CreateFCmpOGE(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<I1, N> CreateFCmpOGT(Value<T, N> lhs, Value<T, N> rhs) {
        return builder.CreateFCmpOGT(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<I1, N> CreateFCmpUEQ(Value<T, N> lhs, Value<T, N> rhs) {
        return builder.CreateFCmpUEQ(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<I1, N> CreateFCmpUNE(Value<T, N> lhs, Value<T, N> rhs) {
        return builder.CreateFCmpUNE(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<I1, N> CreateFCmpULT(Value<T, N> lhs, Value<T, N> rhs) {
        return builder.CreateFCmpULT(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<I1, N> CreateFCmpULE(Value<T, N> lhs, Value<T, N> rhs) {
        return builder.CreateFCmpULE(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<I1, N> CreateFCmpUGE(Value<T, N> lhs, Value<T, N> rhs) {
        return builder.CreateFCmpUGE(lhs.value, rhs.value);
    }

    template <typename T, int N>
    Value<I1, N> CreateFCmpUGT(Value<T, N> lhs, Value<T, N> rhs) {
        return builder.CreateFCmpUGT(lhs.value, rhs.value);
    }

    // Other operations
    template <typename T, int N>
    Value<T, N> CreateSelect(Value<I1, N> cond, Value<T, N> isTrue, Value<T, N> isFalse) {
        return builder.CreateSelect(cond.value, isTrue.value, isFalse.value);
    }

    // Pointer operations
    template <typename TP, typename TV>
    Value<TP*> CreateIntToPtr(Value<TV> v) {
        return builder.CreateIntToPtr(v.value, llvm::PointerType::get(TP::getType()));
    }

    // Function operations
    template <typename TR>
    Value<TR> CreateCall(Function callee, std::vector<llvm::Value*> args) {
        return builder.CreateCall(callee.function, args);
    }

    template <typename T, int N>
    void CreateRet(Value<T, N> v) {
        builder.CreateRet(v.value);
    }

    void CreateRetVoid() {
        builder.CreateRetVoid();
    }

    // Branching operations
    void CreateBr(const Block& block) {
        builder.CreateBr(block.bb);
    }

    void CreateCondBr(Value<I1> cond, const Block& blockTrue, const Block& blockFalse) {
        builder.CreateCondBr(cond.value, blockTrue.bb, blockFalse.bb);
    }
};

}  // namespace hir
}  // namespace cpu