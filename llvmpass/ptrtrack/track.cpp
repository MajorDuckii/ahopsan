#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include <iostream>
#include <vector>

using namespace llvm;

namespace {

class InterestingMemoryOperand {
public:
  Use *PtrUse;
  bool IsWrite;
  Type *OpType;
  uint64_t TypeSize;

  InterestingMemoryOperand(Instruction *I, unsigned OperandNo, bool IsWrite, class Type *OpType)
      : IsWrite(IsWrite), OpType(OpType)
  {
    PtrUse = &I->getOperandUse(OperandNo);
  }

  Instruction *getInsn() { return cast<Instruction>(PtrUse->getUser()); }
  Value *getPtr() { return PtrUse->get(); }
};

// struct PtrTrack : public FunctionPass {
class PtrTrack : public FunctionPass {
public:
  static char ID;
  PtrTrack() : FunctionPass(ID) {}

  bool runOnFunction(Function &F) override;
  void instrumentMop(InterestingMemoryOperand &O);
  void getInterestingMemoryOperands(Instruction *I, SmallVectorImpl<InterestingMemoryOperand> &Interesting);
  void doInstrumentAddress(Instruction *I, Instruction *InsertBefore, Value *Addr);
  void instrumentAddress(Instruction *OrigIns, Instruction *InsertBefore, Value *Addr);

}; // end of struct PtrTrack
} // end of anonymous namespace

bool PtrTrack::runOnFunction(Function &F)
{
  // Print name of function
  std::cerr << F.getName().data() << "\n";

  SmallVector<InterestingMemoryOperand, 16> OperandsToInstrument;
  bool FunctionModified = false;

  for (auto &B : F) { // Iterate over each Basic Blocks in Functions
    // asm("int3");
    for (auto &I : B) { // Iterate over each Instructions in Basic Blocks
      SmallVector<InterestingMemoryOperand, 1> InterestingOperands;
      getInterestingMemoryOperands(&I, InterestingOperands);

      // Dynamically cast Instruction to CallInst.
      // This step will return false for any instruction which is
      // not a CallInst
      if (InterestingOperands.empty())
        continue;

      for (auto &Operand : InterestingOperands)
        OperandsToInstrument.push_back(Operand);

    } // for (auto &I : B)
  }   // for (auto &B
  for (auto &Operand : OperandsToInstrument) {
    instrumentMop(Operand);
    FunctionModified = true;
  }
  return FunctionModified;
}

void PtrTrack::getInterestingMemoryOperands(Instruction *I, SmallVectorImpl<InterestingMemoryOperand> &Interesting)
{
  // Skip memory accesses inserted by another instrumentation.
  if (I->hasMetadata("nosanitize"))
    return;

  if (LoadInst *LI = dyn_cast<LoadInst>(I)) {
    Interesting.emplace_back(I, LI->getPointerOperandIndex(), false, LI->getType());
  }
  else if (StoreInst *SI = dyn_cast<StoreInst>(I)) {
    Interesting.emplace_back(I, SI->getPointerOperandIndex(), true, SI->getValueOperand()->getType());
  }
  else if (AtomicRMWInst *RMW = dyn_cast<AtomicRMWInst>(I)) {
    Interesting.emplace_back(I, RMW->getPointerOperandIndex(), true, RMW->getValOperand()->getType());
  }
  else if (AtomicCmpXchgInst *XCHG = dyn_cast<AtomicCmpXchgInst>(I)) {
    Interesting.emplace_back(I, XCHG->getPointerOperandIndex(), true, XCHG->getCompareOperand()->getType());
  }
  // else if (auto CI = dyn_cast<CallInst>(I)) {
  // }
}

void PtrTrack::instrumentMop(InterestingMemoryOperand &O)
{
  Value *Addr = O.getPtr();
  doInstrumentAddress(O.getInsn(), O.getInsn(), Addr);
}

void PtrTrack::doInstrumentAddress(Instruction *I, Instruction *InsertBefore, Value *Addr)
{
  instrumentAddress(I, InsertBefore, Addr);
  LLVMContext &C = I->getContext();
  MDNode *N = MDNode::get(C, MDString::get(C, "FastAsan"));
  I->setMetadata("fastasan", N);
}

void PtrTrack::instrumentAddress(Instruction *OrigIns, Instruction *InsertBefore, Value *Addr)
{
  // IRBuilder<> IRB(InsertBefore);
  // Value *AddrLong = IRB.CreatePointerCast(Addr, IntptrTy);
}

char PtrTrack::ID = 0;
static RegisterPass<PtrTrack> X("testpp", "Display Function Names");
