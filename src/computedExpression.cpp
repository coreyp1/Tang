/**
 * @file
 * Define the Tang::ComputedExpression class.
 */

#include <typeinfo>
#include "computedExpression.hpp"
#include "computedExpressionBoolean.hpp"
#include "computedExpressionString.hpp"
#include "computedExpressionNativeBoundFunction.hpp"
#include "computedExpressionError.hpp"
#include "tangBase.hpp"

using namespace std;
using namespace Tang;

ComputedExpression::~ComputedExpression() {}

string ComputedExpression::dump() const {
  // Because this is a virtual function, we must ensure that the type is
  // actually ComputedExpression, and not a derived type that forgot to
  // override the virtual method.
  return typeid(*this) == typeid(ComputedExpression)
    ? "null"
    : "UNKNOWN";
}

string ComputedExpression::__asCode() const {
  return this->dump();
}

bool ComputedExpression::isCopyNeeded() const {
  // By default, we will not request a copy of this ComputedExpression.
  return false;
}

GarbageCollected ComputedExpression::makeCopy() const {
  return GarbageCollected::make<ComputedExpression>();
}

bool ComputedExpression::is_equal([[maybe_unused]] const Tang::integer_t & val) const {
  return false;
}

bool ComputedExpression::is_equal([[maybe_unused]] const Tang::float_t & val) const {
  return false;
}

bool ComputedExpression::is_equal([[maybe_unused]] const bool & val) const {
  return typeid(*this) == typeid(ComputedExpression)
    ? val == false
    : false;
}

bool ComputedExpression::is_equal([[maybe_unused]] const string & val) const {
  return false;
}

bool ComputedExpression::is_equal([[maybe_unused]] const nullptr_t & val) const {
  // Because this is a virtual function, we must ensure that the type is
  // actually ComputedExpression, and not a derived type that forgot to
  // override the virtual method.
  return typeid(*this) == typeid(ComputedExpression)
    ? true
    : false;
}

bool ComputedExpression::is_equal([[maybe_unused]] const Error & val) const {
  return false;
}

GarbageCollected ComputedExpression::__assign_index([[maybe_unused]] const GarbageCollected & index, [[maybe_unused]] const GarbageCollected & value) {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to assign this value to the index location."});
}

GarbageCollected ComputedExpression::__add([[maybe_unused]] const GarbageCollected & rhs) const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to add these values."});
}

GarbageCollected ComputedExpression::__subtract([[maybe_unused]] const GarbageCollected & rhs) const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to subtract these values."});
}

GarbageCollected ComputedExpression::__multiply([[maybe_unused]] const GarbageCollected & rhs) const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to multiply these values."});
}

GarbageCollected ComputedExpression::__divide([[maybe_unused]] const GarbageCollected & rhs) const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to divide these values."});
}

GarbageCollected ComputedExpression::__modulo([[maybe_unused]] const GarbageCollected & rhs) const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to modulo these values."});
}

GarbageCollected ComputedExpression::__negative() const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to negate this value."});
}

GarbageCollected ComputedExpression::__not() const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to compute the logical not of this value."});
}

GarbageCollected ComputedExpression::__lessThan([[maybe_unused]] const GarbageCollected & rhs) const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to compare these values."});
}

GarbageCollected ComputedExpression::__equal([[maybe_unused]] const GarbageCollected & rhs) const {
  // Because this is a virtual function, we must ensure that the type is
  // actually ComputedExpression, and not a derived type that forgot to
  // override the virtual method.
  if (typeid(*this) == typeid(ComputedExpression)) {
    if (typeid(*rhs) == typeid(ComputedExpression)) {
      return GarbageCollected::make<ComputedExpressionBoolean>(true);
    }
    return GarbageCollected::make<ComputedExpressionBoolean>(false);
  }
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to compare these values."});
}

GarbageCollected ComputedExpression::__period([[maybe_unused]] const GarbageCollected & member, [[maybe_unused]] shared_ptr<TangBase> & tang) const {
  if (typeid(*member) == typeid(ComputedExpressionString)) {
    auto & objectMethods = tang->getObjectMethods();
    auto thisType = type_index(typeid(*this));
    if (objectMethods.count(thisType)) {
      auto & methods = objectMethods.at(thisType);
      string name = static_cast<ComputedExpressionString &>(*member).dump();
      if (methods.count(name)) {
        auto & fn = methods.at(name);
        return GarbageCollected::make<ComputedExpressionNativeBoundFunction>(fn.second, fn.first, type_index(typeid(*this)));
      }
    }
  }

  return GarbageCollected::make<ComputedExpressionError>(Error{"Member not found."});
}

GarbageCollected ComputedExpression::__index([[maybe_unused]] const GarbageCollected & index) const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to index this expression."});
}

GarbageCollected ComputedExpression::__slice([[maybe_unused]] const GarbageCollected & begin, [[maybe_unused]] const GarbageCollected & end, [[maybe_unused]] const GarbageCollected & skip) const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to slice this expression."});
}

GarbageCollected ComputedExpression::__getIterator([[maybe_unused]] const GarbageCollected & collection) const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to iterate over this expression."});
}

GarbageCollected ComputedExpression::__iteratorNext([[maybe_unused]] size_t index) const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to iterate over this expression."});
}

GarbageCollected ComputedExpression::__integer() const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to cast this value to an integer."});
}

GarbageCollected ComputedExpression::__float() const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to cast this value to a float."});
}

GarbageCollected ComputedExpression::__boolean() const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to cast this value to a boolean."});
}

GarbageCollected ComputedExpression::__string() const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to cast this value to a string."});
}

