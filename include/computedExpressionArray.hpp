/**
 * @file
 * Declare the Tang::ComputedExpressionArray class.
 */

#ifndef TANG_COMPUTEDEXPRESSIONARRAY_HPP
#define TANG_COMPUTEDEXPRESSIONARRAY_HPP

#include <vector>
#include "computedExpression.hpp"

namespace Tang {
  /**
   * Represents an Array that is the result of a computation.
   */
  class ComputedExpressionArray : public ComputedExpression {
    public:
      /**
       * Construct an Array result.
       *
       * @param val The integer value.
       */
      ComputedExpressionArray(std::vector<Tang::GarbageCollected> contents);

      virtual std::string dump() const override;
      virtual bool isCopyNeeded() const override;
      GarbageCollected makeCopy() const override;
      virtual GarbageCollected __index(const GarbageCollected & index) const override;
      virtual GarbageCollected __slice(const GarbageCollected & begin, const GarbageCollected & end, const GarbageCollected & skip) const override;
      virtual GarbageCollected __getIterator(const GarbageCollected & collection) const override;
      virtual GarbageCollected __iteratorNext(size_t index) const override;
      virtual GarbageCollected __assign_index(const GarbageCollected & index, const GarbageCollected & value) override;
      virtual GarbageCollected __string() const override;

      /**
       * Return the contents of this object.
       *
       * @return The contents of this object.
       */
      const std::vector<Tang::GarbageCollected> & getContents() const;

      /**
       * Append an item to the contents of this array object.
       *
       * @param item The value to append to the this array.
       */
      void append(const Tang::GarbageCollected & item);

      /**
       * Return the member functions implemented for this particular
       * expression type.
       *
       * @return The member functions implemented.
       */
      static NativeBoundFunctionMap getMethods();

    private:
      /**
       * The array contents.
       */
      std::vector<Tang::GarbageCollected> contents;
  };
}

#endif // TANG_COMPUTEDEXPRESSIONARRAY_HPP

