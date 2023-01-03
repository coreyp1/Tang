/**
 * @file
 * Declare the Tang::Program class used to compile and execute source code.
 */

namespace Tang {
  class Program;
}

#ifndef TANG_PROGRAM_HPP
#define TANG_PROGRAM_HPP

#include <map>
#include <optional>
#include <set>
#include <string>
#include <vector>
#include "astNode.hpp"
#include "computedExpression.hpp"
#include "context.hpp"
#include "error.hpp"
#include "garbageCollected.hpp"
#include "macros.hpp"
#include "opcode.hpp"
#include "unicodeString.hpp"

namespace Tang {
  class TangBase;
  class AstNode;

  /**
   * Contains the Opcodes of a compiled program.
   */
  using Bytecode = std::vector<Tang::uinteger_t>;

  /**
   * Map of Opcodes to a pair of offsets, with the first position
   * being the Bytecode offset, and the second position being the position of
   * the Opcode relative to the other Opcodes (e.g., the Nth position).
   */
  using OpcodeOffsets = std::map<Opcode, std::vector<std::pair<size_t, size_t>>>;

  /**
   * Vector of Opcodes in positional order.  Each entry is a pair, specifying
   * the Opcode and the Bytecode offset.
   */
  using OpcodePositions = std::vector<std::pair<Opcode, size_t>>;

  /**
   * Map of Bytecode offsets to a string annotation.
   */
  using OpcodeAnnotations = std::map<size_t, std::string>;
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
     * @param tang A pointer to the base Tang class.
     */
    Program(const std::string & code, CodeType codeType, std::shared_ptr<Tang::TangBase> tang);

    /**
     * Create a compiled program using the provided code.
     *
     * @param code An istream to the code to be compiled.
     * @param codeType Whether the code is a `Script` or `Template`.
     * @param tang A pointer to the base Tang class.
     */
    Program(std::istream & code, CodeType codeType, std::shared_ptr<Tang::TangBase> tang);

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
     * Add a Tang::uinteger_t to the Bytecode.
     *
     * @param op The value to add to the Bytecode.
     * @return The size of the bytecode structure.
     */
    size_t addBytecode(Tang::uinteger_t);

    /**
     * Get the Bytecode vector.
     * 
     * @return The Bytecode vector.
     */
    const Bytecode & getBytecode();

    /**
     * Execute the program's Bytecode, and return the execution Context.
     *
     * A default ContextData will be generated for the execution.
     *
     * @return The execution Context.
     */
    Context execute();

    /**
     * Execute the program's Bytecode, and return the execution Context.
     *
     * @param data The default data to be made available to the execution
     *   Context.
     * @return The execution Context.
     */
    Context execute(ContextData && data);

    /**
     * Set the target address of a Jump opcode.
     *
     * @param opcodeAddress The location of the jump statement.
     * @param jumpTarget The address to jump to.
     * @return Whether or not the jumpTarget was set.
     */
    bool setJumpTarget(size_t opcodeAddress, Tang::uinteger_t jumpTarget);

    /**
     * Set the stack details of a function declaration.
     *
     * @param opcodeAddress The location of the FUNCTION opcode.
     * @param argc The argument count to set.
     * @param targetPC The bytecode address of the start of the function.
     */
    bool setFunctionStackDeclaration(size_t opcodeAddress, uinteger_t argc, uinteger_t targetPC);

    /**
     * Create a new compile/execute environment stack entry.
     *
     * @param ast The ast node from which this new environment will be formed.
     */
    void pushEnvironment(const std::shared_ptr<AstNode> & ast);

    /**
     * Remove a compile/execute environment stack entry.
     */
    void popEnvironment();

    /**
     * Add an identifier to the environment.
     *
     * @param name The variable to add to the environment.
     * @param position If provided, the desired position to place the
     *   identifier.
     */
    void addIdentifier(const std::string & name, std::optional<size_t> position = {});

    /**
     * Get the identifier map of the current environment.
     *
     * @return A map of each identifer name to its stack position within the
     *   current environment.
     */
    const std::map<std::string, size_t>& getIdentifiers() const;

    /**
     * Add a library alias to the environment.
     *
     * @param name The library alias to add to the environment.
     */
    void addLibraryAlias(const std::string & name);

    /**
     * Get the library alias map of the current environment.
     *
     * @return A map of each library alias to its stack position within the
     *   current environment.
     */
    const std::map<std::string, uinteger_t> & getLibraryAliases() const;

    /**
     * Indicate that an identifier will be altered within the associated scope.
     *
     * @param name The identifier name.
     */
    void addIdentifierAssigned(const std::string & name);

    /**
     * Get the set of identifiers that will be assigned in the current scope.
     *
     * @return A set of identifier names that have been identified as the
     *   target of an assignment operator within the current scope.
     */
    const std::set<std::string>& getIdentifiersAssigned() const;

    /**
     * Add a string to the environment.
     *
     * @param name The variable to add to the environment.
     * @param type The UnicodeString::Type of the string.
     */
    void addString(const std::string & name, UnicodeString::Type);

    /**
     * Get the string map of the current environment.
     *
     * @return A map of each identifer name to its stack position within the
     *   current environment.
     */
    const std::map<std::pair<std::string, UnicodeString::Type>, size_t>& getStrings() const;

    /**
     * Names of the functions that are declared in a previous or the current
     * scope.
     */
    std::vector<std::set<std::string>> functionsCollected;

    /**
     * Key/value pair of the function declaration information.
     *
     * The key is the name of the function.
     * The value is a `pair` of the `argc` value and the `targetPC` value.
     */
    std::map<std::string, std::pair<uinteger_t, uinteger_t>> functionsDeclared;

    /**
     * For each function name, a list of Bytecode addresses that need to be
     * replaced by a function definition.
     */
    std::map<std::string, std::vector<Tang::uinteger_t>> functionStackDeclarations;

    /**
     * Increase the `break` environment stack, so that we can handle nested
     * break-supporting structures.
     */
    void pushBreakStack();

    /**
     * Add the Bytecode location of a `break` statement, to be set when the
     * final target is known at a later time.
     *
     * @param location The offset location of the `break` bytecode.
     */
    void addBreak(size_t location);

    /**
     * For all `continue` bytecode locations collected by Tang::addContinue,
     * set the target pc to `target`.
     *
     * @param target The target bytecode offset that the `continue` should
     *   jump to.
     */
    void popBreakStack(size_t target);

    /**
     * Increase the `continue` environment stack, so that we can handle nested
     * continue-supporting structures.
     */
    void pushContinueStack();

    /**
     * Add the Bytecode location of a `continue` statement, to be set when the
     * final target is known at a later time.
     *
     * @param location The offset location of the `continue` bytecode.
     */
    void addContinue(size_t location);

    /**
     * For all `continue` bytecode locations collected by Tang::addContinue,
     * set the target pc to `target`.
     *
     * @param target The target bytecode offset that the `continue` should
     *   jump to.
     */
    void popContinueStack(size_t target);

    /**
     * Set a bytecode annotation.
     *
     * @param offset The bytecode offset to associate with the annotation.
     * @param annotation The annotation for the bytecode offset.
     */
    void setAnnotation(size_t offset, const std::string & annotation);

    /**
     * Get the bytecode annotations.
     *
     * @result A map of bytecode offsets to their associated annotation.
     */
    const OpcodeAnnotations & getAnnotations() const;

  private:
    /**
     * A pointer to the base Tang class.
     */
    std::shared_ptr<Tang::TangBase> tang;

    /**
     * Stack of mappings of identifiers to their stack locations.
     */
    std::vector<std::map<std::string, size_t>> identifierStack;

    /**
     * Stack of library aliases that are used in the program.
     */
    std::vector<std::map<std::string, uinteger_t>> libraryAliasStack;

    /**
     * Stack of sets of identifiers that are the target of an assignment
     * statement within the associated scope.
     */
    std::vector<std::set<std::string>> identifiersAssignedStack;

    /**
     * Stack of mappings of strings to their stack locations.
     */
    std::vector<std::map<std::pair<std::string, UnicodeString::Type>, size_t>> stringStack;

    /**
     * Stack of a collection of `break` statement locations.
     */
    std::vector<std::set<size_t>> breakStack;

    /**
     * Stack of a collection of `continue` statement locations.
     */
    std::vector<std::set<size_t>> continueStack;

    /**
     * Parse the code into an AST.
     */
    void parse();

    /**
     * Compile the AST into Bytecode.
     */
    void compile();

    /**
     * Analyze the current Bytecode.
     */
    std::pair<OpcodeOffsets, OpcodePositions> analyze() const;

    /**
     * Optimize the Bytecode.
     */
    void optimize();

    /**
     * The code supplied when the Program was instantiated.
     */
    std::string code;

    /**
     * An optional istream which supplied the code.
     */
    std::optional<std::istream *> istreamCode;

    /**
     * The type of code that was supplied when the Program was instantiated.
     */
    CodeType codeType;

    /**
     * A pointer to the AST, if parsing was successful.
     */
    std::shared_ptr<AstNode> ast;

    /**
     * The Bytecode of the compiled program.
     */
    Bytecode bytecode;

    /**
     * The result of the Program compilation.
     */
    std::optional<GarbageCollected> result;

    /**
     * Bytecode annotations.
     */
     OpcodeAnnotations annotations;
  };
}

#endif // TANG_PROGRAM_HPP

