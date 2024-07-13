#include "operator.hpp"
#include "type.hpp"

using namespace njnr;

/**
 * @brief generic Type class toString() implementation
 *
 * @return const std::string
 */
const std::string TSOperatorType::toString() noexcept
{
   return op;
}



/**
 * @brief get class Type()'s stored value stored as string
 *
 * @return const std::string
 */
const std::string TSOperatorType::getTypeValue() const noexcept
{
   return op;
}

/**
 * @brief return type of instance of class Type()
 *
 * @return const njnr::type
 */
const njnr::type TSOperatorType::getType() const noexcept
{
   return njnr::type::OPERATOR;
}
