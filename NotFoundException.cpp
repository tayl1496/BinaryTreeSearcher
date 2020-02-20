#include <stdexcept>
#include <string>
#include "NotFoundException.h"

NotFoundException::NotFoundException(const std::string& message)
  : std::logic_error(message.c_str() )
{
}

NotFoundException::~NotFoundException()
noexcept {
}
