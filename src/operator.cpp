#include "operator.hpp"
#include "type.hpp"

using namespace njnr;

/**
 * @brief Construct a new TSOperatorType:: TSOperatorType object
 *
 * @param op string with operator
 */
TSOperatorType::TSOperatorType(const std::string& op) : op{op} {}

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
 * @brief is an LVal
 *
 * @return false
 */
const bool TSOperatorType::getLVal() const noexcept
{
   return false;
}

/**
 * @brief is a numeric value?
 *
 * @return true
 */
const bool TSOperatorType::getNumeric() const noexcept
{
   return true;
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
