#ifndef PYBIND11_GENERICS_DICT_H
#define PYBIND11_GENERICS_DICT_H

#include <utility>

#include <pybind11_generics/cast_input_iterator.h>
#include <pybind11_generics/type_name.h>

namespace py = pybind11;

namespace pybind11_generics {

template <typename K, typename V, typename WrapIter>
class dict_cast_input_iterator
    : public cast_input_iterator<std::pair<K, V>, WrapIter> {
private:
  using iter_base = cast_input_iterator<std::pair<K, V>, WrapIter>;

public:
  using difference_type = typename iter_base::difference_type;
  using iterator_category = typename iter_base::iterator_category;
  using value_type = typename iter_base::value_type;
  using reference = typename iter_base::reference;
  using pointer = typename iter_base::pointer;

  using iter_base::iter_base;

  value_type operator*() const {
    auto py_pair = *(this->iter_);
    return std::make_pair(py_pair.first.template cast<K>(),
                          py_pair.second.template cast<V>());
  }
};

using dict_base = py::dict;

template <typename K, typename V> class Dict : public dict_base {
public:
  using value_type = std::pair<K, V>;
  using base_iter_type = py::detail::dict_iterator;
  using const_iterator = dict_cast_input_iterator<K, V, base_iter_type>;

  using dict_base::contains;
  using dict_base::operator[];
  using dict_base::dict_base;

  value_type operator[](const K &key) const {
    return dict_base::operator[](py::cast(key)).template cast<V>();
  }
  const_iterator begin() const { return const_iterator(dict_base::begin()); }
  const_iterator end() const { return const_iterator(dict_base::end()); }
  bool contains(const K &key) const {
    return dict_base::contains(py::cast(key));
  }
};

}; // namespace pybind11_generics

#endif