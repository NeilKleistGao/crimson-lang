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

#include "compiler.h"

#include <iostream>

#include "lexer.h"

namespace crimson {
  int compile(int p_argc, const char* p_argv[]) {
    using namespace llvm;

    cl::opt<std::string> filename_option(cl::Positional,
                                         cl::desc("Input file"),
                                         cl::Required);
    cl::ParseCommandLineOptions(p_argc, p_argv);

    constexpr int ERR_INDEX = 1;

    LexResult lex_res = parseTokens(filename_option);
    if (lex_res.index() == ERR_INDEX) {
      std::cerr << std::get<ERR_INDEX>(lex_res) << std::endl;
      return ERR_INDEX;
    }

    return 0;
  }
} // namespace crimson
