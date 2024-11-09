#include "autocxxgen_ffi.h"
#include "idalib.hpp"
#include "types.h"
#include "bookmarks_extras.h"
#include "bytes_extras.h"
#include "comments_extras.h"
#include "entry_extras.h"
#include "func_extras.h"
#include "loader_extras.h"
#include "inf_extras.h"
#include "kernwin_extras.h"
#include "ph_extras.h"
#include "segm_extras.h"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <new>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

namespace rust {
inline namespace cxxbridge1 {
// #include "rust/cxx.h"

#ifndef CXXBRIDGE1_PANIC
#define CXXBRIDGE1_PANIC
template <typename Exception>
void panic [[noreturn]] (const char *msg);
#endif // CXXBRIDGE1_PANIC

struct unsafe_bitcopy_t;

namespace {
template <typename T>
class impl;
} // namespace

class Opaque;

template <typename T>
::std::size_t size_of();
template <typename T>
::std::size_t align_of();

#ifndef CXXBRIDGE1_RUST_STRING
#define CXXBRIDGE1_RUST_STRING
class String final {
public:
  String() noexcept;
  String(const String &) noexcept;
  String(String &&) noexcept;
  ~String() noexcept;

  String(const std::string &);
  String(const char *);
  String(const char *, std::size_t);
  String(const char16_t *);
  String(const char16_t *, std::size_t);

  static String lossy(const std::string &) noexcept;
  static String lossy(const char *) noexcept;
  static String lossy(const char *, std::size_t) noexcept;
  static String lossy(const char16_t *) noexcept;
  static String lossy(const char16_t *, std::size_t) noexcept;

  String &operator=(const String &) &noexcept;
  String &operator=(String &&) &noexcept;

  explicit operator std::string() const;

  const char *data() const noexcept;
  std::size_t size() const noexcept;
  std::size_t length() const noexcept;
  bool empty() const noexcept;

  const char *c_str() noexcept;

  std::size_t capacity() const noexcept;
  void reserve(size_t new_cap) noexcept;

  using iterator = char *;
  iterator begin() noexcept;
  iterator end() noexcept;

  using const_iterator = const char *;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  bool operator==(const String &) const noexcept;
  bool operator!=(const String &) const noexcept;
  bool operator<(const String &) const noexcept;
  bool operator<=(const String &) const noexcept;
  bool operator>(const String &) const noexcept;
  bool operator>=(const String &) const noexcept;

  void swap(String &) noexcept;

  String(unsafe_bitcopy_t, const String &) noexcept;

private:
  struct lossy_t;
  String(lossy_t, const char *, std::size_t) noexcept;
  String(lossy_t, const char16_t *, std::size_t) noexcept;
  friend void swap(String &lhs, String &rhs) noexcept { lhs.swap(rhs); }

  std::array<std::uintptr_t, 3> repr;
};
#endif // CXXBRIDGE1_RUST_STRING

#ifndef CXXBRIDGE1_RUST_SLICE
#define CXXBRIDGE1_RUST_SLICE
namespace detail {
template <bool>
struct copy_assignable_if {};

template <>
struct copy_assignable_if<false> {
  copy_assignable_if() noexcept = default;
  copy_assignable_if(const copy_assignable_if &) noexcept = default;
  copy_assignable_if &operator=(const copy_assignable_if &) &noexcept = delete;
  copy_assignable_if &operator=(copy_assignable_if &&) &noexcept = default;
};
} // namespace detail

template <typename T>
class Slice final
    : private detail::copy_assignable_if<std::is_const<T>::value> {
public:
  using value_type = T;

  Slice() noexcept;
  Slice(T *, std::size_t count) noexcept;

  template <typename C>
  explicit Slice(C& c) : Slice(c.data(), c.size()) {}

  Slice &operator=(const Slice<T> &) &noexcept = default;
  Slice &operator=(Slice<T> &&) &noexcept = default;

  T *data() const noexcept;
  std::size_t size() const noexcept;
  std::size_t length() const noexcept;
  bool empty() const noexcept;

  T &operator[](std::size_t n) const noexcept;
  T &at(std::size_t n) const;
  T &front() const noexcept;
  T &back() const noexcept;

  Slice(const Slice<T> &) noexcept = default;
  ~Slice() noexcept = default;

  class iterator;
  iterator begin() const noexcept;
  iterator end() const noexcept;

  void swap(Slice &) noexcept;

private:
  class uninit;
  Slice(uninit) noexcept;
  friend impl<Slice>;
  friend void sliceInit(void *, const void *, std::size_t) noexcept;
  friend void *slicePtr(const void *) noexcept;
  friend std::size_t sliceLen(const void *) noexcept;

  std::array<std::uintptr_t, 2> repr;
};

template <typename T>
class Slice<T>::iterator final {
public:
  using iterator_category = std::random_access_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = typename std::add_pointer<T>::type;
  using reference = typename std::add_lvalue_reference<T>::type;

  reference operator*() const noexcept;
  pointer operator->() const noexcept;
  reference operator[](difference_type) const noexcept;

  iterator &operator++() noexcept;
  iterator operator++(int) noexcept;
  iterator &operator--() noexcept;
  iterator operator--(int) noexcept;

  iterator &operator+=(difference_type) noexcept;
  iterator &operator-=(difference_type) noexcept;
  iterator operator+(difference_type) const noexcept;
  iterator operator-(difference_type) const noexcept;
  difference_type operator-(const iterator &) const noexcept;

  bool operator==(const iterator &) const noexcept;
  bool operator!=(const iterator &) const noexcept;
  bool operator<(const iterator &) const noexcept;
  bool operator<=(const iterator &) const noexcept;
  bool operator>(const iterator &) const noexcept;
  bool operator>=(const iterator &) const noexcept;

private:
  friend class Slice;
  void *pos;
  std::size_t stride;
};

template <typename T>
Slice<T>::Slice() noexcept {
  sliceInit(this, reinterpret_cast<void *>(align_of<T>()), 0);
}

template <typename T>
Slice<T>::Slice(T *s, std::size_t count) noexcept {
  assert(s != nullptr || count == 0);
  sliceInit(this,
            s == nullptr && count == 0
                ? reinterpret_cast<void *>(align_of<T>())
                : const_cast<typename std::remove_const<T>::type *>(s),
            count);
}

template <typename T>
T *Slice<T>::data() const noexcept {
  return reinterpret_cast<T *>(slicePtr(this));
}

template <typename T>
std::size_t Slice<T>::size() const noexcept {
  return sliceLen(this);
}

template <typename T>
std::size_t Slice<T>::length() const noexcept {
  return this->size();
}

template <typename T>
bool Slice<T>::empty() const noexcept {
  return this->size() == 0;
}

template <typename T>
T &Slice<T>::operator[](std::size_t n) const noexcept {
  assert(n < this->size());
  auto ptr = static_cast<char *>(slicePtr(this)) + size_of<T>() * n;
  return *reinterpret_cast<T *>(ptr);
}

template <typename T>
T &Slice<T>::at(std::size_t n) const {
  if (n >= this->size()) {
    panic<std::out_of_range>("rust::Slice index out of range");
  }
  return (*this)[n];
}

template <typename T>
T &Slice<T>::front() const noexcept {
  assert(!this->empty());
  return (*this)[0];
}

template <typename T>
T &Slice<T>::back() const noexcept {
  assert(!this->empty());
  return (*this)[this->size() - 1];
}

template <typename T>
typename Slice<T>::iterator::reference
Slice<T>::iterator::operator*() const noexcept {
  return *static_cast<T *>(this->pos);
}

template <typename T>
typename Slice<T>::iterator::pointer
Slice<T>::iterator::operator->() const noexcept {
  return static_cast<T *>(this->pos);
}

template <typename T>
typename Slice<T>::iterator::reference Slice<T>::iterator::operator[](
    typename Slice<T>::iterator::difference_type n) const noexcept {
  auto ptr = static_cast<char *>(this->pos) + this->stride * n;
  return *reinterpret_cast<T *>(ptr);
}

template <typename T>
typename Slice<T>::iterator &Slice<T>::iterator::operator++() noexcept {
  this->pos = static_cast<char *>(this->pos) + this->stride;
  return *this;
}

template <typename T>
typename Slice<T>::iterator Slice<T>::iterator::operator++(int) noexcept {
  auto ret = iterator(*this);
  this->pos = static_cast<char *>(this->pos) + this->stride;
  return ret;
}

template <typename T>
typename Slice<T>::iterator &Slice<T>::iterator::operator--() noexcept {
  this->pos = static_cast<char *>(this->pos) - this->stride;
  return *this;
}

template <typename T>
typename Slice<T>::iterator Slice<T>::iterator::operator--(int) noexcept {
  auto ret = iterator(*this);
  this->pos = static_cast<char *>(this->pos) - this->stride;
  return ret;
}

template <typename T>
typename Slice<T>::iterator &Slice<T>::iterator::operator+=(
    typename Slice<T>::iterator::difference_type n) noexcept {
  this->pos = static_cast<char *>(this->pos) + this->stride * n;
  return *this;
}

template <typename T>
typename Slice<T>::iterator &Slice<T>::iterator::operator-=(
    typename Slice<T>::iterator::difference_type n) noexcept {
  this->pos = static_cast<char *>(this->pos) - this->stride * n;
  return *this;
}

template <typename T>
typename Slice<T>::iterator Slice<T>::iterator::operator+(
    typename Slice<T>::iterator::difference_type n) const noexcept {
  auto ret = iterator(*this);
  ret.pos = static_cast<char *>(this->pos) + this->stride * n;
  return ret;
}

template <typename T>
typename Slice<T>::iterator Slice<T>::iterator::operator-(
    typename Slice<T>::iterator::difference_type n) const noexcept {
  auto ret = iterator(*this);
  ret.pos = static_cast<char *>(this->pos) - this->stride * n;
  return ret;
}

template <typename T>
typename Slice<T>::iterator::difference_type
Slice<T>::iterator::operator-(const iterator &other) const noexcept {
  auto diff = std::distance(static_cast<char *>(other.pos),
                            static_cast<char *>(this->pos));
  return diff / static_cast<typename Slice<T>::iterator::difference_type>(
                    this->stride);
}

template <typename T>
bool Slice<T>::iterator::operator==(const iterator &other) const noexcept {
  return this->pos == other.pos;
}

template <typename T>
bool Slice<T>::iterator::operator!=(const iterator &other) const noexcept {
  return this->pos != other.pos;
}

template <typename T>
bool Slice<T>::iterator::operator<(const iterator &other) const noexcept {
  return this->pos < other.pos;
}

template <typename T>
bool Slice<T>::iterator::operator<=(const iterator &other) const noexcept {
  return this->pos <= other.pos;
}

template <typename T>
bool Slice<T>::iterator::operator>(const iterator &other) const noexcept {
  return this->pos > other.pos;
}

template <typename T>
bool Slice<T>::iterator::operator>=(const iterator &other) const noexcept {
  return this->pos >= other.pos;
}

template <typename T>
typename Slice<T>::iterator Slice<T>::begin() const noexcept {
  iterator it;
  it.pos = slicePtr(this);
  it.stride = size_of<T>();
  return it;
}

template <typename T>
typename Slice<T>::iterator Slice<T>::end() const noexcept {
  iterator it = this->begin();
  it.pos = static_cast<char *>(it.pos) + it.stride * this->size();
  return it;
}

template <typename T>
void Slice<T>::swap(Slice &rhs) noexcept {
  std::swap(*this, rhs);
}
#endif // CXXBRIDGE1_RUST_SLICE

#ifndef CXXBRIDGE1_RUST_BITCOPY_T
#define CXXBRIDGE1_RUST_BITCOPY_T
struct unsafe_bitcopy_t final {
  explicit unsafe_bitcopy_t() = default;
};
#endif // CXXBRIDGE1_RUST_BITCOPY_T

#ifndef CXXBRIDGE1_RUST_VEC
#define CXXBRIDGE1_RUST_VEC
template <typename T>
class Vec final {
public:
  using value_type = T;

  Vec() noexcept;
  Vec(std::initializer_list<T>);
  Vec(const Vec &);
  Vec(Vec &&) noexcept;
  ~Vec() noexcept;

  Vec &operator=(Vec &&) &noexcept;
  Vec &operator=(const Vec &) &;

  std::size_t size() const noexcept;
  bool empty() const noexcept;
  const T *data() const noexcept;
  T *data() noexcept;
  std::size_t capacity() const noexcept;

  const T &operator[](std::size_t n) const noexcept;
  const T &at(std::size_t n) const;
  const T &front() const noexcept;
  const T &back() const noexcept;

  T &operator[](std::size_t n) noexcept;
  T &at(std::size_t n);
  T &front() noexcept;
  T &back() noexcept;

  void reserve(std::size_t new_cap);
  void push_back(const T &value);
  void push_back(T &&value);
  template <typename... Args>
  void emplace_back(Args &&...args);
  void truncate(std::size_t len);
  void clear();

  using iterator = typename Slice<T>::iterator;
  iterator begin() noexcept;
  iterator end() noexcept;

  using const_iterator = typename Slice<const T>::iterator;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  void swap(Vec &) noexcept;

  Vec(unsafe_bitcopy_t, const Vec &) noexcept;

private:
  void reserve_total(std::size_t new_cap) noexcept;
  void set_len(std::size_t len) noexcept;
  void drop() noexcept;

  friend void swap(Vec &lhs, Vec &rhs) noexcept { lhs.swap(rhs); }

  std::array<std::uintptr_t, 3> repr;
};

template <typename T>
Vec<T>::Vec(std::initializer_list<T> init) : Vec{} {
  this->reserve_total(init.size());
  std::move(init.begin(), init.end(), std::back_inserter(*this));
}

template <typename T>
Vec<T>::Vec(const Vec &other) : Vec() {
  this->reserve_total(other.size());
  std::copy(other.begin(), other.end(), std::back_inserter(*this));
}

template <typename T>
Vec<T>::Vec(Vec &&other) noexcept : repr(other.repr) {
  new (&other) Vec();
}

template <typename T>
Vec<T>::~Vec() noexcept {
  this->drop();
}

template <typename T>
Vec<T> &Vec<T>::operator=(Vec &&other) &noexcept {
  this->drop();
  this->repr = other.repr;
  new (&other) Vec();
  return *this;
}

template <typename T>
Vec<T> &Vec<T>::operator=(const Vec &other) & {
  if (this != &other) {
    this->drop();
    new (this) Vec(other);
  }
  return *this;
}

template <typename T>
bool Vec<T>::empty() const noexcept {
  return this->size() == 0;
}

template <typename T>
T *Vec<T>::data() noexcept {
  return const_cast<T *>(const_cast<const Vec<T> *>(this)->data());
}

template <typename T>
const T &Vec<T>::operator[](std::size_t n) const noexcept {
  assert(n < this->size());
  auto data = reinterpret_cast<const char *>(this->data());
  return *reinterpret_cast<const T *>(data + n * size_of<T>());
}

template <typename T>
const T &Vec<T>::at(std::size_t n) const {
  if (n >= this->size()) {
    panic<std::out_of_range>("rust::Vec index out of range");
  }
  return (*this)[n];
}

template <typename T>
const T &Vec<T>::front() const noexcept {
  assert(!this->empty());
  return (*this)[0];
}

template <typename T>
const T &Vec<T>::back() const noexcept {
  assert(!this->empty());
  return (*this)[this->size() - 1];
}

template <typename T>
T &Vec<T>::operator[](std::size_t n) noexcept {
  assert(n < this->size());
  auto data = reinterpret_cast<char *>(this->data());
  return *reinterpret_cast<T *>(data + n * size_of<T>());
}

template <typename T>
T &Vec<T>::at(std::size_t n) {
  if (n >= this->size()) {
    panic<std::out_of_range>("rust::Vec index out of range");
  }
  return (*this)[n];
}

template <typename T>
T &Vec<T>::front() noexcept {
  assert(!this->empty());
  return (*this)[0];
}

template <typename T>
T &Vec<T>::back() noexcept {
  assert(!this->empty());
  return (*this)[this->size() - 1];
}

template <typename T>
void Vec<T>::reserve(std::size_t new_cap) {
  this->reserve_total(new_cap);
}

template <typename T>
void Vec<T>::push_back(const T &value) {
  this->emplace_back(value);
}

template <typename T>
void Vec<T>::push_back(T &&value) {
  this->emplace_back(std::move(value));
}

template <typename T>
template <typename... Args>
void Vec<T>::emplace_back(Args &&...args) {
  auto size = this->size();
  this->reserve_total(size + 1);
  ::new (reinterpret_cast<T *>(reinterpret_cast<char *>(this->data()) +
                               size * size_of<T>()))
      T(std::forward<Args>(args)...);
  this->set_len(size + 1);
}

template <typename T>
void Vec<T>::clear() {
  this->truncate(0);
}

template <typename T>
typename Vec<T>::iterator Vec<T>::begin() noexcept {
  return Slice<T>(this->data(), this->size()).begin();
}

template <typename T>
typename Vec<T>::iterator Vec<T>::end() noexcept {
  return Slice<T>(this->data(), this->size()).end();
}

template <typename T>
typename Vec<T>::const_iterator Vec<T>::begin() const noexcept {
  return this->cbegin();
}

template <typename T>
typename Vec<T>::const_iterator Vec<T>::end() const noexcept {
  return this->cend();
}

template <typename T>
typename Vec<T>::const_iterator Vec<T>::cbegin() const noexcept {
  return Slice<const T>(this->data(), this->size()).begin();
}

template <typename T>
typename Vec<T>::const_iterator Vec<T>::cend() const noexcept {
  return Slice<const T>(this->data(), this->size()).end();
}

template <typename T>
void Vec<T>::swap(Vec &rhs) noexcept {
  using std::swap;
  swap(this->repr, rhs.repr);
}

template <typename T>
Vec<T>::Vec(unsafe_bitcopy_t, const Vec &bits) noexcept : repr(bits.repr) {}
#endif // CXXBRIDGE1_RUST_VEC

#ifndef CXXBRIDGE1_IS_COMPLETE
#define CXXBRIDGE1_IS_COMPLETE
namespace detail {
namespace {
template <typename T, typename = std::size_t>
struct is_complete : std::false_type {};
template <typename T>
struct is_complete<T, decltype(sizeof(T))> : std::true_type {};
} // namespace
} // namespace detail
#endif // CXXBRIDGE1_IS_COMPLETE

#ifndef CXXBRIDGE1_LAYOUT
#define CXXBRIDGE1_LAYOUT
class layout {
  template <typename T>
  friend std::size_t size_of();
  template <typename T>
  friend std::size_t align_of();
  template <typename T>
  static typename std::enable_if<std::is_base_of<Opaque, T>::value,
                                 std::size_t>::type
  do_size_of() {
    return T::layout::size();
  }
  template <typename T>
  static typename std::enable_if<!std::is_base_of<Opaque, T>::value,
                                 std::size_t>::type
  do_size_of() {
    return sizeof(T);
  }
  template <typename T>
  static
      typename std::enable_if<detail::is_complete<T>::value, std::size_t>::type
      size_of() {
    return do_size_of<T>();
  }
  template <typename T>
  static typename std::enable_if<std::is_base_of<Opaque, T>::value,
                                 std::size_t>::type
  do_align_of() {
    return T::layout::align();
  }
  template <typename T>
  static typename std::enable_if<!std::is_base_of<Opaque, T>::value,
                                 std::size_t>::type
  do_align_of() {
    return alignof(T);
  }
  template <typename T>
  static
      typename std::enable_if<detail::is_complete<T>::value, std::size_t>::type
      align_of() {
    return do_align_of<T>();
  }
};

template <typename T>
std::size_t size_of() {
  return layout::size_of<T>();
}

template <typename T>
std::size_t align_of() {
  return layout::align_of<T>();
}
#endif // CXXBRIDGE1_LAYOUT

#ifndef CXXBRIDGE1_RELOCATABLE
#define CXXBRIDGE1_RELOCATABLE
namespace detail {
template <typename... Ts>
struct make_void {
  using type = void;
};

template <typename... Ts>
using void_t = typename make_void<Ts...>::type;

template <typename Void, template <typename...> class, typename...>
struct detect : std::false_type {};
template <template <typename...> class T, typename... A>
struct detect<void_t<T<A...>>, T, A...> : std::true_type {};

template <template <typename...> class T, typename... A>
using is_detected = detect<void, T, A...>;

template <typename T>
using detect_IsRelocatable = typename T::IsRelocatable;

template <typename T>
struct get_IsRelocatable
    : std::is_same<typename T::IsRelocatable, std::true_type> {};
} // namespace detail

template <typename T>
struct IsRelocatable
    : std::conditional<
          detail::is_detected<detail::detect_IsRelocatable, T>::value,
          detail::get_IsRelocatable<T>,
          std::integral_constant<
              bool, std::is_trivially_move_constructible<T>::value &&
                        std::is_trivially_destructible<T>::value>>::type {};
#endif // CXXBRIDGE1_RELOCATABLE

namespace repr {
using Fat = ::std::array<::std::uintptr_t, 2>;

struct PtrLen final {
  void *ptr;
  ::std::size_t len;
};
} // namespace repr

namespace detail {
class Fail final {
  ::rust::repr::PtrLen &throw$;
public:
  Fail(::rust::repr::PtrLen &throw$) noexcept : throw$(throw$) {}
  void operator()(char const *) noexcept;
  void operator()(std::string const &) noexcept;
};
} // namespace detail

namespace {
template <typename T>
class impl<Slice<T>> final {
public:
  static repr::Fat repr(Slice<T> slice) noexcept {
    return slice.repr;
  }
};
} // namespace
} // namespace cxxbridge1

namespace behavior {
class missing {};
missing trycatch(...);

template <typename Try, typename Fail>
static typename ::std::enable_if<
    ::std::is_same<decltype(trycatch(::std::declval<Try>(), ::std::declval<Fail>())),
                 missing>::value>::type
trycatch(Try &&func, Fail &&fail) noexcept try {
  func();
} catch (::std::exception const &e) {
  fail(e.what());
}
} // namespace behavior
} // namespace rust

static_assert(
    ::rust::IsRelocatable<::c_short>::value,
    "type c_short should be trivially move constructible and trivially destructible in C++ to be used as a return value of `idalib_inf_get_bin_prefix_size` in Rust");
static_assert(
    ::rust::IsRelocatable<::c_int>::value,
    "type c_int should be trivially move constructible and trivially destructible in C++ to be used as an argument of `init_library`, `idalib_func_flow_chart`, return value of `init_library`, `idalib_open_database_quiet` or slice element in &[c_int] in Rust");
static_assert(
    ::rust::IsRelocatable<::c_uint>::value,
    "type c_uint should be trivially move constructible and trivially destructible in C++ to be used as an argument of `idalib_bookmarks_t_mark`, `idalib_bookmarks_t_get_desc`, `idalib_bookmarks_t_erase` or return value of `idalib_inf_get_app_bitness` in Rust");
static_assert(
    ::rust::IsRelocatable<::c_longlong>::value,
    "type c_longlong should be trivially move constructible and trivially destructible in C++ to be used as a return value of `idalib_inf_get_netdelta` in Rust");
static_assert(
    ::rust::IsRelocatable<::c_ulonglong>::value,
    "type c_ulonglong should be trivially move constructible and trivially destructible in C++ to be used as an argument of `idalib_entry_name`, `idalib_get_cmt`, `idalib_bookmarks_t_mark` or return value of `idalib_inf_get_baseaddr`, `idalib_inf_get_start_ss`, `idalib_inf_get_start_cs` in Rust");
static_assert(
    ::rust::IsRelocatable<::filetype_t>::value,
    "type filetype_t should be trivially move constructible and trivially destructible in C++ to be used as a return value of `idalib_inf_get_filetype` in Rust");

extern "C" {
void cxxbridge1$init_library(::c_int *argc, char **argv, ::c_int *return$) noexcept {
  ::c_int (*init_library$)(::c_int, char **) = ::init_library;
  new (return$) ::c_int(init_library$(::std::move(*argc), argv));
}

void cxxbridge1$idalib_open_database_quiet(char const *name, bool auto_analysis, ::c_int *return$) noexcept {
  ::c_int (*idalib_open_database_quiet$)(char const *, bool) = ::idalib_open_database_quiet;
  new (return$) ::c_int(idalib_open_database_quiet$(name, auto_analysis));
}

bool cxxbridge1$idalib_check_license() noexcept {
  bool (*idalib_check_license$)() = ::idalib_check_license;
  return idalib_check_license$();
}

bool cxxbridge1$idalib_get_license_id(::std::array<::std::uint8_t, 6> &id) noexcept {
  bool (*idalib_get_license_id$)(::std::array<::std::uint8_t, 6> &) = ::idalib_get_license_id;
  return idalib_get_license_id$(id);
}

::rust::repr::PtrLen cxxbridge1$idalib_entry_name(::c_ulonglong *e, ::rust::String *return$) noexcept {
  ::rust::String (*idalib_entry_name$)(::c_ulonglong) = ::idalib_entry_name;
  ::rust::repr::PtrLen throw$;
  ::rust::behavior::trycatch(
      [&] {
        new (return$) ::rust::String(idalib_entry_name$(::std::move(*e)));
        throw$.ptr = nullptr;
      },
      ::rust::detail::Fail(throw$));
  return throw$;
}

::std::uint64_t cxxbridge1$idalib_func_flags(::func_t const *f) noexcept {
  ::std::uint64_t (*idalib_func_flags$)(::func_t const *) = ::idalib_func_flags;
  return idalib_func_flags$(f);
}

::rust::repr::PtrLen cxxbridge1$idalib_func_name(::func_t const *f, ::rust::String *return$) noexcept {
  ::rust::String (*idalib_func_name$)(::func_t const *) = ::idalib_func_name;
  ::rust::repr::PtrLen throw$;
  ::rust::behavior::trycatch(
      [&] {
        new (return$) ::rust::String(idalib_func_name$(f));
        throw$.ptr = nullptr;
      },
      ::rust::detail::Fail(throw$));
  return throw$;
}

::rust::repr::PtrLen cxxbridge1$idalib_func_flow_chart(::func_t *f, ::c_int *flags, ::qflow_chart_t **return$) noexcept {
  ::std::unique_ptr<::qflow_chart_t> (*idalib_func_flow_chart$)(::func_t *, ::c_int) = ::idalib_func_flow_chart;
  ::rust::repr::PtrLen throw$;
  ::rust::behavior::trycatch(
      [&] {
        new (return$) ::qflow_chart_t *(idalib_func_flow_chart$(f, ::std::move(*flags)).release());
        throw$.ptr = nullptr;
      },
      ::rust::detail::Fail(throw$));
  return throw$;
}

::std::uint16_t cxxbridge1$idalib_inf_get_version() noexcept {
  ::std::uint16_t (*idalib_inf_get_version$)() = ::idalib_inf_get_version;
  return idalib_inf_get_version$();
}

::std::uint16_t cxxbridge1$idalib_inf_get_genflags() noexcept {
  ::std::uint16_t (*idalib_inf_get_genflags$)() = ::idalib_inf_get_genflags;
  return idalib_inf_get_genflags$();
}

bool cxxbridge1$idalib_inf_is_auto_enabled() noexcept {
  bool (*idalib_inf_is_auto_enabled$)() = ::idalib_inf_is_auto_enabled;
  return idalib_inf_is_auto_enabled$();
}

bool cxxbridge1$idalib_inf_use_allasm() noexcept {
  bool (*idalib_inf_use_allasm$)() = ::idalib_inf_use_allasm;
  return idalib_inf_use_allasm$();
}

bool cxxbridge1$idalib_inf_loading_idc() noexcept {
  bool (*idalib_inf_loading_idc$)() = ::idalib_inf_loading_idc;
  return idalib_inf_loading_idc$();
}

bool cxxbridge1$idalib_inf_no_store_user_info() noexcept {
  bool (*idalib_inf_no_store_user_info$)() = ::idalib_inf_no_store_user_info;
  return idalib_inf_no_store_user_info$();
}

bool cxxbridge1$idalib_inf_readonly_idb() noexcept {
  bool (*idalib_inf_readonly_idb$)() = ::idalib_inf_readonly_idb;
  return idalib_inf_readonly_idb$();
}

bool cxxbridge1$idalib_inf_check_manual_ops() noexcept {
  bool (*idalib_inf_check_manual_ops$)() = ::idalib_inf_check_manual_ops;
  return idalib_inf_check_manual_ops$();
}

bool cxxbridge1$idalib_inf_allow_non_matched_ops() noexcept {
  bool (*idalib_inf_allow_non_matched_ops$)() = ::idalib_inf_allow_non_matched_ops;
  return idalib_inf_allow_non_matched_ops$();
}

bool cxxbridge1$idalib_inf_is_graph_view() noexcept {
  bool (*idalib_inf_is_graph_view$)() = ::idalib_inf_is_graph_view;
  return idalib_inf_is_graph_view$();
}

::std::uint32_t cxxbridge1$idalib_inf_get_lflags() noexcept {
  ::std::uint32_t (*idalib_inf_get_lflags$)() = ::idalib_inf_get_lflags;
  return idalib_inf_get_lflags$();
}

bool cxxbridge1$idalib_inf_decode_fpp() noexcept {
  bool (*idalib_inf_decode_fpp$)() = ::idalib_inf_decode_fpp;
  return idalib_inf_decode_fpp$();
}

bool cxxbridge1$idalib_inf_is_32bit_or_higher() noexcept {
  bool (*idalib_inf_is_32bit_or_higher$)() = ::idalib_inf_is_32bit_or_higher;
  return idalib_inf_is_32bit_or_higher$();
}

bool cxxbridge1$idalib_inf_is_32bit_exactly() noexcept {
  bool (*idalib_inf_is_32bit_exactly$)() = ::idalib_inf_is_32bit_exactly;
  return idalib_inf_is_32bit_exactly$();
}

bool cxxbridge1$idalib_inf_is_16bit() noexcept {
  bool (*idalib_inf_is_16bit$)() = ::idalib_inf_is_16bit;
  return idalib_inf_is_16bit$();
}

bool cxxbridge1$idalib_inf_is_64bit() noexcept {
  bool (*idalib_inf_is_64bit$)() = ::idalib_inf_is_64bit;
  return idalib_inf_is_64bit$();
}

bool cxxbridge1$idalib_inf_is_dll() noexcept {
  bool (*idalib_inf_is_dll$)() = ::idalib_inf_is_dll;
  return idalib_inf_is_dll$();
}

bool cxxbridge1$idalib_inf_is_flat_off32() noexcept {
  bool (*idalib_inf_is_flat_off32$)() = ::idalib_inf_is_flat_off32;
  return idalib_inf_is_flat_off32$();
}

bool cxxbridge1$idalib_inf_is_be() noexcept {
  bool (*idalib_inf_is_be$)() = ::idalib_inf_is_be;
  return idalib_inf_is_be$();
}

bool cxxbridge1$idalib_inf_is_wide_high_byte_first() noexcept {
  bool (*idalib_inf_is_wide_high_byte_first$)() = ::idalib_inf_is_wide_high_byte_first;
  return idalib_inf_is_wide_high_byte_first$();
}

bool cxxbridge1$idalib_inf_dbg_no_store_path() noexcept {
  bool (*idalib_inf_dbg_no_store_path$)() = ::idalib_inf_dbg_no_store_path;
  return idalib_inf_dbg_no_store_path$();
}

bool cxxbridge1$idalib_inf_is_snapshot() noexcept {
  bool (*idalib_inf_is_snapshot$)() = ::idalib_inf_is_snapshot;
  return idalib_inf_is_snapshot$();
}

bool cxxbridge1$idalib_inf_pack_idb() noexcept {
  bool (*idalib_inf_pack_idb$)() = ::idalib_inf_pack_idb;
  return idalib_inf_pack_idb$();
}

bool cxxbridge1$idalib_inf_compress_idb() noexcept {
  bool (*idalib_inf_compress_idb$)() = ::idalib_inf_compress_idb;
  return idalib_inf_compress_idb$();
}

bool cxxbridge1$idalib_inf_is_kernel_mode() noexcept {
  bool (*idalib_inf_is_kernel_mode$)() = ::idalib_inf_is_kernel_mode;
  return idalib_inf_is_kernel_mode$();
}

void cxxbridge1$idalib_inf_get_app_bitness(::c_uint *return$) noexcept {
  ::c_uint (*idalib_inf_get_app_bitness$)() = ::idalib_inf_get_app_bitness;
  new (return$) ::c_uint(idalib_inf_get_app_bitness$());
}

::std::uint32_t cxxbridge1$idalib_inf_get_database_change_count() noexcept {
  ::std::uint32_t (*idalib_inf_get_database_change_count$)() = ::idalib_inf_get_database_change_count;
  return idalib_inf_get_database_change_count$();
}

void cxxbridge1$idalib_inf_get_filetype(::filetype_t *return$) noexcept {
  ::filetype_t (*idalib_inf_get_filetype$)() = ::idalib_inf_get_filetype;
  new (return$) ::filetype_t(idalib_inf_get_filetype$());
}

::std::uint16_t cxxbridge1$idalib_inf_get_ostype() noexcept {
  ::std::uint16_t (*idalib_inf_get_ostype$)() = ::idalib_inf_get_ostype;
  return idalib_inf_get_ostype$();
}

::std::uint16_t cxxbridge1$idalib_inf_get_apptype() noexcept {
  ::std::uint16_t (*idalib_inf_get_apptype$)() = ::idalib_inf_get_apptype;
  return idalib_inf_get_apptype$();
}

::std::uint8_t cxxbridge1$idalib_inf_get_asmtype() noexcept {
  ::std::uint8_t (*idalib_inf_get_asmtype$)() = ::idalib_inf_get_asmtype;
  return idalib_inf_get_asmtype$();
}

::std::uint8_t cxxbridge1$idalib_inf_get_specsegs() noexcept {
  ::std::uint8_t (*idalib_inf_get_specsegs$)() = ::idalib_inf_get_specsegs;
  return idalib_inf_get_specsegs$();
}

::std::uint32_t cxxbridge1$idalib_inf_get_af() noexcept {
  ::std::uint32_t (*idalib_inf_get_af$)() = ::idalib_inf_get_af;
  return idalib_inf_get_af$();
}

bool cxxbridge1$idalib_inf_trace_flow() noexcept {
  bool (*idalib_inf_trace_flow$)() = ::idalib_inf_trace_flow;
  return idalib_inf_trace_flow$();
}

bool cxxbridge1$idalib_inf_mark_code() noexcept {
  bool (*idalib_inf_mark_code$)() = ::idalib_inf_mark_code;
  return idalib_inf_mark_code$();
}

bool cxxbridge1$idalib_inf_create_jump_tables() noexcept {
  bool (*idalib_inf_create_jump_tables$)() = ::idalib_inf_create_jump_tables;
  return idalib_inf_create_jump_tables$();
}

bool cxxbridge1$idalib_inf_noflow_to_data() noexcept {
  bool (*idalib_inf_noflow_to_data$)() = ::idalib_inf_noflow_to_data;
  return idalib_inf_noflow_to_data$();
}

bool cxxbridge1$idalib_inf_create_all_xrefs() noexcept {
  bool (*idalib_inf_create_all_xrefs$)() = ::idalib_inf_create_all_xrefs;
  return idalib_inf_create_all_xrefs$();
}

bool cxxbridge1$idalib_inf_create_func_from_ptr() noexcept {
  bool (*idalib_inf_create_func_from_ptr$)() = ::idalib_inf_create_func_from_ptr;
  return idalib_inf_create_func_from_ptr$();
}

bool cxxbridge1$idalib_inf_create_func_from_call() noexcept {
  bool (*idalib_inf_create_func_from_call$)() = ::idalib_inf_create_func_from_call;
  return idalib_inf_create_func_from_call$();
}

bool cxxbridge1$idalib_inf_create_func_tails() noexcept {
  bool (*idalib_inf_create_func_tails$)() = ::idalib_inf_create_func_tails;
  return idalib_inf_create_func_tails$();
}

bool cxxbridge1$idalib_inf_should_create_stkvars() noexcept {
  bool (*idalib_inf_should_create_stkvars$)() = ::idalib_inf_should_create_stkvars;
  return idalib_inf_should_create_stkvars$();
}

bool cxxbridge1$idalib_inf_propagate_stkargs() noexcept {
  bool (*idalib_inf_propagate_stkargs$)() = ::idalib_inf_propagate_stkargs;
  return idalib_inf_propagate_stkargs$();
}

bool cxxbridge1$idalib_inf_propagate_regargs() noexcept {
  bool (*idalib_inf_propagate_regargs$)() = ::idalib_inf_propagate_regargs;
  return idalib_inf_propagate_regargs$();
}

bool cxxbridge1$idalib_inf_should_trace_sp() noexcept {
  bool (*idalib_inf_should_trace_sp$)() = ::idalib_inf_should_trace_sp;
  return idalib_inf_should_trace_sp$();
}

bool cxxbridge1$idalib_inf_full_sp_ana() noexcept {
  bool (*idalib_inf_full_sp_ana$)() = ::idalib_inf_full_sp_ana;
  return idalib_inf_full_sp_ana$();
}

bool cxxbridge1$idalib_inf_noret_ana() noexcept {
  bool (*idalib_inf_noret_ana$)() = ::idalib_inf_noret_ana;
  return idalib_inf_noret_ana$();
}

bool cxxbridge1$idalib_inf_guess_func_type() noexcept {
  bool (*idalib_inf_guess_func_type$)() = ::idalib_inf_guess_func_type;
  return idalib_inf_guess_func_type$();
}

bool cxxbridge1$idalib_inf_truncate_on_del() noexcept {
  bool (*idalib_inf_truncate_on_del$)() = ::idalib_inf_truncate_on_del;
  return idalib_inf_truncate_on_del$();
}

bool cxxbridge1$idalib_inf_create_strlit_on_xref() noexcept {
  bool (*idalib_inf_create_strlit_on_xref$)() = ::idalib_inf_create_strlit_on_xref;
  return idalib_inf_create_strlit_on_xref$();
}

bool cxxbridge1$idalib_inf_check_unicode_strlits() noexcept {
  bool (*idalib_inf_check_unicode_strlits$)() = ::idalib_inf_check_unicode_strlits;
  return idalib_inf_check_unicode_strlits$();
}

bool cxxbridge1$idalib_inf_create_off_using_fixup() noexcept {
  bool (*idalib_inf_create_off_using_fixup$)() = ::idalib_inf_create_off_using_fixup;
  return idalib_inf_create_off_using_fixup$();
}

bool cxxbridge1$idalib_inf_create_off_on_dref() noexcept {
  bool (*idalib_inf_create_off_on_dref$)() = ::idalib_inf_create_off_on_dref;
  return idalib_inf_create_off_on_dref$();
}

bool cxxbridge1$idalib_inf_op_offset() noexcept {
  bool (*idalib_inf_op_offset$)() = ::idalib_inf_op_offset;
  return idalib_inf_op_offset$();
}

bool cxxbridge1$idalib_inf_data_offset() noexcept {
  bool (*idalib_inf_data_offset$)() = ::idalib_inf_data_offset;
  return idalib_inf_data_offset$();
}

bool cxxbridge1$idalib_inf_use_flirt() noexcept {
  bool (*idalib_inf_use_flirt$)() = ::idalib_inf_use_flirt;
  return idalib_inf_use_flirt$();
}

bool cxxbridge1$idalib_inf_append_sigcmt() noexcept {
  bool (*idalib_inf_append_sigcmt$)() = ::idalib_inf_append_sigcmt;
  return idalib_inf_append_sigcmt$();
}

bool cxxbridge1$idalib_inf_allow_sigmulti() noexcept {
  bool (*idalib_inf_allow_sigmulti$)() = ::idalib_inf_allow_sigmulti;
  return idalib_inf_allow_sigmulti$();
}

bool cxxbridge1$idalib_inf_hide_libfuncs() noexcept {
  bool (*idalib_inf_hide_libfuncs$)() = ::idalib_inf_hide_libfuncs;
  return idalib_inf_hide_libfuncs$();
}

bool cxxbridge1$idalib_inf_rename_jumpfunc() noexcept {
  bool (*idalib_inf_rename_jumpfunc$)() = ::idalib_inf_rename_jumpfunc;
  return idalib_inf_rename_jumpfunc$();
}

bool cxxbridge1$idalib_inf_rename_nullsub() noexcept {
  bool (*idalib_inf_rename_nullsub$)() = ::idalib_inf_rename_nullsub;
  return idalib_inf_rename_nullsub$();
}

bool cxxbridge1$idalib_inf_coagulate_data() noexcept {
  bool (*idalib_inf_coagulate_data$)() = ::idalib_inf_coagulate_data;
  return idalib_inf_coagulate_data$();
}

bool cxxbridge1$idalib_inf_coagulate_code() noexcept {
  bool (*idalib_inf_coagulate_code$)() = ::idalib_inf_coagulate_code;
  return idalib_inf_coagulate_code$();
}

bool cxxbridge1$idalib_inf_final_pass() noexcept {
  bool (*idalib_inf_final_pass$)() = ::idalib_inf_final_pass;
  return idalib_inf_final_pass$();
}

::std::uint32_t cxxbridge1$idalib_inf_get_af2() noexcept {
  ::std::uint32_t (*idalib_inf_get_af2$)() = ::idalib_inf_get_af2;
  return idalib_inf_get_af2$();
}

bool cxxbridge1$idalib_inf_handle_eh() noexcept {
  bool (*idalib_inf_handle_eh$)() = ::idalib_inf_handle_eh;
  return idalib_inf_handle_eh$();
}

bool cxxbridge1$idalib_inf_handle_rtti() noexcept {
  bool (*idalib_inf_handle_rtti$)() = ::idalib_inf_handle_rtti;
  return idalib_inf_handle_rtti$();
}

bool cxxbridge1$idalib_inf_macros_enabled() noexcept {
  bool (*idalib_inf_macros_enabled$)() = ::idalib_inf_macros_enabled;
  return idalib_inf_macros_enabled$();
}

bool cxxbridge1$idalib_inf_merge_strlits() noexcept {
  bool (*idalib_inf_merge_strlits$)() = ::idalib_inf_merge_strlits;
  return idalib_inf_merge_strlits$();
}

void cxxbridge1$idalib_inf_get_baseaddr(::c_ulonglong *return$) noexcept {
  ::c_ulonglong (*idalib_inf_get_baseaddr$)() = ::idalib_inf_get_baseaddr;
  new (return$) ::c_ulonglong(idalib_inf_get_baseaddr$());
}

void cxxbridge1$idalib_inf_get_start_ss(::c_ulonglong *return$) noexcept {
  ::c_ulonglong (*idalib_inf_get_start_ss$)() = ::idalib_inf_get_start_ss;
  new (return$) ::c_ulonglong(idalib_inf_get_start_ss$());
}

void cxxbridge1$idalib_inf_get_start_cs(::c_ulonglong *return$) noexcept {
  ::c_ulonglong (*idalib_inf_get_start_cs$)() = ::idalib_inf_get_start_cs;
  new (return$) ::c_ulonglong(idalib_inf_get_start_cs$());
}

void cxxbridge1$idalib_inf_get_start_ip(::c_ulonglong *return$) noexcept {
  ::c_ulonglong (*idalib_inf_get_start_ip$)() = ::idalib_inf_get_start_ip;
  new (return$) ::c_ulonglong(idalib_inf_get_start_ip$());
}

void cxxbridge1$idalib_inf_get_start_ea(::c_ulonglong *return$) noexcept {
  ::c_ulonglong (*idalib_inf_get_start_ea$)() = ::idalib_inf_get_start_ea;
  new (return$) ::c_ulonglong(idalib_inf_get_start_ea$());
}

void cxxbridge1$idalib_inf_get_start_sp(::c_ulonglong *return$) noexcept {
  ::c_ulonglong (*idalib_inf_get_start_sp$)() = ::idalib_inf_get_start_sp;
  new (return$) ::c_ulonglong(idalib_inf_get_start_sp$());
}

void cxxbridge1$idalib_inf_get_main(::c_ulonglong *return$) noexcept {
  ::c_ulonglong (*idalib_inf_get_main$)() = ::idalib_inf_get_main;
  new (return$) ::c_ulonglong(idalib_inf_get_main$());
}

void cxxbridge1$idalib_inf_get_min_ea(::c_ulonglong *return$) noexcept {
  ::c_ulonglong (*idalib_inf_get_min_ea$)() = ::idalib_inf_get_min_ea;
  new (return$) ::c_ulonglong(idalib_inf_get_min_ea$());
}

void cxxbridge1$idalib_inf_get_max_ea(::c_ulonglong *return$) noexcept {
  ::c_ulonglong (*idalib_inf_get_max_ea$)() = ::idalib_inf_get_max_ea;
  new (return$) ::c_ulonglong(idalib_inf_get_max_ea$());
}

void cxxbridge1$idalib_inf_get_omin_ea(::c_ulonglong *return$) noexcept {
  ::c_ulonglong (*idalib_inf_get_omin_ea$)() = ::idalib_inf_get_omin_ea;
  new (return$) ::c_ulonglong(idalib_inf_get_omin_ea$());
}

void cxxbridge1$idalib_inf_get_omax_ea(::c_ulonglong *return$) noexcept {
  ::c_ulonglong (*idalib_inf_get_omax_ea$)() = ::idalib_inf_get_omax_ea;
  new (return$) ::c_ulonglong(idalib_inf_get_omax_ea$());
}

void cxxbridge1$idalib_inf_get_lowoff(::c_ulonglong *return$) noexcept {
  ::c_ulonglong (*idalib_inf_get_lowoff$)() = ::idalib_inf_get_lowoff;
  new (return$) ::c_ulonglong(idalib_inf_get_lowoff$());
}

void cxxbridge1$idalib_inf_get_highoff(::c_ulonglong *return$) noexcept {
  ::c_ulonglong (*idalib_inf_get_highoff$)() = ::idalib_inf_get_highoff;
  new (return$) ::c_ulonglong(idalib_inf_get_highoff$());
}

void cxxbridge1$idalib_inf_get_maxref(::c_ulonglong *return$) noexcept {
  ::c_ulonglong (*idalib_inf_get_maxref$)() = ::idalib_inf_get_maxref;
  new (return$) ::c_ulonglong(idalib_inf_get_maxref$());
}

void cxxbridge1$idalib_inf_get_netdelta(::c_longlong *return$) noexcept {
  ::c_longlong (*idalib_inf_get_netdelta$)() = ::idalib_inf_get_netdelta;
  new (return$) ::c_longlong(idalib_inf_get_netdelta$());
}

::std::uint8_t cxxbridge1$idalib_inf_get_xrefnum() noexcept {
  ::std::uint8_t (*idalib_inf_get_xrefnum$)() = ::idalib_inf_get_xrefnum;
  return idalib_inf_get_xrefnum$();
}

::std::uint8_t cxxbridge1$idalib_inf_get_type_xrefnum() noexcept {
  ::std::uint8_t (*idalib_inf_get_type_xrefnum$)() = ::idalib_inf_get_type_xrefnum;
  return idalib_inf_get_type_xrefnum$();
}

::std::uint8_t cxxbridge1$idalib_inf_get_refcmtnum() noexcept {
  ::std::uint8_t (*idalib_inf_get_refcmtnum$)() = ::idalib_inf_get_refcmtnum;
  return idalib_inf_get_refcmtnum$();
}

::std::uint8_t cxxbridge1$idalib_inf_get_xrefflag() noexcept {
  ::std::uint8_t (*idalib_inf_get_xrefflag$)() = ::idalib_inf_get_xrefflag;
  return idalib_inf_get_xrefflag$();
}

bool cxxbridge1$idalib_inf_show_xref_seg() noexcept {
  bool (*idalib_inf_show_xref_seg$)() = ::idalib_inf_show_xref_seg;
  return idalib_inf_show_xref_seg$();
}

bool cxxbridge1$idalib_inf_show_xref_tmarks() noexcept {
  bool (*idalib_inf_show_xref_tmarks$)() = ::idalib_inf_show_xref_tmarks;
  return idalib_inf_show_xref_tmarks$();
}

bool cxxbridge1$idalib_inf_show_xref_fncoff() noexcept {
  bool (*idalib_inf_show_xref_fncoff$)() = ::idalib_inf_show_xref_fncoff;
  return idalib_inf_show_xref_fncoff$();
}

bool cxxbridge1$idalib_inf_show_xref_val() noexcept {
  bool (*idalib_inf_show_xref_val$)() = ::idalib_inf_show_xref_val;
  return idalib_inf_show_xref_val$();
}

::std::uint16_t cxxbridge1$idalib_inf_get_max_autoname_len() noexcept {
  ::std::uint16_t (*idalib_inf_get_max_autoname_len$)() = ::idalib_inf_get_max_autoname_len;
  return idalib_inf_get_max_autoname_len$();
}

char cxxbridge1$idalib_inf_get_nametype() noexcept {
  char (*idalib_inf_get_nametype$)() = ::idalib_inf_get_nametype;
  return idalib_inf_get_nametype$();
}

::std::uint32_t cxxbridge1$idalib_inf_get_short_demnames() noexcept {
  ::std::uint32_t (*idalib_inf_get_short_demnames$)() = ::idalib_inf_get_short_demnames;
  return idalib_inf_get_short_demnames$();
}

::std::uint32_t cxxbridge1$idalib_inf_get_long_demnames() noexcept {
  ::std::uint32_t (*idalib_inf_get_long_demnames$)() = ::idalib_inf_get_long_demnames;
  return idalib_inf_get_long_demnames$();
}

::std::uint8_t cxxbridge1$idalib_inf_get_demnames() noexcept {
  ::std::uint8_t (*idalib_inf_get_demnames$)() = ::idalib_inf_get_demnames;
  return idalib_inf_get_demnames$();
}

::std::uint8_t cxxbridge1$idalib_inf_get_listnames() noexcept {
  ::std::uint8_t (*idalib_inf_get_listnames$)() = ::idalib_inf_get_listnames;
  return idalib_inf_get_listnames$();
}

::std::uint8_t cxxbridge1$idalib_inf_get_indent() noexcept {
  ::std::uint8_t (*idalib_inf_get_indent$)() = ::idalib_inf_get_indent;
  return idalib_inf_get_indent$();
}

::std::uint8_t cxxbridge1$idalib_inf_get_cmt_indent() noexcept {
  ::std::uint8_t (*idalib_inf_get_cmt_indent$)() = ::idalib_inf_get_cmt_indent;
  return idalib_inf_get_cmt_indent$();
}

::std::uint16_t cxxbridge1$idalib_inf_get_margin() noexcept {
  ::std::uint16_t (*idalib_inf_get_margin$)() = ::idalib_inf_get_margin;
  return idalib_inf_get_margin$();
}

::std::uint16_t cxxbridge1$idalib_inf_get_lenxref() noexcept {
  ::std::uint16_t (*idalib_inf_get_lenxref$)() = ::idalib_inf_get_lenxref;
  return idalib_inf_get_lenxref$();
}

::std::uint32_t cxxbridge1$idalib_inf_get_outflags() noexcept {
  ::std::uint32_t (*idalib_inf_get_outflags$)() = ::idalib_inf_get_outflags;
  return idalib_inf_get_outflags$();
}

bool cxxbridge1$idalib_inf_show_void() noexcept {
  bool (*idalib_inf_show_void$)() = ::idalib_inf_show_void;
  return idalib_inf_show_void$();
}

bool cxxbridge1$idalib_inf_show_auto() noexcept {
  bool (*idalib_inf_show_auto$)() = ::idalib_inf_show_auto;
  return idalib_inf_show_auto$();
}

bool cxxbridge1$idalib_inf_gen_null() noexcept {
  bool (*idalib_inf_gen_null$)() = ::idalib_inf_gen_null;
  return idalib_inf_gen_null$();
}

bool cxxbridge1$idalib_inf_show_line_pref() noexcept {
  bool (*idalib_inf_show_line_pref$)() = ::idalib_inf_show_line_pref;
  return idalib_inf_show_line_pref$();
}

bool cxxbridge1$idalib_inf_line_pref_with_seg() noexcept {
  bool (*idalib_inf_line_pref_with_seg$)() = ::idalib_inf_line_pref_with_seg;
  return idalib_inf_line_pref_with_seg$();
}

bool cxxbridge1$idalib_inf_gen_lzero() noexcept {
  bool (*idalib_inf_gen_lzero$)() = ::idalib_inf_gen_lzero;
  return idalib_inf_gen_lzero$();
}

bool cxxbridge1$idalib_inf_gen_org() noexcept {
  bool (*idalib_inf_gen_org$)() = ::idalib_inf_gen_org;
  return idalib_inf_gen_org$();
}

bool cxxbridge1$idalib_inf_gen_assume() noexcept {
  bool (*idalib_inf_gen_assume$)() = ::idalib_inf_gen_assume;
  return idalib_inf_gen_assume$();
}

bool cxxbridge1$idalib_inf_gen_tryblks() noexcept {
  bool (*idalib_inf_gen_tryblks$)() = ::idalib_inf_gen_tryblks;
  return idalib_inf_gen_tryblks$();
}

::std::uint8_t cxxbridge1$idalib_inf_get_cmtflg() noexcept {
  ::std::uint8_t (*idalib_inf_get_cmtflg$)() = ::idalib_inf_get_cmtflg;
  return idalib_inf_get_cmtflg$();
}

bool cxxbridge1$idalib_inf_show_repeatables() noexcept {
  bool (*idalib_inf_show_repeatables$)() = ::idalib_inf_show_repeatables;
  return idalib_inf_show_repeatables$();
}

bool cxxbridge1$idalib_inf_show_all_comments() noexcept {
  bool (*idalib_inf_show_all_comments$)() = ::idalib_inf_show_all_comments;
  return idalib_inf_show_all_comments$();
}

bool cxxbridge1$idalib_inf_hide_comments() noexcept {
  bool (*idalib_inf_hide_comments$)() = ::idalib_inf_hide_comments;
  return idalib_inf_hide_comments$();
}

bool cxxbridge1$idalib_inf_show_src_linnum() noexcept {
  bool (*idalib_inf_show_src_linnum$)() = ::idalib_inf_show_src_linnum;
  return idalib_inf_show_src_linnum$();
}

bool cxxbridge1$idalib_inf_test_mode() noexcept {
  bool (*idalib_inf_test_mode$)() = ::idalib_inf_test_mode;
  return idalib_inf_test_mode$();
}

bool cxxbridge1$idalib_inf_show_hidden_insns() noexcept {
  bool (*idalib_inf_show_hidden_insns$)() = ::idalib_inf_show_hidden_insns;
  return idalib_inf_show_hidden_insns$();
}

bool cxxbridge1$idalib_inf_show_hidden_funcs() noexcept {
  bool (*idalib_inf_show_hidden_funcs$)() = ::idalib_inf_show_hidden_funcs;
  return idalib_inf_show_hidden_funcs$();
}

bool cxxbridge1$idalib_inf_show_hidden_segms() noexcept {
  bool (*idalib_inf_show_hidden_segms$)() = ::idalib_inf_show_hidden_segms;
  return idalib_inf_show_hidden_segms$();
}

::std::uint8_t cxxbridge1$idalib_inf_get_limiter() noexcept {
  ::std::uint8_t (*idalib_inf_get_limiter$)() = ::idalib_inf_get_limiter;
  return idalib_inf_get_limiter$();
}

bool cxxbridge1$idalib_inf_is_limiter_thin() noexcept {
  bool (*idalib_inf_is_limiter_thin$)() = ::idalib_inf_is_limiter_thin;
  return idalib_inf_is_limiter_thin$();
}

bool cxxbridge1$idalib_inf_is_limiter_thick() noexcept {
  bool (*idalib_inf_is_limiter_thick$)() = ::idalib_inf_is_limiter_thick;
  return idalib_inf_is_limiter_thick$();
}

bool cxxbridge1$idalib_inf_is_limiter_empty() noexcept {
  bool (*idalib_inf_is_limiter_empty$)() = ::idalib_inf_is_limiter_empty;
  return idalib_inf_is_limiter_empty$();
}

void cxxbridge1$idalib_inf_get_bin_prefix_size(::c_short *return$) noexcept {
  ::c_short (*idalib_inf_get_bin_prefix_size$)() = ::idalib_inf_get_bin_prefix_size;
  new (return$) ::c_short(idalib_inf_get_bin_prefix_size$());
}

::std::uint8_t cxxbridge1$idalib_inf_get_prefflag() noexcept {
  ::std::uint8_t (*idalib_inf_get_prefflag$)() = ::idalib_inf_get_prefflag;
  return idalib_inf_get_prefflag$();
}

bool cxxbridge1$idalib_inf_prefix_show_segaddr() noexcept {
  bool (*idalib_inf_prefix_show_segaddr$)() = ::idalib_inf_prefix_show_segaddr;
  return idalib_inf_prefix_show_segaddr$();
}

bool cxxbridge1$idalib_inf_prefix_show_funcoff() noexcept {
  bool (*idalib_inf_prefix_show_funcoff$)() = ::idalib_inf_prefix_show_funcoff;
  return idalib_inf_prefix_show_funcoff$();
}

bool cxxbridge1$idalib_inf_prefix_show_stack() noexcept {
  bool (*idalib_inf_prefix_show_stack$)() = ::idalib_inf_prefix_show_stack;
  return idalib_inf_prefix_show_stack$();
}

bool cxxbridge1$idalib_inf_prefix_truncate_opcode_bytes() noexcept {
  bool (*idalib_inf_prefix_truncate_opcode_bytes$)() = ::idalib_inf_prefix_truncate_opcode_bytes;
  return idalib_inf_prefix_truncate_opcode_bytes$();
}

::std::uint8_t cxxbridge1$idalib_inf_get_strlit_flags() noexcept {
  ::std::uint8_t (*idalib_inf_get_strlit_flags$)() = ::idalib_inf_get_strlit_flags;
  return idalib_inf_get_strlit_flags$();
}

bool cxxbridge1$idalib_inf_strlit_names() noexcept {
  bool (*idalib_inf_strlit_names$)() = ::idalib_inf_strlit_names;
  return idalib_inf_strlit_names$();
}

bool cxxbridge1$idalib_inf_strlit_name_bit() noexcept {
  bool (*idalib_inf_strlit_name_bit$)() = ::idalib_inf_strlit_name_bit;
  return idalib_inf_strlit_name_bit$();
}

bool cxxbridge1$idalib_inf_strlit_serial_names() noexcept {
  bool (*idalib_inf_strlit_serial_names$)() = ::idalib_inf_strlit_serial_names;
  return idalib_inf_strlit_serial_names$();
}

bool cxxbridge1$idalib_inf_unicode_strlits() noexcept {
  bool (*idalib_inf_unicode_strlits$)() = ::idalib_inf_unicode_strlits;
  return idalib_inf_unicode_strlits$();
}

bool cxxbridge1$idalib_inf_strlit_autocmt() noexcept {
  bool (*idalib_inf_strlit_autocmt$)() = ::idalib_inf_strlit_autocmt;
  return idalib_inf_strlit_autocmt$();
}

bool cxxbridge1$idalib_inf_strlit_savecase() noexcept {
  bool (*idalib_inf_strlit_savecase$)() = ::idalib_inf_strlit_savecase;
  return idalib_inf_strlit_savecase$();
}

::std::uint8_t cxxbridge1$idalib_inf_get_strlit_break() noexcept {
  ::std::uint8_t (*idalib_inf_get_strlit_break$)() = ::idalib_inf_get_strlit_break;
  return idalib_inf_get_strlit_break$();
}

char cxxbridge1$idalib_inf_get_strlit_zeroes() noexcept {
  char (*idalib_inf_get_strlit_zeroes$)() = ::idalib_inf_get_strlit_zeroes;
  return idalib_inf_get_strlit_zeroes$();
}

::std::int32_t cxxbridge1$idalib_inf_get_strtype() noexcept {
  ::std::int32_t (*idalib_inf_get_strtype$)() = ::idalib_inf_get_strtype;
  return idalib_inf_get_strtype$();
}

void cxxbridge1$idalib_inf_get_strlit_sernum(::c_ulonglong *return$) noexcept {
  ::c_ulonglong (*idalib_inf_get_strlit_sernum$)() = ::idalib_inf_get_strlit_sernum;
  new (return$) ::c_ulonglong(idalib_inf_get_strlit_sernum$());
}

void cxxbridge1$idalib_inf_get_datatypes(::c_ulonglong *return$) noexcept {
  ::c_ulonglong (*idalib_inf_get_datatypes$)() = ::idalib_inf_get_datatypes;
  new (return$) ::c_ulonglong(idalib_inf_get_datatypes$());
}

::std::uint32_t cxxbridge1$idalib_inf_get_abibits() noexcept {
  ::std::uint32_t (*idalib_inf_get_abibits$)() = ::idalib_inf_get_abibits;
  return idalib_inf_get_abibits$();
}

bool cxxbridge1$idalib_inf_is_mem_aligned4() noexcept {
  bool (*idalib_inf_is_mem_aligned4$)() = ::idalib_inf_is_mem_aligned4;
  return idalib_inf_is_mem_aligned4$();
}

bool cxxbridge1$idalib_inf_pack_stkargs() noexcept {
  bool (*idalib_inf_pack_stkargs$)() = ::idalib_inf_pack_stkargs;
  return idalib_inf_pack_stkargs$();
}

bool cxxbridge1$idalib_inf_big_arg_align() noexcept {
  bool (*idalib_inf_big_arg_align$)() = ::idalib_inf_big_arg_align;
  return idalib_inf_big_arg_align$();
}

bool cxxbridge1$idalib_inf_stack_ldbl() noexcept {
  bool (*idalib_inf_stack_ldbl$)() = ::idalib_inf_stack_ldbl;
  return idalib_inf_stack_ldbl$();
}

bool cxxbridge1$idalib_inf_stack_varargs() noexcept {
  bool (*idalib_inf_stack_varargs$)() = ::idalib_inf_stack_varargs;
  return idalib_inf_stack_varargs$();
}

bool cxxbridge1$idalib_inf_is_hard_float() noexcept {
  bool (*idalib_inf_is_hard_float$)() = ::idalib_inf_is_hard_float;
  return idalib_inf_is_hard_float$();
}

bool cxxbridge1$idalib_inf_abi_set_by_user() noexcept {
  bool (*idalib_inf_abi_set_by_user$)() = ::idalib_inf_abi_set_by_user;
  return idalib_inf_abi_set_by_user$();
}

bool cxxbridge1$idalib_inf_use_gcc_layout() noexcept {
  bool (*idalib_inf_use_gcc_layout$)() = ::idalib_inf_use_gcc_layout;
  return idalib_inf_use_gcc_layout$();
}

bool cxxbridge1$idalib_inf_map_stkargs() noexcept {
  bool (*idalib_inf_map_stkargs$)() = ::idalib_inf_map_stkargs;
  return idalib_inf_map_stkargs$();
}

bool cxxbridge1$idalib_inf_huge_arg_align() noexcept {
  bool (*idalib_inf_huge_arg_align$)() = ::idalib_inf_huge_arg_align;
  return idalib_inf_huge_arg_align$();
}

::std::uint32_t cxxbridge1$idalib_inf_get_appcall_options() noexcept {
  ::std::uint32_t (*idalib_inf_get_appcall_options$)() = ::idalib_inf_get_appcall_options;
  return idalib_inf_get_appcall_options$();
}

void cxxbridge1$idalib_inf_get_privrange_start_ea(::c_ulonglong *return$) noexcept {
  ::c_ulonglong (*idalib_inf_get_privrange_start_ea$)() = ::idalib_inf_get_privrange_start_ea;
  new (return$) ::c_ulonglong(idalib_inf_get_privrange_start_ea$());
}

void cxxbridge1$idalib_inf_get_privrange_end_ea(::c_ulonglong *return$) noexcept {
  ::c_ulonglong (*idalib_inf_get_privrange_end_ea$)() = ::idalib_inf_get_privrange_end_ea;
  new (return$) ::c_ulonglong(idalib_inf_get_privrange_end_ea$());
}

::std::uint8_t cxxbridge1$idalib_inf_get_cc_id() noexcept {
  ::std::uint8_t (*idalib_inf_get_cc_id$)() = ::idalib_inf_get_cc_id;
  return idalib_inf_get_cc_id$();
}

::std::uint8_t cxxbridge1$idalib_inf_get_cc_cm() noexcept {
  ::std::uint8_t (*idalib_inf_get_cc_cm$)() = ::idalib_inf_get_cc_cm;
  return idalib_inf_get_cc_cm$();
}

::std::uint8_t cxxbridge1$idalib_inf_get_cc_size_i() noexcept {
  ::std::uint8_t (*idalib_inf_get_cc_size_i$)() = ::idalib_inf_get_cc_size_i;
  return idalib_inf_get_cc_size_i$();
}

::std::uint8_t cxxbridge1$idalib_inf_get_cc_size_b() noexcept {
  ::std::uint8_t (*idalib_inf_get_cc_size_b$)() = ::idalib_inf_get_cc_size_b;
  return idalib_inf_get_cc_size_b$();
}

::std::uint8_t cxxbridge1$idalib_inf_get_cc_size_e() noexcept {
  ::std::uint8_t (*idalib_inf_get_cc_size_e$)() = ::idalib_inf_get_cc_size_e;
  return idalib_inf_get_cc_size_e$();
}

::std::uint8_t cxxbridge1$idalib_inf_get_cc_defalign() noexcept {
  ::std::uint8_t (*idalib_inf_get_cc_defalign$)() = ::idalib_inf_get_cc_defalign;
  return idalib_inf_get_cc_defalign$();
}

::std::uint8_t cxxbridge1$idalib_inf_get_cc_size_s() noexcept {
  ::std::uint8_t (*idalib_inf_get_cc_size_s$)() = ::idalib_inf_get_cc_size_s;
  return idalib_inf_get_cc_size_s$();
}

::std::uint8_t cxxbridge1$idalib_inf_get_cc_size_l() noexcept {
  ::std::uint8_t (*idalib_inf_get_cc_size_l$)() = ::idalib_inf_get_cc_size_l;
  return idalib_inf_get_cc_size_l$();
}

::std::uint8_t cxxbridge1$idalib_inf_get_cc_size_ll() noexcept {
  ::std::uint8_t (*idalib_inf_get_cc_size_ll$)() = ::idalib_inf_get_cc_size_ll;
  return idalib_inf_get_cc_size_ll$();
}

::std::uint8_t cxxbridge1$idalib_inf_get_cc_size_ldbl() noexcept {
  ::std::uint8_t (*idalib_inf_get_cc_size_ldbl$)() = ::idalib_inf_get_cc_size_ldbl;
  return idalib_inf_get_cc_size_ldbl$();
}

void cxxbridge1$idalib_inf_get_procname(::rust::String *return$) noexcept {
  ::rust::String (*idalib_inf_get_procname$)() = ::idalib_inf_get_procname;
  new (return$) ::rust::String(idalib_inf_get_procname$());
}

void cxxbridge1$idalib_inf_get_strlit_pref(::rust::String *return$) noexcept {
  ::rust::String (*idalib_inf_get_strlit_pref$)() = ::idalib_inf_get_strlit_pref;
  new (return$) ::rust::String(idalib_inf_get_strlit_pref$());
}

bool cxxbridge1$idalib_inf_get_cc(::compiler_info_t *out) noexcept {
  bool (*idalib_inf_get_cc$)(::compiler_info_t *) = ::idalib_inf_get_cc;
  return idalib_inf_get_cc$(out);
}

bool cxxbridge1$idalib_inf_get_privrange(::range_t *out) noexcept {
  bool (*idalib_inf_get_privrange$)(::range_t *) = ::idalib_inf_get_privrange;
  return idalib_inf_get_privrange$(out);
}

::std::int32_t cxxbridge1$idalib_ph_id(::processor_t const *ph) noexcept {
  ::std::int32_t (*idalib_ph_id$)(::processor_t const *) = ::idalib_ph_id;
  return idalib_ph_id$(ph);
}

void cxxbridge1$idalib_ph_short_name(::processor_t const *ph, ::rust::String *return$) noexcept {
  ::rust::String (*idalib_ph_short_name$)(::processor_t const *) = ::idalib_ph_short_name;
  new (return$) ::rust::String(idalib_ph_short_name$(ph));
}

void cxxbridge1$idalib_ph_long_name(::processor_t const *ph, ::rust::String *return$) noexcept {
  ::rust::String (*idalib_ph_long_name$)(::processor_t const *) = ::idalib_ph_long_name;
  new (return$) ::rust::String(idalib_ph_long_name$(ph));
}

::qbasic_block_t const *cxxbridge1$idalib_qflow_graph_getn_block(::qflow_chart_t const *f, ::std::size_t n) noexcept {
  ::qbasic_block_t const *(*idalib_qflow_graph_getn_block$)(::qflow_chart_t const *, ::std::size_t) = ::idalib_qflow_graph_getn_block;
  return idalib_qflow_graph_getn_block$(f, n);
}

::rust::repr::Fat cxxbridge1$idalib_qbasic_block_succs(::qbasic_block_t const *b) noexcept {
  ::rust::Slice<::c_int const> (*idalib_qbasic_block_succs$)(::qbasic_block_t const *) = ::idalib_qbasic_block_succs;
  return ::rust::impl<::rust::Slice<::c_int const>>::repr(idalib_qbasic_block_succs$(b));
}

::rust::repr::Fat cxxbridge1$idalib_qbasic_block_preds(::qbasic_block_t const *b) noexcept {
  ::rust::Slice<::c_int const> (*idalib_qbasic_block_preds$)(::qbasic_block_t const *) = ::idalib_qbasic_block_preds;
  return ::rust::impl<::rust::Slice<::c_int const>>::repr(idalib_qbasic_block_preds$(b));
}

::rust::repr::PtrLen cxxbridge1$idalib_segm_name(::segment_t const *s, ::rust::String *return$) noexcept {
  ::rust::String (*idalib_segm_name$)(::segment_t const *) = ::idalib_segm_name;
  ::rust::repr::PtrLen throw$;
  ::rust::behavior::trycatch(
      [&] {
        new (return$) ::rust::String(idalib_segm_name$(s));
        throw$.ptr = nullptr;
      },
      ::rust::detail::Fail(throw$));
  return throw$;
}

::rust::repr::PtrLen cxxbridge1$idalib_segm_bytes(::segment_t const *s, ::rust::Vec<::std::uint8_t> &buf, ::std::size_t *return$) noexcept {
  ::std::size_t (*idalib_segm_bytes$)(::segment_t const *, ::rust::Vec<::std::uint8_t> &) = ::idalib_segm_bytes;
  ::rust::repr::PtrLen throw$;
  ::rust::behavior::trycatch(
      [&] {
        new (return$) ::std::size_t(idalib_segm_bytes$(s, buf));
        throw$.ptr = nullptr;
      },
      ::rust::detail::Fail(throw$));
  return throw$;
}

::std::uint8_t cxxbridge1$idalib_segm_align(::segment_t const *s) noexcept {
  ::std::uint8_t (*idalib_segm_align$)(::segment_t const *) = ::idalib_segm_align;
  return idalib_segm_align$(s);
}

::std::uint8_t cxxbridge1$idalib_segm_perm(::segment_t const *s) noexcept {
  ::std::uint8_t (*idalib_segm_perm$)(::segment_t const *) = ::idalib_segm_perm;
  return idalib_segm_perm$(s);
}

::std::uint8_t cxxbridge1$idalib_segm_bitness(::segment_t const *s) noexcept {
  ::std::uint8_t (*idalib_segm_bitness$)(::segment_t const *) = ::idalib_segm_bitness;
  return idalib_segm_bitness$(s);
}

::std::uint8_t cxxbridge1$idalib_segm_type(::segment_t const *s) noexcept {
  ::std::uint8_t (*idalib_segm_type$)(::segment_t const *) = ::idalib_segm_type;
  return idalib_segm_type$(s);
}

void cxxbridge1$idalib_get_cmt(::c_ulonglong *ea, bool rptble, ::rust::String *return$) noexcept {
  ::rust::String (*idalib_get_cmt$)(::c_ulonglong, bool) = ::idalib_get_cmt;
  new (return$) ::rust::String(idalib_get_cmt$(::std::move(*ea), rptble));
}

::std::uint32_t cxxbridge1$idalib_bookmarks_t_mark(::c_ulonglong *ea, ::c_uint *index, char const *desc) noexcept {
  ::std::uint32_t (*idalib_bookmarks_t_mark$)(::c_ulonglong, ::c_uint, char const *) = ::idalib_bookmarks_t_mark;
  return idalib_bookmarks_t_mark$(::std::move(*ea), ::std::move(*index), desc);
}

void cxxbridge1$idalib_bookmarks_t_get_desc(::c_uint *index, ::rust::String *return$) noexcept {
  ::rust::String (*idalib_bookmarks_t_get_desc$)(::c_uint) = ::idalib_bookmarks_t_get_desc;
  new (return$) ::rust::String(idalib_bookmarks_t_get_desc$(::std::move(*index)));
}

bool cxxbridge1$idalib_bookmarks_t_erase(::c_uint *index) noexcept {
  bool (*idalib_bookmarks_t_erase$)(::c_uint) = ::idalib_bookmarks_t_erase;
  return idalib_bookmarks_t_erase$(::std::move(*index));
}

::std::uint32_t cxxbridge1$idalib_bookmarks_t_size() noexcept {
  ::std::uint32_t (*idalib_bookmarks_t_size$)() = ::idalib_bookmarks_t_size;
  return idalib_bookmarks_t_size$();
}

::std::uint32_t cxxbridge1$idalib_bookmarks_t_find_index(::c_ulonglong *ea) noexcept {
  ::std::uint32_t (*idalib_bookmarks_t_find_index$)(::c_ulonglong) = ::idalib_bookmarks_t_find_index;
  return idalib_bookmarks_t_find_index$(::std::move(*ea));
}

::std::uint8_t cxxbridge1$idalib_get_byte(::c_ulonglong *ea) noexcept {
  ::std::uint8_t (*idalib_get_byte$)(::c_ulonglong) = ::idalib_get_byte;
  return idalib_get_byte$(::std::move(*ea));
}

::std::uint16_t cxxbridge1$idalib_get_word(::c_ulonglong *ea) noexcept {
  ::std::uint16_t (*idalib_get_word$)(::c_ulonglong) = ::idalib_get_word;
  return idalib_get_word$(::std::move(*ea));
}

::std::uint32_t cxxbridge1$idalib_get_dword(::c_ulonglong *ea) noexcept {
  ::std::uint32_t (*idalib_get_dword$)(::c_ulonglong) = ::idalib_get_dword;
  return idalib_get_dword$(::std::move(*ea));
}

::std::uint64_t cxxbridge1$idalib_get_qword(::c_ulonglong *ea) noexcept {
  ::std::uint64_t (*idalib_get_qword$)(::c_ulonglong) = ::idalib_get_qword;
  return idalib_get_qword$(::std::move(*ea));
}

::rust::repr::PtrLen cxxbridge1$idalib_get_bytes(::c_ulonglong *ea, ::rust::Vec<::std::uint8_t> &buf, ::std::size_t *return$) noexcept {
  ::std::size_t (*idalib_get_bytes$)(::c_ulonglong, ::rust::Vec<::std::uint8_t> &) = ::idalib_get_bytes;
  ::rust::repr::PtrLen throw$;
  ::rust::behavior::trycatch(
      [&] {
        new (return$) ::std::size_t(idalib_get_bytes$(::std::move(*ea), buf));
        throw$.ptr = nullptr;
      },
      ::rust::detail::Fail(throw$));
  return throw$;
}

::std::uint64_t cxxbridge1$idalib_plugin_version(::plugin_t const *p) noexcept {
  ::std::uint64_t (*idalib_plugin_version$)(::plugin_t const *) = ::idalib_plugin_version;
  return idalib_plugin_version$(p);
}

::std::uint64_t cxxbridge1$idalib_plugin_flags(::plugin_t const *p) noexcept {
  ::std::uint64_t (*idalib_plugin_flags$)(::plugin_t const *) = ::idalib_plugin_flags;
  return idalib_plugin_flags$(p);
}
} // extern "C"
