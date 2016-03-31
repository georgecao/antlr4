﻿/*
 * [The "BSD license"]
 *  Copyright (c) 2016 Mike Lischke
 *  Copyright (c) 2013 Terence Parr
 *  Copyright (c) 2013 Dan McLaughlin
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 *  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 *  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MurmurHash.h"
#include "StringBuilder.h"
#include "PredictionContext.h"

#include "ATNConfig.h"

using namespace org::antlr::v4::runtime::atn;

ATNConfig::ATNConfig(ATNConfig *old) : state(old->state), alt(old->alt), semanticContext(old->semanticContext) {
  InitializeInstanceFields();
  this->context = old->context;
  this->reachesIntoOuterContext = old->reachesIntoOuterContext;
}

ATNConfig::ATNConfig(ATNState *state, int alt, PredictionContext *context) : state(state), alt(alt), context(context), semanticContext(nullptr) {
}

ATNConfig::ATNConfig(ATNState *state, int alt, PredictionContext *context, SemanticContext *semanticContext) : state(state), alt(alt), semanticContext(semanticContext) {
  InitializeInstanceFields();
  this->context = context;
}

ATNConfig::ATNConfig(ATNConfig *c, ATNState *state) : state(state), alt(0), context(nullptr), semanticContext(nullptr)
{
}

ATNConfig::ATNConfig(ATNConfig *c, ATNState *state, SemanticContext *semanticContext) : state(state), alt(0), context(nullptr), semanticContext(semanticContext)
{
}

ATNConfig::ATNConfig(ATNConfig *c, SemanticContext *semanticContext) : state(nullptr), alt(0), context(nullptr), semanticContext(semanticContext)
{
}

ATNConfig::ATNConfig(ATNConfig *c, ATNState *state, PredictionContext *context) : state(state), alt(0), context(context), semanticContext(nullptr)
{
}

ATNConfig::ATNConfig(ATNConfig *c, ATNState *state, PredictionContext *context, SemanticContext *semanticContext) : state(state), alt(c->alt), semanticContext(semanticContext) {
  InitializeInstanceFields();
  this->context = context;
  this->reachesIntoOuterContext = c->reachesIntoOuterContext;
}

size_t ATNConfig::hashCode() const {
  size_t hashCode = misc::MurmurHash::initialize(7);
  hashCode = misc::MurmurHash::update(hashCode, (size_t)state->stateNumber);
  hashCode = misc::MurmurHash::update(hashCode, (size_t)alt);
  hashCode = misc::MurmurHash::update(hashCode, (size_t)context);
  hashCode = misc::MurmurHash::update(hashCode, (size_t)semanticContext);
  hashCode = misc::MurmurHash::finish(hashCode, 4);
  return hashCode;
}

bool ATNConfig::operator == (const ATNConfig& other) const
{
  return this->state->stateNumber == other.state->stateNumber && this->alt == other.alt &&
    (this->context == other.context || (this->context != nullptr && this->context == other.context)) &&
    this->semanticContext == other.semanticContext;
}

std::wstring ATNConfig::toString() {
  return toString(true);
}


void ATNConfig::InitializeInstanceFields() {
  reachesIntoOuterContext = 0;
}
