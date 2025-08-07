#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(const std::string& source) {
  // Step One: Identify all iterators to space characters
  auto space_it = find_all(source.begin(), source.end(), ::isspace);

  // Step Two: Generate tokens between consecutive space characters
  Corpus corpus;
  std::transform(
    space_it.begin(), space_it.end() - 1, space_it.begin() + 1,
    std::inserter(corpus, corpus.end()),
    [&source](auto begin, auto end) {
      return Token(source, begin, end);
    });

  // Step Three: Get rid of empty tokens
  std::erase_if(corpus, [](const Token& token) {
    return token.content.empty();
  });
  return corpus;
}

std::set<Mispelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  // Step One: Skip words that are already correctly spelled.
  auto view = source 
            | std::ranges::views::filter([&dictionary](const Token& token) {
                return !dictionary.contains(token.content);
            })
            // Step Two: Find one-edit-away words in the dictionary using Damerau-Levenshtein
            | std::ranges::views::transform([&dictionary](const Token& token) {
                auto view = dictionary 
                          | std::ranges::views::filter([&token](const std::string& word) {
                              return levenshtein(token.content, word) == 1;
                          });
                std::set<std::string> suggestions(view.begin(), view.end());
                return Mispelling{token, std::move(suggestions)};
            });
  
  // Step Three: Drop misspellings with no suggestions.
  std::set<Mispelling> misspellings;
  std::ranges::copy_if(view, std::inserter(misspellings, misspellings.end()),
                       [](const Mispelling& mispelling) {
                         return !mispelling.suggestions.empty();
                       });

  return misspellings;
};

/* Helper methods */

#include "utils.cpp"