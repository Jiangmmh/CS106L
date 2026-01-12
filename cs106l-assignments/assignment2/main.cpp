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
#include <sstream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>

std::string kYourName = "Minghan Jiang"; // Don't forget to change this!

/**
 * Takes in a name and returns the initials of that name.
 * For example, "Haven Whitney" would return "HW".
 * 
 * @param name  The name to fetch initials from.
 * @returns     A string containing the initials of the name.
 */
std::string fetch_initials(const std::string& name) {
  std::string initials;

  std::stringstream ss(name);
  std::string token;
  while (std::getline(ss, token, ' ')) {
    if (!token.empty()) {
      initials += token[0];
    }
  }

  return initials;
}

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
std::unordered_set<std::string> get_applicants(std::string filename) {
  std::ifstream input_file(filename);
  if (!input_file.is_open()) {
    std::cerr << "Error: Could not open file '" << filename << "'." << std::endl;
    exit(1);
  }

  std::unordered_set<std::string> applicants;

  std::string line;
  while (std::getline(input_file, line)) {
    applicants.insert(line);
  }

  return applicants;
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name, std::unordered_set<std::string>& students) {
  std::queue<const std::string*> matches;
  std::string target_initials = fetch_initials(name);

  for (const std::string& student_name : students) {
    if (fetch_initials(student_name) == target_initials) {
      matches.push(&student_name);
    }
  }

  return matches;
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
  if (matches.empty()) {
    return "NO MATCHES FOUND.";
  }

  // Example implementation: Return the first match in the queue.
  const std::string* match = matches.front();
  matches.pop();
  return *match;
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
