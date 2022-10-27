/**
 * @file
 */

#ifndef TANG_ASTNODEINTEGER_HPP
#define TANG_ASTNODEINTEGER_HPP

#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents an integer literal.
   *
   * Integers are represented by the `int64_t` type, and so are limited in
   * range by that of the underlying type.
   */
  class AstNodeInteger : public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param number The number to represent.
     * @param loc The location associated with the expression.
     * @location The location associated with this node.
     */
    AstNodeInteger(int64_t number, Tang::location loc) : AstNode(loc), val{number} {}

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual AstNode * makeCopy() const override;

  private:
    /**
     * The integer value being stored.
     */
    int64_t val;
  };
}

#endif // TANG_ASTNODEINTEGER_HPP
