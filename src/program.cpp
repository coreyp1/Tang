/**
 * @file
 * Define the Tang::Program class.
 */

#include <sstream>
#include "program.hpp"
#include "opcode.hpp"
#include "tangScanner.hpp"
#include "tangParser.hpp"
#include "astNodeString.hpp"
#include "computedExpressionError.hpp"

using namespace std;
using namespace Tang;

Program::Program(string code, Program::CodeType codeType) : code{code}, codeType{codeType}, ast{nullptr} {
  this->parse();
  if (this->ast) {
    this->compile();
  }
}

void Program::parse() {
  stringstream ss{this->code};
  TangScanner scanner{ss, std::cout};
  Error * error{nullptr};
  TangParser parser{scanner, this->ast, error};
  parser.parse();
  if (error) {
    this->result = GarbageCollected::make<ComputedExpressionError>(*error);
    delete error;
  }
}

void Program::pushEnvironment(const shared_ptr<AstNode> & ast) {
  // Prepare the identifier mapping stack with an empty map.
  this->identifierStack.push_back(map<string,size_t>{});

  // Prepare the string mapping stack with an empty map.
  this->stringStack.push_back(map<string,size_t>{});

  // Gather all of the identifiers in the current scope into the current map.
  ast->collectIdentifiers(*this);

  // Gather all of the strings in the current scope into the current map.
  ast->collectStrings(*this);
}

void Program::popEnvironment() {
  // Remove stack entries.
  this->identifierStack.pop_back();
  this->stringStack.pop_back();
}

void Program::compile() {
  // Prepare the environment.
  this->pushEnvironment(this->ast);

  // Reserve spaces on the stack for each variable.
  for ([[maybe_unused]] const auto & x : this->getIdentifiers()) {
    this->bytecode.push_back((uinteger_t)Opcode::NULLVAL);
  }

  // Reserve spaces on the stack for each string.
  // We must be careful to add them in the expected order, so figure out the
  // order first, and put that into `stringLiterals`.
  vector<string> stringLiterals(this->stringStack.back().size());
  for (auto & item : this->stringStack.back()) {
    stringLiterals[item.second] = item.first;
  }
  // Now that the strings are in the correct order, push them onto the stack.
  for (auto & literal : stringLiterals) {
    AstNodeString(literal, Tang::location{}).compileLiteral(*this);
  }

  // Compile the program.
  this->ast->compile(*this);

  // Release the environment.
  this->popEnvironment();
}

void Program::addIdentifier(const string & name, optional<size_t> position) {
  auto & identifiers = this->identifierStack.back();
  if (identifiers.count(name) == 0) {
    identifiers[name] = identifiers.size();
  }

  // If a specific position was requested, then swap entries as necessary.
  if (position && (identifiers[name] != *position)) {
    map<size_t, string> flipped{};
    for (auto i : identifiers) {
      flipped[i.second] = i.first;
    }
    identifiers[flipped[*position]] = identifiers[name];
    identifiers[name] = *position;
  }
};

const map<string, size_t>& Program::getIdentifiers() const {
  return this->identifierStack.back();
}

void Program::addString(const string & val) {
  auto & strings = this->stringStack.back();
  if (strings.count(val) == 0) {
    strings[val] = strings.size();
  }
}

const map<string, size_t>& Program::getStrings() const {
  return this->stringStack.back();
}

string Program::getCode() const {
  return this->code;
}

optional<const shared_ptr<AstNode>> Program::getAst() const {
  if (this->ast) {
    return this->ast;
  }
  return nullopt;
}

optional<const GarbageCollected> Program::getResult() const {
  return this->result;
}

size_t Program::addBytecode(uinteger_t op) {
  this->bytecode.push_back(op);
  return this->bytecode.size();
}

const Bytecode & Program::getBytecode() {
  return this->bytecode;
}

bool Program::setJumpTarget(size_t opcodeAddress, uinteger_t jumpTarget) {
  // Verify that the address is in scope.
  if (opcodeAddress >= this->bytecode.size() - 1) {
    return false;
  }
  // Verify that the opcodeAddress is, in fact, a jump instruction.
  // TODO

  // Set the instruction.
  this->bytecode[opcodeAddress + 1] = jumpTarget;
  return true;
}

