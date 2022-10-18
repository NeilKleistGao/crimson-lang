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

#include "lexer.h"

#include <exception>
#include <iostream>

namespace crimson {
  // TODO: other systems
  static const char* s_compiler_args[] = {
          "-I/usr/include",
          "-I."
  };

  TokenStream::~TokenStream() {
    clang_disposeTokens(m_unit, m_tokens, m_tokens_size);
    clang_disposeTranslationUnit(m_unit);

    m_unit = nullptr; m_tokens = nullptr; m_tokens_size = 0;
  }

  CXToken& TokenStream::operator[](int p_index) {
    if (m_tokens == nullptr) {
      throw std::runtime_error("the token stream is empty.");
    }
    if (p_index < 0 || p_index > m_tokens_size) {
      throw std::out_of_range("index out of range in token stream.");
    }

    return m_tokens[p_index];
  }

  LexResult parseTokens(const llvm::cl::opt<std::string>& p_filename) {
    CXIndex index = clang_createIndex(0, 0);
    TokenStream stream{};

    try {
      stream.m_unit = clang_parseTranslationUnit(index, p_filename.c_str(),
                                                 s_compiler_args, 2,
                                                 nullptr, 0,
                                                 CXTranslationUnit_None);

      CXFile file = clang_getFile(stream.m_unit, p_filename.c_str());
      // TODO:

      return LexResult{std::move(stream)};
    }
    catch (...) {
      std::cerr << "can't compile file " << p_filename.c_str() << "." << std::endl;
      return LexResult{ErrorMessage{}};
    }
  }

} // namespace crimson
