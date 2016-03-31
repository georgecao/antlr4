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

#include "Parser.h"

#include "NoViableAltException.h"

using namespace org::antlr::v4::runtime;

NoViableAltException::NoViableAltException(Parser *recognizer)
  : NoViableAltException(recognizer, recognizer->getInputStream(), recognizer->getCurrentToken(), recognizer->getCurrentToken(),
                         nullptr, recognizer->ctx) {
}

NoViableAltException::NoViableAltException(Parser *recognizer, TokenStream *input, Token *startToken,
  Token *offendingToken, atn::ATNConfigSet *deadEndConfigs, ParserRuleContext *ctx)
  : RecognitionException(recognizer, input, ctx, offendingToken), deadEndConfigs(deadEndConfigs), startToken(startToken) {
}

std::shared_ptr<Token> NoViableAltException::getStartToken() {
  return startToken;
}

std::shared_ptr<atn::ATNConfigSet> NoViableAltException::getDeadEndConfigs() {
  return deadEndConfigs;
}
