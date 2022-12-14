/**
 * @file
 * Declare the Tang::ComputedExpressionInteger class.
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
      ComputedExpressionInteger(Tang::integer_t val);

      virtual std::string dump() const override;
      GarbageCollected makeCopy() const override;
      virtual bool is_equal(const Tang::integer_t & val) const override;
      virtual bool is_equal(const Tang::float_t & val) const override;
      virtual bool is_equal(const bool & val) const override;
      virtual GarbageCollected __add(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __subtract(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __multiply(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __divide(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __modulo(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __negative() const override;
      virtual GarbageCollected __not() const override;
      virtual GarbageCollected __lessThan(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __equal(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __integer() const override;
      virtual GarbageCollected __float() const override;
      virtual GarbageCollected __boolean() const override;
      virtual GarbageCollected __string() const override;

      /**
       * Helper function to get the value associated with this expression.
       *
       * @return The value associated with this expression.
       */
      Tang::integer_t getValue() const;

    private:
      /**
       * The integer value.
       */
      Tang::integer_t val;
  };
}

#endif // TANG_COMPUTEDEXPRESSIONINTEGER_HPP

