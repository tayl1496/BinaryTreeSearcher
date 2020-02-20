#ifndef NOT_FOUND_EXCEPTION_
#define NOT_FOUND_EXCEPTION_

#include <stdexcept>
#include <string>

class NotFoundException : public std::logic_error
{
 public:
  explicit NotFoundException(const std::string& message = "Not found");

  virtual ~NotFoundException() noexcept;
};

#endif
