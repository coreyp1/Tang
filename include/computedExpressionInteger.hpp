/**
 * @file
 */

#ifndef TANG_COMPUTEDEXPRESSIONINTEGER_HPP
#define TANG_COMPUTEDEXPRESSIONINTEGER_HPP

#include "computedExpression.hpp"

namespace Tang {
  /**
   * Represents an Integer that is the result of a computation.
   */
  class ComputedExpressionInteger : public ComputedExpression {
    public:
      /**
       * Construct an Integer result.
       *
       * @param val The integer value.
       */
      ComputedExpressionInteger(int64_t val);

      virtual std::string dump() const override;
      ComputedExpression * makeCopy() const override;
      virtual bool is_equal(const int & val) const override;
      virtual bool is_equal(const double & val) const override;
      virtual GarbageCollected __add(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __subtract(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __multiply(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __divide(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __modulo(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __negative() const override;

      friend class ComputedExpressionFloat;

    private:
      /**
       * The integer value.
       */
      int64_t val;
  };
}

#endif // TANG_COMPUTEDEXPRESSIONINTEGER_HPP

