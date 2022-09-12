#include "MetalTranslate.h"
#include <iostream>
#include <fmt/core.h>

namespace MetalTranslate {

MetalTranslate::MetalTranslate() {
  tokenizer = new onmt::Tokenizer(fmt::format("{}sentencepiece.model", this->model_path));
  const size_t num_translators = 2;
  const size_t num_threads_per_translator = 0; // Unused with DNNL
  translator = new ctranslate2::TranslatorPool(num_translators,
                                              num_threads_per_translator,
                                              fmt::format("{}model", this->model_path),
                                              ctranslate2::Device::CPU);
}

MetalTranslate::~MetalTranslate() {
  delete tokenizer;
  delete translator;
}

std::string MetalTranslate::Translate(const std::string& text, const std::string& src_lang, const std::string& tgt_lang) {
  std::vector<std::string> tokens;
  tokenizer->tokenize(text, tokens);
  std::string source_prefix = fmt::format("__{}__", src_lang);
  tokens.insert(tokens.begin(), source_prefix);
  const std::vector<std::vector<std::string>> batch = {tokens};
  const std::vector<std::vector<std::string>> target_prefix = {{
      fmt::format("__{}__", tgt_lang)
    }
  };
  const std::vector<ctranslate2::TranslationResult> results = translator->translate_batch(batch, target_prefix);
  const std::vector<std::string> translatedTokens = results[0].output();
  std::string result = tokenizer->detokenize(translatedTokens);
  return result.substr(7);
}

} // namespace MetalTranslate
