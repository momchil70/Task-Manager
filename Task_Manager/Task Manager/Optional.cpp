#include "Optional.h"

void OptionalDate::clear()
{
    value = nullptr;
}

OptionalDate& OptionalDate::operator=(OptionalDate&& other) noexcept
{
    value = other.value;
    other.value = nullptr;

    return *this;
}

OptionalDate& OptionalDate::operator=(const OptionalDate& other)
{
    value = other.value;

    return *this;
}

bool OptionalDate::hasValue() const
{
    return value;
}

const Date& OptionalDate::getValue() const
{
    if (!hasValue()) {
        throw std::logic_error("No value in optional");
    }

    return *value;
}

void OptionalDate::setValue(const Date* newValue)
{
    value = newValue;
}
