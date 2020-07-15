#pragma once

#include <memory>

template<typename T>
class Pimpl
{
  // FIXME compiler time error:
  // /usr/include/c++/7/bits/unique_ptr.h:76:22:
  //   error: invalid application of ‘sizeof’ to incomplete type
  //  ‘Person::PersonImpl’
  //   static_assert(sizeof(_Tp)>0,
  //std::unique_ptr<T> impl_;
  T* impl_;
 public:
  Pimpl() : impl_{new T{} } {}

  template<typename... Args>
  Pimpl(Args&& ...args) : impl_{new T{std::forward<Args>(args)...} } {}

  virtual ~Pimpl() { if (impl_) delete impl_; }

  T* operator->() { return impl_; }
  T& operator*()  { return *impl_; }
};
