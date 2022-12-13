#pragma once

//
// This file is distributed under the MIT License. See LICENSE.md for details.
//

#include "llvm/Object/Binary.h"

#include "revng/Model/Binary.h"

class DwarfImporter {
private:
  TupleTree<model::Binary> &Model;
  std::vector<std::string> LoadedFiles;
  using DwarfID = std::pair<size_t, size_t>;
  std::map<DwarfID, model::QualifiedType> DwarfToModel;
  uint64_t PreferredBaseAddress;

public:
  DwarfImporter(TupleTree<model::Binary> &Model,
                uint64_t PreferredBaseAddress) :
    Model(Model), PreferredBaseAddress(PreferredBaseAddress) {}

public:
  model::QualifiedType *findType(DwarfID ID) {
    auto It = DwarfToModel.find(ID);
    return It == DwarfToModel.end() ? nullptr : &It->second;
  }

  const model::QualifiedType &
  recordType(DwarfID ID, const model::QualifiedType &QT) {
    revng_assert(DwarfToModel.count(ID) == 0);
    return DwarfToModel.insert({ ID, QT }).first->second;
  }

  TupleTree<model::Binary> &getModel() { return Model; }

public:
  void import(llvm::StringRef FileName, unsigned FetchDebugInfoWithLevel);

private:
  void import(const llvm::object::Binary &TheBinary, llvm::StringRef FileName);
};
