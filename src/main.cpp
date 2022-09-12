#include <iostream>
#include <string>
#include <chrono>
#include <fmt/core.h>
#include "MetalTranslate.h"

void help() {
  std::cout << "Usage: metaltranslate <text> <source code> <target code>\n"
            << "Example: metaltranslate \"my text to translate\" en es\n";
}

int main(int argc, char **argv) {
  MetalTranslate::MetalTranslate metalTranslate;
  if (argc < 2) {
    help();
    return 1;
  }
  std::string text{argv[1]};
  std::string src_lang;
  if (argc > 2) {
    src_lang = std::string(argv[2]);
  }
  std::string tgt_lang;
  if (argc > 3) {
    tgt_lang = std::string(argv[3]);
  }

  auto start = std::chrono::high_resolution_clock::now();
  std::string result = metalTranslate.Translate(text, src_lang, tgt_lang);
  auto end = std::chrono::high_resolution_clock::now();
  fmt::print("Translated Text: {}\n", result);
  fmt::print("Elapsed time in milliseconds: {}ms\n", std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start).count());

  return 0;
}
