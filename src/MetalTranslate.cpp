#include "MetalTranslate.h"

#include <ctranslate2/translator_pool.h>
#include <iostream>
#include <onmt/Tokenizer.h>

namespace MetalTranslate {

MetalTranslate::MetalTranslate(MetalTranslateConfig config) {
  this->_config = config;
}

std::string MetalTranslate::Translate(std::string source,
                                      std::string source_code,
                                      std::string target_code) {

  // Tokenizer
  onmt::Tokenizer tokenizer(this->_config.ModelPath + "sentencepiece.model");
  std::vector<std::string> tokens;
  tokenizer.tokenize(source, tokens);

  std::string source_prefix = "__" + source_code + "__";
  tokens.insert(tokens.begin(), source_prefix);

  // CTranslate2
  const size_t num_translators = 1;
  const size_t num_threads_per_translator = 4;
  ctranslate2::TranslatorPool translator(
      num_translators, num_threads_per_translator,
      this->_config.ModelPath + "model", ctranslate2::Device::CPU);

  const std::vector<std::vector<std::string>> batch = {tokens};
  const std::vector<std::vector<std::string>> target_prefix = {
      {"__" + target_code + "__"}};
  const int max_batch_size = 2024;

  const std::vector<ctranslate2::TranslationResult> results =
      translator.translate_batch(batch, target_prefix);

  const std::vector<std::string> translatedTokens = results[0].output();

  std::string result = tokenizer.detokenize(translatedTokens);

  // Remove target prefix
  // __es__ Traducción de texto con MetalTranslate
  // -> Traducción de texto con MetalTranslate
  result = result.substr(7);

  return result;
}

} // namespace MetalTranslate

int main() {
  MetalTranslate::MetalTranslateConfig config;

  MetalTranslate::MetalTranslate translate(config);

  std::string result =
      translate.Translate("Translating text with MetalTranslate", "en", "es");

  std::cout << "Result: " << result << std::endl;

  return 0;
}
