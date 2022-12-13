#pragma once

//
// This file is distributed under the MIT License. See LICENSE.md for details.
//

#include "llvm/ADT/StringRef.h"
#include "llvm/Object/Binary.h"

#include "revng/Model/Binary.h"

namespace llvm {
namespace object {
class ObjectFile;
}
} // namespace llvm

llvm::Error importBinary(TupleTree<model::Binary> &Model,
                         llvm::object::ObjectFile &BinaryHandle,
                         uint64_t PreferredBaseAddress,
                         unsigned FetchDebugInfoWithLevel);
llvm::Error importBinary(TupleTree<model::Binary> &Model,
                         llvm::StringRef Path,
                         uint64_t PreferredBaseAddress,
                         unsigned FetchDebugInfoWithLevel);
