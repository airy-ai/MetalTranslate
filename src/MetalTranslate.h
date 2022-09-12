#include <string>
#include <ctranslate2/translator_pool.h>
#include <onmt/Tokenizer.h>

namespace MetalTranslate {
class MetalTranslate {
public:
  MetalTranslate();
  ~MetalTranslate();
  std::string Translate(const std::string& text, const std::string& src_lang, const std::string& tgt_lang);

private:
  std::string model_path = "model_repo/translate-fairseq_m2m_100_418M/";
  onmt::Tokenizer *tokenizer;
  ctranslate2::TranslatorPool *translator;
};
} // namespace MetalTranslate
