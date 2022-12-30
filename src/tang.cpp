#include <cstring>
#include <iomanip>
#include <iostream>
#include "tang.hpp"

using namespace Tang;
using namespace std;

void printHelpText() {
  int width = 15;
  int indent = 20;
  cout
    << setw(width) << "--evaluate ARGUMENT, -e ARGUMENT" << endl
    << setw(indent) << " " << "Evaluate supplied ARGUMENT instead of stdin" << endl
    << setw(width) << "--help, -h" << endl
    << setw(indent) << " " << "Display help message" << endl
    << setw(width) << "--script, -s" << endl
    << setw(indent) << " " << "Evaluate as a script instead of a template" << endl
  ;
}

int main(int argc, char* argv[]) {
  bool isScript{false};
  char * eval{nullptr};

  // Parse Command line arguments.
  for (int i = 0; i < argc; ++i) {
    // Evaluate the provided argument instead of reading from stdin.
    if (!strcmp(argv[i], "--evaluate") || !strcmp(argv[i], "-e")) {
      if (i + 1 >= argc) {
        // Error: not enough arguments.
        cerr << "Error, not enough arguments";
        return 1;
      }
      eval = argv[i + 1];
      ++i;
    }
    // Print the help text.
    if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h")) {
      printHelpText();
      return 0;
    }
    // Evaluate the code as a script rather than a template.
    if (!strcmp(argv[i], "--script") || !strcmp(argv[i], "-s")) {
      isScript = true;
    }
  }

  auto tang = TangBase::make_shared();
  if (eval) {
    if (isScript) {
      auto program = tang->compileScript(eval);
      cout << program.execute().out;
    }
    else {
      auto program = tang->compileTemplate(eval);
      cout << program.execute().out;
    }
  }
  else {
    if (isScript) {
      auto program = tang->compileScript(cin);
      cout << program.execute().out;
    }
    else {
      auto program = tang->compileTemplate(cin);
      cout << program.execute().out;
    }
  }
  return 0;
}
