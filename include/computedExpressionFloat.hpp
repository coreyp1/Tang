/**
 * @file
 * Declare the Tang::ComputedExpressionFloat class.
 */

#ifndef TANG_COMPUTEDEXPRESSIONFLOAT_HPP
#define TANG_COMPUTEDEXPRESSIONFLOAT_HPP

#include "computedExpression.hpp"

namespace Tang {
  /**
   * Represents a Float that is the result of a computation.
   */
  class ComputedExpressionFloat: public ComputedExpression {
    public:
      /**
       * Construct a Float result.
       *
       * @param val The float value.
       */
      ComputedExpressionFloat(Tang::float_t val);

      virtual std::string dump() const override;
      GarbageCollected makeCopy() const override;
      virtual bool is_equal(const Tang::integer_t & val) const override;
      virtual bool is_equal(const Tang::float_t & val) const override;
      virtual bool is_equal(const bool & val) const override;
      virtual GarbageCollected __add(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __subtract(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __multiply(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __divide(const GarbageCollected & rhs) const override;
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
      Tang::float_t getValue() const;

    private:
      /**
       * The float value.
       */
      Tang::float_t val;
  };
}

#endif // TANG_COMPUTEDEXPRESSIONFLOAT_HPP

