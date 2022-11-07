/**
 * @file
 * Declare the Tang::ComputedExpressionString class.
 */

#ifndef TANG_COMPUTEDEXPRESSIONSTRING_HPP
#define TANG_COMPUTEDEXPRESSIONSTRING_HPP

#include "computedExpression.hpp"

namespace Tang {
  /**
   * Represents a String that is the result of a computation.
   */
  class ComputedExpressionString : public ComputedExpression {
    public:
      /**
       * Construct a String result.
       *
       * @param val The string value.
       */
      ComputedExpressionString(std::string val);

      virtual std::string dump() const override;
      GarbageCollected makeCopy() const override;
      virtual bool is_equal(const string & val) const override;
      virtual GarbageCollected __add(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __not() const override;
      virtual GarbageCollected __lessThan(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __equal(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __boolean() const override;
      virtual GarbageCollected __string() const override;

    private:
      /**
       * The string value.
       */
      std::string val;
  };
}

#endif // TANG_COMPUTEDEXPRESSIONSTRING_HPP

