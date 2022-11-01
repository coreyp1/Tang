/**
 * @file
 * Define the Tang::AstNodeAssign class.
 */

#include <string>
#include "astNodeAssign.hpp"
#include "astNodeIdentifier.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeAssign::AstNodeAssign(shared_ptr<AstNode> lhs, shared_ptr<AstNode> rhs, Tang::location location) : AstNode(location), lhs{lhs}, rhs{rhs} {}

string AstNodeAssign::dump(string indent) const {
  return indent + "Assign:\n"
    + indent + "  lhs:\n"
    + this->lhs->dump(indent + "    ")
    + indent + "  rhs:\n"
    + this->rhs->dump(indent + "    ");
}

void AstNodeAssign::compileIdentifiers(Program & program) const {
  this->lhs->compileIdentifiers(program);
  this->rhs->compileIdentifiers(program);
}

void AstNodeAssign::compile(Tang::Program & program) const {
  // Compile the rhs, leaving the value on the stack.
  this->rhs->compile(program);

  // Store the value if the lhs is an identifier.
  if (typeid(*this->lhs) == typeid(AstNodeIdentifier)) {
    auto & lhsConv = static_cast<AstNodeIdentifier&>(*this->lhs);
    auto & identifier = program.identifierStack.back();
    if (identifier.count(lhsConv.name)) {
      program.addBytecode((uint64_t)Opcode::POKE);
      program.addBytecode((uint64_t)identifier[lhsConv.name]);
    }
  }
}

shared_ptr<AstNode> AstNodeAssign::makeCopy() const {
  return make_shared<AstNodeAssign>(this->lhs->makeCopy(), this->rhs->makeCopy(), this->location);
}
