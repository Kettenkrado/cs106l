/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

std::string kYourName = "Ivy Blossom"; // Don't forget to change this!

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::set<std::string> get_applicants(std::string filename) {
  ifstream ifs(filename);
  set<string> applicants;
  string name;

  while (getline(ifs, name)) {
    applicants.insert(name);
  }

  return applicants;
}

/**
 * Helper function of find_matches, calculate the initials of some student's name.
 * 
 * @param name  The name of some student.
 * @return      A string of this student's initials.
 */
std::string calculate_initials(const std::string& name) {
  std::string initials;
  bool isLastName = false;

  for (auto c: name) {
    if (c == ' ') {
      isLastName = true;
    } else if (initials.empty() || isLastName) {
      initials += c;
      if (isLastName) break;
    }
  }

  return initials;
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
  std::queue<const std::string*> matches;
  string initials = calculate_initials(name);
  string candidate_initials;

  for (const auto& candidate: students) {
    candidate_initials = calculate_initials(candidate);
    if (candidate_initials == initials) 
      matches.push(&candidate);
  }

  return matches;
}

/**
 * Calculate the similarity of two strings (here names) 
 * by Levenshtein Distance.
 * 
 * @param s1  One name string.
 * @param s2  Another name string.
 * @return    The similarity between them.
 */
int levenshteinDistance(const std::string& s1, const std::string& s2) {
  int m = s1.length();
  int n = s2.length();
  std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

  for (int i = 0; i <= m; ++i) {
      for (int j = 0; j <= n; ++j) {
          if (i == 0) {
              dp[i][j] = j;
          } else if (j == 0) {
              dp[i][j] = i;
          } else {
              dp[i][j] = std::min({dp[i - 1][j] + 1,        // delete
                                   dp[i][j - 1] + 1,        // insert
                                   dp[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1)}); // constitute
          }
      }
  }

  return dp[m][n];
}


/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
  string best_match;
  float similarity = 0;

  while (!matches.empty()) {
    string candidate = *(matches.front());
    int distance = levenshteinDistance(kYourName, candidate);
    float current_similarity = 1 - (float) distance / (float) max(kYourName.length(), candidate.length());
    if (current_similarity > similarity) {
      best_match = candidate;
      similarity = current_similarity;
    } matches.pop();
  }

  if (best_match.empty()) return "NO MATCHES FOUND.";
  return best_match;
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
