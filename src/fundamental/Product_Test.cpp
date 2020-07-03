#include <gtest/gtest.h>

#include <algorithm>

#include "fundamental/Product.h"

using namespace std;

struct ColorSpecFilter : FilterSpec<Product> {
  Color color;

  ColorSpecFilter(Color color) : color(color) {}

  bool match(const Product *t) const override {
    return t->color == color;
  }
};

struct SizeSpecFilter : FilterSpec<Product> {
  Size size;

  SizeSpecFilter(Size size) : size(size) {}

  bool match(const Product *t) const override {
    return t->size == size;
  }
};

struct ProductFilter : Filter<Product> {
  std::vector<Product *> filter(std::vector<Product *> &items,
                                FilterSpec<Product> &spec) override {
    std::vector<Product *> ret;
    for (const auto item : items) {
      if (spec.match(item)) {
        ret.push_back(item);
      }
    }
    return ret;
  }
};

TEST(Product_Test, ColorFilter) {
  Product p1{"Apple", Color::red, Size::small};
  Product p2{"Tree", Color::green, Size::large};
  Product p3{"Phone", Color::blue, Size::medium};

  vector<Product *> items{&p1, &p2, &p3};

  ColorSpecFilter filter_spec(Color::red);
  ProductFilter filter;

  auto filtered = filter.filter(items, filter_spec);

  EXPECT_EQ(filtered.size(), 1);
  EXPECT_EQ(filtered[0]->name, "Apple");
  EXPECT_EQ(filtered[0]->color, Color::red);
  EXPECT_EQ(filtered[0]->size, Size::small);
}

TEST(Product_Test, SizeFilter) {
  Product p1{"Apple", Color::red, Size::small};
  Product p2{"Tree", Color::green, Size::large};
  Product p3{"House", Color::blue, Size::large};

  vector<Product *> items{&p1, &p2, &p3};

  SizeSpecFilter filter_spec(Size::large);
  ProductFilter filter;

  auto filtered = filter.filter(items, filter_spec);

  EXPECT_EQ(filtered.size(), 2);
  EXPECT_EQ(filtered[0]->name, "Tree");
  EXPECT_EQ(filtered[0]->color, Color::green);
  EXPECT_EQ(filtered[0]->size, Size::large);
  EXPECT_EQ(filtered[1]->name, "House");
  EXPECT_EQ(filtered[1]->color, Color::blue);
  EXPECT_EQ(filtered[1]->size, Size::large);
}

TEST(Product_Test, AndFilterSpec) {
  Product p1{"Apple", Color::red, Size::small};
  Product p2{"Tree", Color::green, Size::large};
  Product p3{"House", Color::blue, Size::large};

  vector<Product *> items{&p1, &p2, &p3};

  ColorSpecFilter color_spec(Color::blue);
  SizeSpecFilter size_spec(Size::large);
  ProductFilter filter;

  auto color_and_size = AndFilterSpec<Product>(color_spec, size_spec);

  auto filtered = filter.filter(items, color_and_size);

  EXPECT_EQ(filtered.size(), 1);
  EXPECT_EQ(filtered[0]->name, "House");
  EXPECT_EQ(filtered[0]->color, Color::blue);
  EXPECT_EQ(filtered[0]->size, Size::large);
}