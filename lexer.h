/*
 * MIT License
 * Copyright (c) 2022 Cunyuan(Holden) Gao
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CRIMSON_LEXER_H
#define CRIMSON_LEXER_H

extern "C" {
#include <clang-c/Index.h>
}

#include <variant>
#include <llvm/Support/CommandLine.h>

#include "diagnostic.h"

namespace crimson {
  struct TokenStream;
  using LexResult = std::variant<TokenStream, std::string>;

  LexResult parseTokens(const llvm::cl::opt<std::string>& p_filename);

  struct TokenStream {
    unsigned int m_tokens_size;

    TokenStream() : m_tokens(nullptr), m_tokens_size(0), m_unit(nullptr) {}
    TokenStream(TokenStream&& other) noexcept;
    ~TokenStream();

    CXToken& operator[](int p_index);

    friend LexResult parseTokens(const llvm::cl::opt<std::string>& p_filename);
  private:
    CXTranslationUnit m_unit;
    CXToken* m_tokens;
  };
} // namespace crimson

#endif //CRIMSON_LEXER_H
