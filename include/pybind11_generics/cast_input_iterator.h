#ifndef PYBIND11_GENERICS_CAST_INPUT_ITERATOR_H
#define PYBIND11_GENERICS_CAST_INPUT_ITERATOR_H

#include <iterator>

#include <pybind11/pybind11.h>

#include <pybind11_generics/cast.h>

namespace py = pybind11;

namespace pybind11_generics {

template <typename T, typename WrapIter> class cast_input_iterator {
public:
  using difference_type = std::size_t;
  using iterator_category = std::input_iterator_tag;
  using value_type = T;
  using reference = value_type &;
  using pointer = value_type *;
  using It = cast_input_iterator;

  struct arrow_proxy {
    value_type value;

    explicit arrow_proxy(value_type &&value) : value(std::move(value)) {}
    const pointer operator->() const { return &value; }
  };

protected:
  WrapIter iter_;

public:
  cast_input_iterator() = default;

  explicit cast_input_iterator(WrapIter &&iter) : iter_(std::move(iter)) {}

  friend bool operator==(const It &a, const It &b) {
    return a.iter_ == b.iter_;
  }
  friend bool operator!=(const It &a, const It &b) { return !(a == b); }

  const value_type operator*() const { return cast_from_handle<T>(*iter_); }
  arrow_proxy operator->() const { return arrow_proxy(**this); }

  It &operator++() {
    ++iter_;
    return *this;
  }
  It operator++(int) {
    auto copy = *this;
    ++(*this);
    return copy;
  }
};

} // namespace pybind11_generics

#endif
