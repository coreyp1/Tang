/**
 * @file
 * Declare the Tang::Program class used to compile and execute source code.
 */

#ifndef TANG_PROGRAM_HPP
#define TANG_PROGRAM_HPP

#include <string>
#include <optional>
#include <vector>
#include <map>
#include "astNode.hpp"
#include "error.hpp"
#include "computedExpression.hpp"
#include "garbageCollected.hpp"

namespace Tang {
  class AstNode;

  /**
   * Contains the Opcodes of a compiled program.
   */
  using Bytecode = std::vector<uint64_t>;

  /**
   * Represents a compiled script or template that may be executed.
   */
  class Program {
  public:
    /**
     * Indicate the type of code that was supplied to the Program.
     */
    enum CodeType {
      Script,  ///< The code is pure Tang script, without any templating.
      Template ///< The code is a template.
    };

    /**
     * Create a compiled program using the provided code.
     *
     * @param code The code to be compiled.
     * @param codeType Whether the code is a `Script` or `Template`.
     */
    Program(std::string code, CodeType codeType);

    /**
     * Get the code that was provided when the Program was created.
     *
     * @return The source code from which the Program was created.
     */
    std::string getCode() const;

    /**
     * Get the AST that was generated by the parser.
     *
     * The parser may have failed, so the return is an `optional<>` type.  If
     * the compilation failed, check \ref Program::error.
     *
     * @return A pointer to the AST, if it exists.
     */
    std::optional<const std::shared_ptr<AstNode>> getAst() const;

    /**
     * Get the Opcodes of the compiled program, formatted like Assembly.
     *
     * @return A string containing the Opcode representation.
     */
    std::string dumpBytecode() const;

    /**
     * Get the result of the Program execution, if it exists.
     *
     * @return The result of the Program execution, if it exists.
     */
    std::optional<const GarbageCollected> getResult() const;

    /**
     * The output of the program, resulting from the program execution.
     */
    std::string out;

    /**
     * Add a uint64_t to the Bytecode.
     *
     * @param op The value to add to the Bytecode.
     */
    void addBytecode(uint64_t);

    /**
     * Execute the program's Bytecode, and return the current Program object.
     *
     * @return The current Program object.
     */
    Program & execute();

    /**
     * Stack of mappings of identifiers to their stack locations.
     */
    std::vector<std::map<std::string, size_t>> identifierStack;

  private:
    /**
     * Parse the code into an AST.
     */
    void parse();

    /**
     * Compile the AST into Bytecode.
     */
    void compile();

    /**
     * The code supplied when the Program was instantiated.
     */
    std::string code;

    /**
     * The type of code that was supplied when the Program was instantiated.
     */
    CodeType codeType;

    /**
     * A pointer to the AST, if parsing was successful.
     */
    shared_ptr<AstNode> ast;

    /**
     * The Bytecode of the compiled program.
     */
    Bytecode bytecode;

    /**
     * The result of the Program execution.
     */
    std::optional<GarbageCollected> result;
  };
}

#endif // TANG_PROGRAM_HPP

