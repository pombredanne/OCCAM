//
// OCCAM
//
// Copyright (c) 2011-2012, SRI International
//
//  All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of SRI International nor the names of its contributors may
//   be used to endorse or promote products derived from this software without
//   specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

/*
 * IntPolicy.h
 *
 *  Created on: Jul 11, 2011
 *      Author: malecha
 */

#ifndef __SPECPOLICY_H__
#define __SPECPOLICY_H__

#include "Previrtualize.h"
#include "PrevirtTypes.h"

namespace llvm
{
  class CallGraph;
}

namespace previrt
{
  struct SpecializationPolicy
  {
  protected:
    SpecializationPolicy();

  public:
    virtual
    ~SpecializationPolicy(); // Don't call this
    virtual void
    release() = 0;

  public:
    virtual llvm::Value**
    specializeOn(llvm::Function*, llvm::User::op_iterator,
        llvm::User::op_iterator) const = 0;

    virtual bool
    specializeOn(llvm::Function*, const PrevirtType*,
        const PrevirtType*, llvm::SmallBitVector&) const = 0;

    virtual bool
    specializeOn(llvm::Function*, std::vector<PrevirtType>::const_iterator,
        std::vector<PrevirtType>::const_iterator, llvm::SmallBitVector&) const = 0;

  public:
    static bool
    isConstantSpecializable(llvm::Constant* cst)
    {
      if (cst == NULL) return false;
      return PrevirtType::abstract(cst).isConcrete();
    }

  public:
    static SpecializationPolicy*
    aggressivePolicy();

    static SpecializationPolicy*
    conservativePolicy();

    static SpecializationPolicy*
    recursiveGuard(SpecializationPolicy*, llvm::CallGraph&);
  };
}

#endif /* __SPECPOLICY_H__ */
