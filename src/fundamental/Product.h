#ifndef DESIGN_PATTERNS_CPP_SRC_FUNDAMENTAL_PRODUCT_H_
#define DESIGN_PATTERNS_CPP_SRC_FUNDAMENTAL_PRODUCT_H_

#include <string>
#include <vector>

enum class Color { red, green, blue };
enum class Size { small, medium, large };

struct Product {
  std::string name;
  Color color;
  Size size;
};

template<typename T>
struct FilterSpec {
  FilterSpec() {}
  virtual ~FilterSpec() {}

  virtual bool match(const T *) const = 0;
};

template<typename T>
struct AndFilterSpec : FilterSpec<T> {
  FilterSpec<T> &first;
  FilterSpec<T> &second;

  AndFilterSpec(FilterSpec<T> &first, FilterSpec<T> &second)
      : first(first), second(second) {}

  bool match(const T *t) const {
    return first.match(t) && second.match(t);
  }
};

template<typename T>
struct AndFilterSpec<T> operator&&(FilterSpec<T> first,
                                   FilterSpec<T> second) {
  return {first, second};
}

template<typename T>
struct Filter {
  Filter() {}
  virtual ~Filter() {}

  virtual std::vector<T *> filter(std::vector<T *> &items,
                                  FilterSpec<T> &spec) = 0;
};

#endif //DESIGN_PATTERNS_CPP_SRC_FUNDAMENTAL_PRODUCT_H_

