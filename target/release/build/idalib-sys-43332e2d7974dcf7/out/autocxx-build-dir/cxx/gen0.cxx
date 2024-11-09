#include "types.h"
#include "auto.hpp"
#include "bytes.hpp"
#include "entry.hpp"
#include "funcs.hpp"
#include "gdl.hpp"
#include "ida.hpp"
#include "idalib.hpp"
#include "idp.hpp"
#include "loader.hpp"
#include "moves.hpp"
#include "pro.h"
#include "segment.hpp"
#include "ua.hpp"
#include "xref.hpp"
#include "autocxxgen_ffi.h"
#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <new>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace rust {
inline namespace cxxbridge1 {
// #include "rust/cxx.h"

namespace {
template <typename T>
class impl;
} // namespace

class String;

#ifndef CXXBRIDGE1_RUST_STR
#define CXXBRIDGE1_RUST_STR
class Str final {
public:
  Str() noexcept;
  Str(const String &) noexcept;
  Str(const std::string &);
  Str(const char *);
  Str(const char *, std::size_t);

  Str &operator=(const Str &) &noexcept = default;

  explicit operator std::string() const;

  const char *data() const noexcept;
  std::size_t size() const noexcept;
  std::size_t length() const noexcept;
  bool empty() const noexcept;

  Str(const Str &) noexcept = default;
  ~Str() noexcept = default;

  using iterator = const char *;
  using const_iterator = const char *;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  bool operator==(const Str &) const noexcept;
  bool operator!=(const Str &) const noexcept;
  bool operator<(const Str &) const noexcept;
  bool operator<=(const Str &) const noexcept;
  bool operator>(const Str &) const noexcept;
  bool operator>=(const Str &) const noexcept;

  void swap(Str &) noexcept;

private:
  class uninit;
  Str(uninit) noexcept;
  friend impl<Str>;

  std::array<std::uintptr_t, 2> repr;
};
#endif // CXXBRIDGE1_RUST_STR

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

namespace detail {
template <typename T, typename = void *>
struct operator_new {
  void *operator()(::std::size_t sz) { return ::operator new(sz); }
};

template <typename T>
struct operator_new<T, decltype(T::operator new(sizeof(T)))> {
  void *operator()(::std::size_t sz) { return T::operator new(sz); }
};
} // namespace detail

template <typename T>
union MaybeUninit {
  T value;
  void *operator new(::std::size_t sz) { return detail::operator_new<T>{}(sz); }
  MaybeUninit() {}
  ~MaybeUninit() {}
};

namespace {
template <typename T>
void destroy(T *ptr) {
  ptr->~T();
}

template <bool> struct deleter_if {
  template <typename T> void operator()(T *) {}
};

template <> struct deleter_if<true> {
  template <typename T> void operator()(T *ptr) { ptr->~T(); }
};
} // namespace
} // namespace cxxbridge1
} // namespace rust

using gdl_graph_t = ::gdl_graph_t;
using qstring_char_AutocxxConcrete = ::qstring_char_AutocxxConcrete;
using reg_finder_t = ::reg_finder_t;

static_assert(
    ::rust::IsRelocatable<::fc_block_type_t>::value,
    "type fc_block_type_t should be trivially move constructible and trivially destructible in C++ to be used as a return value of `calc_block_type` in Rust");
static_assert(
    ::rust::IsRelocatable<::fpvalue_error_t>::value,
    "type fpvalue_error_t should be trivially move constructible and trivially destructible in C++ to be used as a return value of `realcvt_autocxx_wrapper_0x8d0b21477d8c77db` in Rust");
static_assert(
    ::rust::IsRelocatable<::c_ulonglong>::value,
    "type c_ulonglong should be trivially move constructible and trivially destructible in C++ to be used as an argument of `contains`, `extend`, `range_t_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db` or return value of `size`, `prev_head`, `next_head` in Rust");
static_assert(
    ::rust::IsRelocatable<::c_int>::value,
    "type c_int should be trivially move constructible and trivially destructible in C++ to be used as an argument of `nedge`, `edge`, `path_exists` or return value of `compare`, `func_t_compare_autocxx_wrapper_0x8d0b21477d8c77db`, `get_func_num` in Rust");
static_assert(
    ::rust::IsRelocatable<::c_uint>::value,
    "type c_uint should be trivially move constructible and trivially destructible in C++ to be used as a return value of `get_node_color_autocxx_wrapper_0x8d0b21477d8c77db`, `get_edge_color_autocxx_wrapper_0x8d0b21477d8c77db`, `processor_t_get_canon_feature_autocxx_wrapper_0x8d0b21477d8c77db` in Rust");
static_assert(
    ::rust::IsRelocatable<::c_ushort>::value,
    "type c_ushort should be trivially move constructible and trivially destructible in C++ to be used as an argument of `realcvt_autocxx_wrapper_0x8d0b21477d8c77db`, `processor_t_is_canon_insn_autocxx_wrapper_0x8d0b21477d8c77db`, `processor_t_get_canon_mnem_autocxx_wrapper_0x8d0b21477d8c77db` in Rust");

extern "C" {
::std::string *cxxbridge1$autocxx_make_string_0x8d0b21477d8c77db(::rust::Str str_) noexcept {
  ::std::unique_ptr<::std::string> (*autocxx_make_string_0x8d0b21477d8c77db$)(::rust::Str) = ::autocxx_make_string_0x8d0b21477d8c77db;
  return autocxx_make_string_0x8d0b21477d8c77db$(str_).release();
}

::range_t *cxxbridge1$range_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db() noexcept {
  ::range_t *(*range_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$)() = ::range_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db;
  return range_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$();
}

void cxxbridge1$range_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(::range_t *arg0) noexcept {
  void (*range_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$)(::range_t *) = ::range_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db;
  range_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$(arg0);
}

::range_t const *cxxbridge1$cast_func_t_to_range_t_autocxx_wrapper_0x8d0b21477d8c77db(::func_t const &autocxx_gen_this) noexcept {
  ::range_t const &(*cast_func_t_to_range_t_autocxx_wrapper_0x8d0b21477d8c77db$)(::func_t const &) = ::cast_func_t_to_range_t_autocxx_wrapper_0x8d0b21477d8c77db;
  return &cast_func_t_to_range_t_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this);
}

::func_t *cxxbridge1$func_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db() noexcept {
  ::func_t *(*func_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$)() = ::func_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db;
  return func_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$();
}

void cxxbridge1$func_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(::func_t *arg0) noexcept {
  void (*func_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$)(::func_t *) = ::func_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db;
  func_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$(arg0);
}

::lock_func *cxxbridge1$lock_func_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db() noexcept {
  ::lock_func *(*lock_func_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$)() = ::lock_func_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db;
  return lock_func_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$();
}

void cxxbridge1$lock_func_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(::lock_func *arg0) noexcept {
  void (*lock_func_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$)(::lock_func *) = ::lock_func_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db;
  lock_func_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$(arg0);
}

::gdl_graph_t *cxxbridge1$gdl_graph_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db() noexcept {
  ::gdl_graph_t *(*gdl_graph_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$)() = ::gdl_graph_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db;
  return gdl_graph_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$();
}

void cxxbridge1$gdl_graph_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(::gdl_graph_t *arg0) noexcept {
  void (*gdl_graph_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$)(::gdl_graph_t *) = ::gdl_graph_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db;
  gdl_graph_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$(arg0);
}

::range_t const *cxxbridge1$cast_qbasic_block_t_to_range_t_autocxx_wrapper_0x8d0b21477d8c77db(::qbasic_block_t const &autocxx_gen_this) noexcept {
  ::range_t const &(*cast_qbasic_block_t_to_range_t_autocxx_wrapper_0x8d0b21477d8c77db$)(::qbasic_block_t const &) = ::cast_qbasic_block_t_to_range_t_autocxx_wrapper_0x8d0b21477d8c77db;
  return &cast_qbasic_block_t_to_range_t_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this);
}

::qbasic_block_t *cxxbridge1$qbasic_block_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db() noexcept {
  ::qbasic_block_t *(*qbasic_block_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$)() = ::qbasic_block_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db;
  return qbasic_block_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$();
}

void cxxbridge1$qbasic_block_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(::qbasic_block_t *arg0) noexcept {
  void (*qbasic_block_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$)(::qbasic_block_t *) = ::qbasic_block_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db;
  qbasic_block_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$(arg0);
}

::qflow_chart_t *cxxbridge1$qflow_chart_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db() noexcept {
  ::qflow_chart_t *(*qflow_chart_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$)() = ::qflow_chart_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db;
  return qflow_chart_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$();
}

void cxxbridge1$qflow_chart_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(::qflow_chart_t *arg0) noexcept {
  void (*qflow_chart_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$)(::qflow_chart_t *) = ::qflow_chart_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db;
  qflow_chart_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$(arg0);
}

::range_t const *cxxbridge1$cast_segment_t_to_range_t_autocxx_wrapper_0x8d0b21477d8c77db(::segment_t const &autocxx_gen_this) noexcept {
  ::range_t const &(*cast_segment_t_to_range_t_autocxx_wrapper_0x8d0b21477d8c77db$)(::segment_t const &) = ::cast_segment_t_to_range_t_autocxx_wrapper_0x8d0b21477d8c77db;
  return &cast_segment_t_to_range_t_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this);
}

::segment_t *cxxbridge1$segment_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db() noexcept {
  ::segment_t *(*segment_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$)() = ::segment_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db;
  return segment_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$();
}

void cxxbridge1$segment_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(::segment_t *arg0) noexcept {
  void (*segment_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$)(::segment_t *) = ::segment_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db;
  segment_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$(arg0);
}

::lock_segment *cxxbridge1$lock_segment_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db() noexcept {
  ::lock_segment *(*lock_segment_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$)() = ::lock_segment_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db;
  return lock_segment_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$();
}

void cxxbridge1$lock_segment_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(::lock_segment *arg0) noexcept {
  void (*lock_segment_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$)(::lock_segment *) = ::lock_segment_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db;
  lock_segment_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$(arg0);
}

::xrefblk_t *cxxbridge1$xrefblk_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db() noexcept {
  ::xrefblk_t *(*xrefblk_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$)() = ::xrefblk_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db;
  return xrefblk_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$();
}

void cxxbridge1$xrefblk_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(::xrefblk_t *arg0) noexcept {
  void (*xrefblk_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$)(::xrefblk_t *) = ::xrefblk_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db;
  xrefblk_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$(arg0);
}

::processor_t *cxxbridge1$processor_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db() noexcept {
  ::processor_t *(*processor_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$)() = ::processor_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db;
  return processor_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$();
}

void cxxbridge1$processor_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(::processor_t *arg0) noexcept {
  void (*processor_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$)(::processor_t *) = ::processor_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db;
  processor_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$(arg0);
}

::plugin_t *cxxbridge1$plugin_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db() noexcept {
  ::plugin_t *(*plugin_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$)() = ::plugin_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db;
  return plugin_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$();
}

void cxxbridge1$plugin_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(::plugin_t *arg0) noexcept {
  void (*plugin_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$)(::plugin_t *) = ::plugin_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db;
  plugin_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$(arg0);
}

void cxxbridge1$range_t$compare(::range_t const &self, ::range_t const &r, ::c_int *return$) noexcept {
  ::c_int (::range_t::*compare$)(::range_t const &) const = &::range_t::compare;
  new (return$) ::c_int((self.*compare$)(r));
}

bool cxxbridge1$range_t$contains(::range_t const &self, ::c_ulonglong *ea) noexcept {
  bool (::range_t::*contains$)(::c_ulonglong) const = &::range_t::contains;
  return (self.*contains$)(::std::move(*ea));
}

bool cxxbridge1$range_t$contains1(::range_t const &self, ::range_t const &r) noexcept {
  bool (::range_t::*contains1$)(::range_t const &) const = &::range_t::contains;
  return (self.*contains1$)(r);
}

bool cxxbridge1$range_t$overlaps(::range_t const &self, ::range_t const &r) noexcept {
  bool (::range_t::*overlaps$)(::range_t const &) const = &::range_t::overlaps;
  return (self.*overlaps$)(r);
}

void cxxbridge1$range_t$clear(::range_t &self) noexcept {
  void (::range_t::*clear$)() = &::range_t::clear;
  (self.*clear$)();
}

bool cxxbridge1$range_t$empty(::range_t const &self) noexcept {
  bool (::range_t::*empty$)() const = &::range_t::empty;
  return (self.*empty$)();
}

void cxxbridge1$range_t$size(::range_t const &self, ::c_ulonglong *return$) noexcept {
  ::c_ulonglong (::range_t::*size$)() const = &::range_t::size;
  new (return$) ::c_ulonglong((self.*size$)());
}

void cxxbridge1$range_t$intersect(::range_t &self, ::range_t const &r) noexcept {
  void (::range_t::*intersect$)(::range_t const &) = &::range_t::intersect;
  (self.*intersect$)(r);
}

void cxxbridge1$range_t$extend(::range_t &self, ::c_ulonglong *ea) noexcept {
  void (::range_t::*extend$)(::c_ulonglong) = &::range_t::extend;
  (self.*extend$)(::std::move(*ea));
}

::std::size_t cxxbridge1$range_t$print(::range_t const &self, char *buf, ::std::size_t bufsize) noexcept {
  ::std::size_t (::range_t::*print$)(char *, ::std::size_t) const = &::range_t::print;
  return (self.*print$)(buf, bufsize);
}

void cxxbridge1$range_t_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db(::range_t *autocxx_gen_this, ::c_ulonglong *ea1, ::c_ulonglong *ea2) noexcept {
  void (*range_t_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db$)(::range_t *, ::c_ulonglong, ::c_ulonglong) = ::range_t_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db;
  range_t_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, ::std::move(*ea1), ::std::move(*ea2));
}

bool cxxbridge1$auto_wait() noexcept {
  bool (*auto_wait$)() = ::auto_wait;
  return auto_wait$();
}

void cxxbridge1$prev_head(::c_ulonglong *ea, ::c_ulonglong *minea, ::c_ulonglong *return$) noexcept {
  ::c_ulonglong (*prev_head$)(::c_ulonglong, ::c_ulonglong) = ::prev_head;
  new (return$) ::c_ulonglong(prev_head$(::std::move(*ea), ::std::move(*minea)));
}

void cxxbridge1$next_head(::c_ulonglong *ea, ::c_ulonglong *maxea, ::c_ulonglong *return$) noexcept {
  ::c_ulonglong (*next_head$)(::c_ulonglong, ::c_ulonglong) = ::next_head;
  new (return$) ::c_ulonglong(next_head$(::std::move(*ea), ::std::move(*maxea)));
}

bool cxxbridge1$set_cmt(::c_ulonglong *ea, char const *comm, bool rptble) noexcept {
  bool (*set_cmt$)(::c_ulonglong, char const *, bool) = ::set_cmt;
  return set_cmt$(::std::move(*ea), comm, rptble);
}

bool cxxbridge1$append_cmt(::c_ulonglong *ea, char const *str_, bool rptble) noexcept {
  bool (*append_cmt$)(::c_ulonglong, char const *, bool) = ::append_cmt;
  return append_cmt$(::std::move(*ea), str_, rptble);
}

::std::size_t cxxbridge1$get_entry_qty() noexcept {
  ::std::size_t (*get_entry_qty$)() = ::get_entry_qty;
  return get_entry_qty$();
}

void cxxbridge1$get_entry_ordinal(::std::size_t idx, ::c_ulonglong *return$) noexcept {
  ::c_ulonglong (*get_entry_ordinal$)(::std::size_t) = ::get_entry_ordinal;
  new (return$) ::c_ulonglong(get_entry_ordinal$(idx));
}

void cxxbridge1$get_entry(::c_ulonglong *ord, ::c_ulonglong *return$) noexcept {
  ::c_ulonglong (*get_entry$)(::c_ulonglong) = ::get_entry;
  new (return$) ::c_ulonglong(get_entry$(::std::move(*ord)));
}

bool cxxbridge1$func_t$is_far(::func_t const &self) noexcept {
  bool (::func_t::*is_far$)() const = &::func_t::is_far;
  return (self.*is_far$)();
}

bool cxxbridge1$func_t$does_return(::func_t const &self) noexcept {
  bool (::func_t::*does_return$)() const = &::func_t::does_return;
  return (self.*does_return$)();
}

bool cxxbridge1$func_t$analyzed_sp(::func_t const &self) noexcept {
  bool (::func_t::*analyzed_sp$)() const = &::func_t::analyzed_sp;
  return (self.*analyzed_sp$)();
}

bool cxxbridge1$func_t$need_prolog_analysis(::func_t const &self) noexcept {
  bool (::func_t::*need_prolog_analysis$)() const = &::func_t::need_prolog_analysis;
  return (self.*need_prolog_analysis$)();
}

void cxxbridge1$func_t_compare_autocxx_wrapper_0x8d0b21477d8c77db(::func_t const &autocxx_gen_this, ::func_t const &r, ::c_int *return$) noexcept {
  ::c_int (*func_t_compare_autocxx_wrapper_0x8d0b21477d8c77db$)(::func_t const &, ::func_t const &) = ::func_t_compare_autocxx_wrapper_0x8d0b21477d8c77db;
  new (return$) ::c_int(func_t_compare_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, r));
}

void cxxbridge1$func_t_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db(::func_t *autocxx_gen_this, ::c_ulonglong *start, ::c_ulonglong *end, ::c_ulonglong *f) noexcept {
  void (*func_t_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db$)(::func_t *, ::c_ulonglong, ::c_ulonglong, ::c_ulonglong) = ::func_t_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db;
  func_t_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, ::std::move(*start), ::std::move(*end), ::std::move(*f));
}

void cxxbridge1$lock_func_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db(::lock_func *autocxx_gen_this, ::func_t const *_pfn) noexcept {
  void (*lock_func_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db$)(::lock_func *, ::func_t const *) = ::lock_func_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db;
  lock_func_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, _pfn);
}

void cxxbridge1$lock_func_destructor_autocxx_wrapper_0x8d0b21477d8c77db(::lock_func *autocxx_gen_this) noexcept {
  void (*lock_func_destructor_autocxx_wrapper_0x8d0b21477d8c77db$)(::lock_func *) = ::lock_func_destructor_autocxx_wrapper_0x8d0b21477d8c77db;
  lock_func_destructor_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this);
}

::func_t *cxxbridge1$get_func(::c_ulonglong *ea) noexcept {
  ::func_t *(*get_func$)(::c_ulonglong) = ::get_func;
  return get_func$(::std::move(*ea));
}

::func_t *cxxbridge1$getn_func(::std::size_t n) noexcept {
  ::func_t *(*getn_func$)(::std::size_t) = ::getn_func;
  return getn_func$(n);
}

::std::size_t cxxbridge1$get_func_qty() noexcept {
  ::std::size_t (*get_func_qty$)() = ::get_func_qty;
  return get_func_qty$();
}

void cxxbridge1$get_func_num(::c_ulonglong *ea, ::c_int *return$) noexcept {
  ::c_int (*get_func_num$)(::c_ulonglong) = ::get_func_num;
  new (return$) ::c_int(get_func_num$(::std::move(*ea)));
}

void cxxbridge1$calc_thunk_func_target(::func_t *pfn, ::c_ulonglong *fptr, ::c_ulonglong *return$) noexcept {
  ::c_ulonglong (*calc_thunk_func_target$)(::func_t *, ::c_ulonglong *) = ::calc_thunk_func_target;
  new (return$) ::c_ulonglong(calc_thunk_func_target$(pfn, fptr));
}

void cxxbridge1$gdl_graph_t$gen_gdl(::gdl_graph_t const &self, ::_IO_FILE *fp) noexcept {
  void (::gdl_graph_t::*gen_gdl$)(::_IO_FILE *) const = &::gdl_graph_t::gen_gdl;
  (self.*gen_gdl$)(fp);
}

void cxxbridge1$gdl_graph_t$gen_gdl1(::gdl_graph_t const &self, char const *file) noexcept {
  void (::gdl_graph_t::*gen_gdl1$)(char const *) const = &::gdl_graph_t::gen_gdl;
  (self.*gen_gdl1$)(file);
}

::std::size_t cxxbridge1$gdl_graph_t$nedge(::gdl_graph_t const &self, ::c_int *node, bool ispred) noexcept {
  ::std::size_t (::gdl_graph_t::*nedge$)(::c_int, bool) const = &::gdl_graph_t::nedge;
  return (self.*nedge$)(::std::move(*node), ispred);
}

void cxxbridge1$gdl_graph_t$edge(::gdl_graph_t const &self, ::c_int *node, ::c_int *i, bool ispred, ::c_int *return$) noexcept {
  ::c_int (::gdl_graph_t::*edge$)(::c_int, ::c_int, bool) const = &::gdl_graph_t::edge;
  new (return$) ::c_int((self.*edge$)(::std::move(*node), ::std::move(*i), ispred));
}

void cxxbridge1$gdl_graph_t$front(::gdl_graph_t &self, ::c_int *return$) noexcept {
  ::c_int (::gdl_graph_t::*front$)() = &::gdl_graph_t::front;
  new (return$) ::c_int((self.*front$)());
}

void cxxbridge1$begin_autocxx_wrapper_0x8d0b21477d8c77db(::gdl_graph_t const &autocxx_gen_this, ::node_iterator *placement_return_type) noexcept {
  void (*begin_autocxx_wrapper_0x8d0b21477d8c77db$)(::gdl_graph_t const &, ::node_iterator *) = ::begin_autocxx_wrapper_0x8d0b21477d8c77db;
  begin_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, placement_return_type);
}

void cxxbridge1$gdl_graph_t_end_autocxx_wrapper_0x8d0b21477d8c77db(::gdl_graph_t const &autocxx_gen_this, ::node_iterator *placement_return_type) noexcept {
  void (*gdl_graph_t_end_autocxx_wrapper_0x8d0b21477d8c77db$)(::gdl_graph_t const &, ::node_iterator *) = ::gdl_graph_t_end_autocxx_wrapper_0x8d0b21477d8c77db;
  gdl_graph_t_end_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, placement_return_type);
}

bool cxxbridge1$gdl_graph_t$path_exists(::gdl_graph_t const &self, ::c_int *m, ::c_int *n) noexcept {
  bool (::gdl_graph_t::*path_exists$)(::c_int, ::c_int) const = &::gdl_graph_t::path_exists;
  return (self.*path_exists$)(::std::move(*m), ::std::move(*n));
}

void cxxbridge1$gdl_graph_t$gen_dot(::gdl_graph_t const &self, ::_IO_FILE *fp) noexcept {
  void (::gdl_graph_t::*gen_dot$)(::_IO_FILE *) const = &::gdl_graph_t::gen_dot;
  (self.*gen_dot$)(fp);
}

void cxxbridge1$gdl_graph_t$gen_dot1(::gdl_graph_t const &self, char const *file) noexcept {
  void (::gdl_graph_t::*gen_dot1$)(char const *) const = &::gdl_graph_t::gen_dot;
  (self.*gen_dot1$)(file);
}

void cxxbridge1$gdl_graph_t_destructor_autocxx_wrapper_0x8d0b21477d8c77db(::gdl_graph_t *autocxx_gen_this) noexcept {
  void (*gdl_graph_t_destructor_autocxx_wrapper_0x8d0b21477d8c77db$)(::gdl_graph_t *) = ::gdl_graph_t_destructor_autocxx_wrapper_0x8d0b21477d8c77db;
  gdl_graph_t_destructor_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this);
}

char *cxxbridge1$get_node_label_autocxx_wrapper_0x8d0b21477d8c77db(::gdl_graph_t const &autocxx_gen_this, char *iobuf, ::c_int *iobufsize, ::c_int *n) noexcept {
  char *(*get_node_label_autocxx_wrapper_0x8d0b21477d8c77db$)(::gdl_graph_t const &, char *, ::c_int, ::c_int) = ::get_node_label_autocxx_wrapper_0x8d0b21477d8c77db;
  return get_node_label_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, iobuf, ::std::move(*iobufsize), ::std::move(*n));
}

void cxxbridge1$print_graph_attributes_autocxx_wrapper_0x8d0b21477d8c77db(::gdl_graph_t const &autocxx_gen_this, ::_IO_FILE *fp) noexcept {
  void (*print_graph_attributes_autocxx_wrapper_0x8d0b21477d8c77db$)(::gdl_graph_t const &, ::_IO_FILE *) = ::print_graph_attributes_autocxx_wrapper_0x8d0b21477d8c77db;
  print_graph_attributes_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, fp);
}

bool cxxbridge1$print_node_autocxx_wrapper_0x8d0b21477d8c77db(::gdl_graph_t const &autocxx_gen_this, ::_IO_FILE *fp, ::c_int *n) noexcept {
  bool (*print_node_autocxx_wrapper_0x8d0b21477d8c77db$)(::gdl_graph_t const &, ::_IO_FILE *, ::c_int) = ::print_node_autocxx_wrapper_0x8d0b21477d8c77db;
  return print_node_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, fp, ::std::move(*n));
}

bool cxxbridge1$print_edge_autocxx_wrapper_0x8d0b21477d8c77db(::gdl_graph_t const &autocxx_gen_this, ::_IO_FILE *fp, ::c_int *i, ::c_int *j) noexcept {
  bool (*print_edge_autocxx_wrapper_0x8d0b21477d8c77db$)(::gdl_graph_t const &, ::_IO_FILE *, ::c_int, ::c_int) = ::print_edge_autocxx_wrapper_0x8d0b21477d8c77db;
  return print_edge_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, fp, ::std::move(*i), ::std::move(*j));
}

void cxxbridge1$print_node_attributes_autocxx_wrapper_0x8d0b21477d8c77db(::gdl_graph_t const &autocxx_gen_this, ::_IO_FILE *fp, ::c_int *n) noexcept {
  void (*print_node_attributes_autocxx_wrapper_0x8d0b21477d8c77db$)(::gdl_graph_t const &, ::_IO_FILE *, ::c_int) = ::print_node_attributes_autocxx_wrapper_0x8d0b21477d8c77db;
  print_node_attributes_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, fp, ::std::move(*n));
}

void cxxbridge1$gdl_graph_t_size_autocxx_wrapper_0x8d0b21477d8c77db(::gdl_graph_t const &autocxx_gen_this, ::c_int *return$) noexcept {
  ::c_int (*gdl_graph_t_size_autocxx_wrapper_0x8d0b21477d8c77db$)(::gdl_graph_t const &) = ::gdl_graph_t_size_autocxx_wrapper_0x8d0b21477d8c77db;
  new (return$) ::c_int(gdl_graph_t_size_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this));
}

void cxxbridge1$node_qty_autocxx_wrapper_0x8d0b21477d8c77db(::gdl_graph_t const &autocxx_gen_this, ::c_int *return$) noexcept {
  ::c_int (*node_qty_autocxx_wrapper_0x8d0b21477d8c77db$)(::gdl_graph_t const &) = ::node_qty_autocxx_wrapper_0x8d0b21477d8c77db;
  new (return$) ::c_int(node_qty_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this));
}

bool cxxbridge1$exists_autocxx_wrapper_0x8d0b21477d8c77db(::gdl_graph_t const &autocxx_gen_this, ::c_int *node) noexcept {
  bool (*exists_autocxx_wrapper_0x8d0b21477d8c77db$)(::gdl_graph_t const &, ::c_int) = ::exists_autocxx_wrapper_0x8d0b21477d8c77db;
  return exists_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, ::std::move(*node));
}

void cxxbridge1$entry_autocxx_wrapper_0x8d0b21477d8c77db(::gdl_graph_t const &autocxx_gen_this, ::c_int *return$) noexcept {
  ::c_int (*entry_autocxx_wrapper_0x8d0b21477d8c77db$)(::gdl_graph_t const &) = ::entry_autocxx_wrapper_0x8d0b21477d8c77db;
  new (return$) ::c_int(entry_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this));
}

void cxxbridge1$exit_autocxx_wrapper_0x8d0b21477d8c77db(::gdl_graph_t const &autocxx_gen_this, ::c_int *return$) noexcept {
  ::c_int (*exit_autocxx_wrapper_0x8d0b21477d8c77db$)(::gdl_graph_t const &) = ::exit_autocxx_wrapper_0x8d0b21477d8c77db;
  new (return$) ::c_int(exit_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this));
}

void cxxbridge1$nsucc_autocxx_wrapper_0x8d0b21477d8c77db(::gdl_graph_t const &autocxx_gen_this, ::c_int *node, ::c_int *return$) noexcept {
  ::c_int (*nsucc_autocxx_wrapper_0x8d0b21477d8c77db$)(::gdl_graph_t const &, ::c_int) = ::nsucc_autocxx_wrapper_0x8d0b21477d8c77db;
  new (return$) ::c_int(nsucc_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, ::std::move(*node)));
}

void cxxbridge1$npred_autocxx_wrapper_0x8d0b21477d8c77db(::gdl_graph_t const &autocxx_gen_this, ::c_int *node, ::c_int *return$) noexcept {
  ::c_int (*npred_autocxx_wrapper_0x8d0b21477d8c77db$)(::gdl_graph_t const &, ::c_int) = ::npred_autocxx_wrapper_0x8d0b21477d8c77db;
  new (return$) ::c_int(npred_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, ::std::move(*node)));
}

void cxxbridge1$succ_autocxx_wrapper_0x8d0b21477d8c77db(::gdl_graph_t const &autocxx_gen_this, ::c_int *node, ::c_int *i, ::c_int *return$) noexcept {
  ::c_int (*succ_autocxx_wrapper_0x8d0b21477d8c77db$)(::gdl_graph_t const &, ::c_int, ::c_int) = ::succ_autocxx_wrapper_0x8d0b21477d8c77db;
  new (return$) ::c_int(succ_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, ::std::move(*node), ::std::move(*i)));
}

void cxxbridge1$pred_autocxx_wrapper_0x8d0b21477d8c77db(::gdl_graph_t const &autocxx_gen_this, ::c_int *node, ::c_int *i, ::c_int *return$) noexcept {
  ::c_int (*pred_autocxx_wrapper_0x8d0b21477d8c77db$)(::gdl_graph_t const &, ::c_int, ::c_int) = ::pred_autocxx_wrapper_0x8d0b21477d8c77db;
  new (return$) ::c_int(pred_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, ::std::move(*node), ::std::move(*i)));
}

bool cxxbridge1$gdl_graph_t_empty_autocxx_wrapper_0x8d0b21477d8c77db(::gdl_graph_t const &autocxx_gen_this) noexcept {
  bool (*gdl_graph_t_empty_autocxx_wrapper_0x8d0b21477d8c77db$)(::gdl_graph_t const &) = ::gdl_graph_t_empty_autocxx_wrapper_0x8d0b21477d8c77db;
  return gdl_graph_t_empty_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this);
}

void cxxbridge1$get_node_color_autocxx_wrapper_0x8d0b21477d8c77db(::gdl_graph_t const &autocxx_gen_this, ::c_int *n, ::c_uint *return$) noexcept {
  ::c_uint (*get_node_color_autocxx_wrapper_0x8d0b21477d8c77db$)(::gdl_graph_t const &, ::c_int) = ::get_node_color_autocxx_wrapper_0x8d0b21477d8c77db;
  new (return$) ::c_uint(get_node_color_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, ::std::move(*n)));
}

void cxxbridge1$get_edge_color_autocxx_wrapper_0x8d0b21477d8c77db(::gdl_graph_t const &autocxx_gen_this, ::c_int *i, ::c_int *j, ::c_uint *return$) noexcept {
  ::c_uint (*get_edge_color_autocxx_wrapper_0x8d0b21477d8c77db$)(::gdl_graph_t const &, ::c_int, ::c_int) = ::get_edge_color_autocxx_wrapper_0x8d0b21477d8c77db;
  new (return$) ::c_uint(get_edge_color_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, ::std::move(*i), ::std::move(*j)));
}

void cxxbridge1$qflow_chart_t_create_autocxx_wrapper_0x8d0b21477d8c77db(::qflow_chart_t &autocxx_gen_this, char const *_title, ::func_t *_pfn, ::c_ulonglong *_ea1, ::c_ulonglong *_ea2, ::c_int *_flags) noexcept {
  void (*qflow_chart_t_create_autocxx_wrapper_0x8d0b21477d8c77db$)(::qflow_chart_t &, char const *, ::func_t *, ::c_ulonglong, ::c_ulonglong, ::c_int) = ::qflow_chart_t_create_autocxx_wrapper_0x8d0b21477d8c77db;
  qflow_chart_t_create_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, _title, _pfn, ::std::move(*_ea1), ::std::move(*_ea2), ::std::move(*_flags));
}

void cxxbridge1$qflow_chart_t_create1_autocxx_wrapper_0x8d0b21477d8c77db(::qflow_chart_t &autocxx_gen_this, char const *_title, ::rangevec_t const &ranges, ::c_int *_flags) noexcept {
  void (*qflow_chart_t_create1_autocxx_wrapper_0x8d0b21477d8c77db$)(::qflow_chart_t &, char const *, ::rangevec_t const &, ::c_int) = ::qflow_chart_t_create1_autocxx_wrapper_0x8d0b21477d8c77db;
  qflow_chart_t_create1_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, _title, ranges, ::std::move(*_flags));
}

void cxxbridge1$qflow_chart_t$append_to_flowchart(::qflow_chart_t &self, ::c_ulonglong *ea1, ::c_ulonglong *ea2) noexcept {
  void (::qflow_chart_t::*append_to_flowchart$)(::c_ulonglong, ::c_ulonglong) = &::qflow_chart_t::append_to_flowchart;
  (self.*append_to_flowchart$)(::std::move(*ea1), ::std::move(*ea2));
}

void cxxbridge1$qflow_chart_t$refresh(::qflow_chart_t &self) noexcept {
  void (::qflow_chart_t::*refresh$)() = &::qflow_chart_t::refresh;
  (self.*refresh$)();
}

void cxxbridge1$qflow_chart_t$calc_block_type(::qflow_chart_t const &self, ::std::size_t blknum, ::fc_block_type_t *return$) noexcept {
  ::fc_block_type_t (::qflow_chart_t::*calc_block_type$)(::std::size_t) const = &::qflow_chart_t::calc_block_type;
  new (return$) ::fc_block_type_t((self.*calc_block_type$)(blknum));
}

bool cxxbridge1$qflow_chart_t$is_ret_block(::qflow_chart_t const &self, ::std::size_t blknum) noexcept {
  bool (::qflow_chart_t::*is_ret_block$)(::std::size_t) const = &::qflow_chart_t::is_ret_block;
  return (self.*is_ret_block$)(blknum);
}

bool cxxbridge1$qflow_chart_t$is_noret_block(::qflow_chart_t const &self, ::std::size_t blknum) noexcept {
  bool (::qflow_chart_t::*is_noret_block$)(::std::size_t) const = &::qflow_chart_t::is_noret_block;
  return (self.*is_noret_block$)(blknum);
}

bool cxxbridge1$qflow_chart_t$print_names(::qflow_chart_t const &self) noexcept {
  bool (::qflow_chart_t::*print_names$)() const = &::qflow_chart_t::print_names;
  return (self.*print_names$)();
}

void cxxbridge1$qflow_chart_t_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db(::qflow_chart_t *autocxx_gen_this) noexcept {
  void (*qflow_chart_t_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db$)(::qflow_chart_t *) = ::qflow_chart_t_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db;
  qflow_chart_t_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this);
}

void cxxbridge1$qflow_chart_t_new1_autocxx_wrapper_0x8d0b21477d8c77db(::qflow_chart_t *autocxx_gen_this, char const *_title, ::func_t *_pfn, ::c_ulonglong *_ea1, ::c_ulonglong *_ea2, ::c_int *_flags) noexcept {
  void (*qflow_chart_t_new1_autocxx_wrapper_0x8d0b21477d8c77db$)(::qflow_chart_t *, char const *, ::func_t *, ::c_ulonglong, ::c_ulonglong, ::c_int) = ::qflow_chart_t_new1_autocxx_wrapper_0x8d0b21477d8c77db;
  qflow_chart_t_new1_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, _title, _pfn, ::std::move(*_ea1), ::std::move(*_ea2), ::std::move(*_flags));
}

void cxxbridge1$qflow_chart_t_destructor_autocxx_wrapper_0x8d0b21477d8c77db(::qflow_chart_t *autocxx_gen_this) noexcept {
  void (*qflow_chart_t_destructor_autocxx_wrapper_0x8d0b21477d8c77db$)(::qflow_chart_t *) = ::qflow_chart_t_destructor_autocxx_wrapper_0x8d0b21477d8c77db;
  qflow_chart_t_destructor_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this);
}

void cxxbridge1$qflow_chart_t_print_node_attributes_autocxx_wrapper_0x8d0b21477d8c77db(::qflow_chart_t const &autocxx_gen_this, ::_IO_FILE *fp, ::c_int *n) noexcept {
  void (*qflow_chart_t_print_node_attributes_autocxx_wrapper_0x8d0b21477d8c77db$)(::qflow_chart_t const &, ::_IO_FILE *, ::c_int) = ::qflow_chart_t_print_node_attributes_autocxx_wrapper_0x8d0b21477d8c77db;
  qflow_chart_t_print_node_attributes_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, fp, ::std::move(*n));
}

void cxxbridge1$qflow_chart_t_nsucc_autocxx_wrapper_0x8d0b21477d8c77db(::qflow_chart_t const &autocxx_gen_this, ::c_int *node, ::c_int *return$) noexcept {
  ::c_int (*qflow_chart_t_nsucc_autocxx_wrapper_0x8d0b21477d8c77db$)(::qflow_chart_t const &, ::c_int) = ::qflow_chart_t_nsucc_autocxx_wrapper_0x8d0b21477d8c77db;
  new (return$) ::c_int(qflow_chart_t_nsucc_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, ::std::move(*node)));
}

void cxxbridge1$qflow_chart_t_npred_autocxx_wrapper_0x8d0b21477d8c77db(::qflow_chart_t const &autocxx_gen_this, ::c_int *node, ::c_int *return$) noexcept {
  ::c_int (*qflow_chart_t_npred_autocxx_wrapper_0x8d0b21477d8c77db$)(::qflow_chart_t const &, ::c_int) = ::qflow_chart_t_npred_autocxx_wrapper_0x8d0b21477d8c77db;
  new (return$) ::c_int(qflow_chart_t_npred_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, ::std::move(*node)));
}

void cxxbridge1$qflow_chart_t_succ_autocxx_wrapper_0x8d0b21477d8c77db(::qflow_chart_t const &autocxx_gen_this, ::c_int *node, ::c_int *i, ::c_int *return$) noexcept {
  ::c_int (*qflow_chart_t_succ_autocxx_wrapper_0x8d0b21477d8c77db$)(::qflow_chart_t const &, ::c_int, ::c_int) = ::qflow_chart_t_succ_autocxx_wrapper_0x8d0b21477d8c77db;
  new (return$) ::c_int(qflow_chart_t_succ_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, ::std::move(*node), ::std::move(*i)));
}

void cxxbridge1$qflow_chart_t_pred_autocxx_wrapper_0x8d0b21477d8c77db(::qflow_chart_t const &autocxx_gen_this, ::c_int *node, ::c_int *i, ::c_int *return$) noexcept {
  ::c_int (*qflow_chart_t_pred_autocxx_wrapper_0x8d0b21477d8c77db$)(::qflow_chart_t const &, ::c_int, ::c_int) = ::qflow_chart_t_pred_autocxx_wrapper_0x8d0b21477d8c77db;
  new (return$) ::c_int(qflow_chart_t_pred_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, ::std::move(*node), ::std::move(*i)));
}

char *cxxbridge1$qflow_chart_t_get_node_label_autocxx_wrapper_0x8d0b21477d8c77db(::qflow_chart_t const &autocxx_gen_this, char *iobuf, ::c_int *iobufsize, ::c_int *n) noexcept {
  char *(*qflow_chart_t_get_node_label_autocxx_wrapper_0x8d0b21477d8c77db$)(::qflow_chart_t const &, char *, ::c_int, ::c_int) = ::qflow_chart_t_get_node_label_autocxx_wrapper_0x8d0b21477d8c77db;
  return qflow_chart_t_get_node_label_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, iobuf, ::std::move(*iobufsize), ::std::move(*n));
}

void cxxbridge1$qflow_chart_t_size_autocxx_wrapper_0x8d0b21477d8c77db(::qflow_chart_t const &autocxx_gen_this, ::c_int *return$) noexcept {
  ::c_int (*qflow_chart_t_size_autocxx_wrapper_0x8d0b21477d8c77db$)(::qflow_chart_t const &) = ::qflow_chart_t_size_autocxx_wrapper_0x8d0b21477d8c77db;
  new (return$) ::c_int(qflow_chart_t_size_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this));
}

void cxxbridge1$open_database(char const *file_path, bool run_auto, ::c_int *return$) noexcept {
  ::c_int (*open_database$)(char const *, bool) = ::open_database;
  new (return$) ::c_int(open_database$(file_path, run_auto));
}

void cxxbridge1$close_database(bool save) noexcept {
  void (*close_database$)(bool) = ::close_database;
  close_database$(save);
}

bool cxxbridge1$make_signatures(bool only_pat) noexcept {
  bool (*make_signatures$)(bool) = ::make_signatures;
  return make_signatures$(only_pat);
}

void cxxbridge1$enable_console_messages(bool enable) noexcept {
  void (*enable_console_messages$)(bool) = ::enable_console_messages;
  enable_console_messages$(enable);
}

void cxxbridge1$set_screen_ea(::c_ulonglong *ea) noexcept {
  void (*set_screen_ea$)(::c_ulonglong) = ::set_screen_ea;
  set_screen_ea$(::std::move(*ea));
}

bool cxxbridge1$segment_t$is_16bit(::segment_t const &self) noexcept {
  bool (::segment_t::*is_16bit$)() const = &::segment_t::is_16bit;
  return (self.*is_16bit$)();
}

bool cxxbridge1$segment_t$is_32bit(::segment_t const &self) noexcept {
  bool (::segment_t::*is_32bit$)() const = &::segment_t::is_32bit;
  return (self.*is_32bit$)();
}

bool cxxbridge1$segment_t$is_64bit(::segment_t const &self) noexcept {
  bool (::segment_t::*is_64bit$)() const = &::segment_t::is_64bit;
  return (self.*is_64bit$)();
}

void cxxbridge1$segment_t$abits(::segment_t const &self, ::c_int *return$) noexcept {
  ::c_int (::segment_t::*abits$)() const = &::segment_t::abits;
  new (return$) ::c_int((self.*abits$)());
}

void cxxbridge1$segment_t$abytes(::segment_t const &self, ::c_int *return$) noexcept {
  ::c_int (::segment_t::*abytes$)() const = &::segment_t::abytes;
  new (return$) ::c_int((self.*abytes$)());
}

bool cxxbridge1$segment_t$comorg(::segment_t const &self) noexcept {
  bool (::segment_t::*comorg$)() const = &::segment_t::comorg;
  return (self.*comorg$)();
}

void cxxbridge1$segment_t$set_comorg(::segment_t &self) noexcept {
  void (::segment_t::*set_comorg$)() = &::segment_t::set_comorg;
  (self.*set_comorg$)();
}

void cxxbridge1$segment_t$clr_comorg(::segment_t &self) noexcept {
  void (::segment_t::*clr_comorg$)() = &::segment_t::clr_comorg;
  (self.*clr_comorg$)();
}

bool cxxbridge1$segment_t$ob_ok(::segment_t const &self) noexcept {
  bool (::segment_t::*ob_ok$)() const = &::segment_t::ob_ok;
  return (self.*ob_ok$)();
}

void cxxbridge1$segment_t$set_ob_ok(::segment_t &self) noexcept {
  void (::segment_t::*set_ob_ok$)() = &::segment_t::set_ob_ok;
  (self.*set_ob_ok$)();
}

void cxxbridge1$segment_t$clr_ob_ok(::segment_t &self) noexcept {
  void (::segment_t::*clr_ob_ok$)() = &::segment_t::clr_ob_ok;
  (self.*clr_ob_ok$)();
}

bool cxxbridge1$segment_t$is_visible_segm(::segment_t const &self) noexcept {
  bool (::segment_t::*is_visible_segm$)() const = &::segment_t::is_visible_segm;
  return (self.*is_visible_segm$)();
}

void cxxbridge1$segment_t$set_visible_segm(::segment_t &self, bool visible) noexcept {
  void (::segment_t::*set_visible_segm$)(bool) = &::segment_t::set_visible_segm;
  (self.*set_visible_segm$)(visible);
}

bool cxxbridge1$segment_t$is_debugger_segm(::segment_t const &self) noexcept {
  bool (::segment_t::*is_debugger_segm$)() const = &::segment_t::is_debugger_segm;
  return (self.*is_debugger_segm$)();
}

void cxxbridge1$segment_t$set_debugger_segm(::segment_t &self, bool debseg) noexcept {
  void (::segment_t::*set_debugger_segm$)(bool) = &::segment_t::set_debugger_segm;
  (self.*set_debugger_segm$)(debseg);
}

bool cxxbridge1$segment_t$is_loader_segm(::segment_t const &self) noexcept {
  bool (::segment_t::*is_loader_segm$)() const = &::segment_t::is_loader_segm;
  return (self.*is_loader_segm$)();
}

void cxxbridge1$segment_t$set_loader_segm(::segment_t &self, bool ldrseg) noexcept {
  void (::segment_t::*set_loader_segm$)(bool) = &::segment_t::set_loader_segm;
  (self.*set_loader_segm$)(ldrseg);
}

bool cxxbridge1$segment_t$is_hidden_segtype(::segment_t const &self) noexcept {
  bool (::segment_t::*is_hidden_segtype$)() const = &::segment_t::is_hidden_segtype;
  return (self.*is_hidden_segtype$)();
}

void cxxbridge1$segment_t$set_hidden_segtype(::segment_t &self, bool hide) noexcept {
  void (::segment_t::*set_hidden_segtype$)(bool) = &::segment_t::set_hidden_segtype;
  (self.*set_hidden_segtype$)(hide);
}

bool cxxbridge1$segment_t$is_header_segm(::segment_t const &self) noexcept {
  bool (::segment_t::*is_header_segm$)() const = &::segment_t::is_header_segm;
  return (self.*is_header_segm$)();
}

void cxxbridge1$segment_t$set_header_segm(::segment_t &self, bool on) noexcept {
  void (::segment_t::*set_header_segm$)(bool) = &::segment_t::set_header_segm;
  (self.*set_header_segm$)(on);
}

bool cxxbridge1$segment_t$is_ephemeral_segm(::segment_t const &self) noexcept {
  bool (::segment_t::*is_ephemeral_segm$)() const = &::segment_t::is_ephemeral_segm;
  return (self.*is_ephemeral_segm$)();
}

bool cxxbridge1$segment_t$update(::segment_t &self) noexcept {
  bool (::segment_t::*update$)() = &::segment_t::update;
  return (self.*update$)();
}

void cxxbridge1$segment_t_compare_autocxx_wrapper_0x8d0b21477d8c77db(::segment_t const &autocxx_gen_this, ::segment_t const &r, ::c_int *return$) noexcept {
  ::c_int (*segment_t_compare_autocxx_wrapper_0x8d0b21477d8c77db$)(::segment_t const &, ::segment_t const &) = ::segment_t_compare_autocxx_wrapper_0x8d0b21477d8c77db;
  new (return$) ::c_int(segment_t_compare_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, r));
}

void cxxbridge1$segment_t_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db(::segment_t *autocxx_gen_this) noexcept {
  void (*segment_t_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db$)(::segment_t *) = ::segment_t_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db;
  segment_t_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this);
}

void cxxbridge1$lock_segment_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db(::lock_segment *autocxx_gen_this, ::segment_t const *_segm) noexcept {
  void (*lock_segment_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db$)(::lock_segment *, ::segment_t const *) = ::lock_segment_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db;
  lock_segment_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, _segm);
}

void cxxbridge1$lock_segment_destructor_autocxx_wrapper_0x8d0b21477d8c77db(::lock_segment *autocxx_gen_this) noexcept {
  void (*lock_segment_destructor_autocxx_wrapper_0x8d0b21477d8c77db$)(::lock_segment *) = ::lock_segment_destructor_autocxx_wrapper_0x8d0b21477d8c77db;
  lock_segment_destructor_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this);
}

void cxxbridge1$get_segm_qty(::c_int *return$) noexcept {
  ::c_int (*get_segm_qty$)() = ::get_segm_qty;
  new (return$) ::c_int(get_segm_qty$());
}

::segment_t *cxxbridge1$getseg(::c_ulonglong *ea) noexcept {
  ::segment_t *(*getseg$)(::c_ulonglong) = ::getseg;
  return getseg$(::std::move(*ea));
}

::segment_t *cxxbridge1$getnseg(::c_int *n) noexcept {
  ::segment_t *(*getnseg$)(::c_int) = ::getnseg;
  return getnseg$(::std::move(*n));
}

::segment_t *cxxbridge1$get_segm_by_name(char const *name) noexcept {
  ::segment_t *(*get_segm_by_name$)(char const *) = ::get_segm_by_name;
  return get_segm_by_name$(name);
}

bool cxxbridge1$xrefblk_t_first_from(::xrefblk_t *arg1, ::c_ulonglong *from, ::c_int *flags) noexcept {
  bool (*xrefblk_t_first_from$)(::xrefblk_t *, ::c_ulonglong, ::c_int) = ::xrefblk_t_first_from;
  return xrefblk_t_first_from$(arg1, ::std::move(*from), ::std::move(*flags));
}

bool cxxbridge1$xrefblk_t_next_from(::xrefblk_t *arg1) noexcept {
  bool (*xrefblk_t_next_from$)(::xrefblk_t *) = ::xrefblk_t_next_from;
  return xrefblk_t_next_from$(arg1);
}

bool cxxbridge1$xrefblk_t_first_to(::xrefblk_t *arg1, ::c_ulonglong *to, ::c_int *flags) noexcept {
  bool (*xrefblk_t_first_to$)(::xrefblk_t *, ::c_ulonglong, ::c_int) = ::xrefblk_t_first_to;
  return xrefblk_t_first_to$(arg1, ::std::move(*to), ::std::move(*flags));
}

bool cxxbridge1$xrefblk_t_next_to(::xrefblk_t *arg1) noexcept {
  bool (*xrefblk_t_next_to$)(::xrefblk_t *) = ::xrefblk_t_next_to;
  return xrefblk_t_next_to$(arg1);
}

bool cxxbridge1$xrefblk_t$first_from(::xrefblk_t &self, ::c_ulonglong *_from, ::c_int *flags) noexcept {
  bool (::xrefblk_t::*first_from$)(::c_ulonglong, ::c_int) = &::xrefblk_t::first_from;
  return (self.*first_from$)(::std::move(*_from), ::std::move(*flags));
}

bool cxxbridge1$xrefblk_t$first_to(::xrefblk_t &self, ::c_ulonglong *_to, ::c_int *flags) noexcept {
  bool (::xrefblk_t::*first_to$)(::c_ulonglong, ::c_int) = &::xrefblk_t::first_to;
  return (self.*first_to$)(::std::move(*_to), ::std::move(*flags));
}

bool cxxbridge1$has_external_refs(::func_t *pfn, ::c_ulonglong *ea) noexcept {
  bool (*has_external_refs$)(::func_t *, ::c_ulonglong) = ::has_external_refs;
  return has_external_refs$(pfn, ::std::move(*ea));
}

void cxxbridge1$decode_insn(::insn_t *out, ::c_ulonglong *ea, ::c_int *return$) noexcept {
  ::c_int (*decode_insn$)(::insn_t *, ::c_ulonglong) = ::decode_insn;
  new (return$) ::c_int(decode_insn$(out, ::std::move(*ea)));
}

bool cxxbridge1$is_call_insn(::insn_t const &insn) noexcept {
  bool (*is_call_insn$)(::insn_t const &) = ::is_call_insn;
  return is_call_insn$(insn);
}

bool cxxbridge1$is_ret_insn(::insn_t const &insn, ::std::uint8_t flags) noexcept {
  bool (*is_ret_insn$)(::insn_t const &, ::std::uint8_t) = ::is_ret_insn;
  return is_ret_insn$(insn, flags);
}

bool cxxbridge1$is_indirect_jump_insn(::insn_t const &insn) noexcept {
  bool (*is_indirect_jump_insn$)(::insn_t const &) = ::is_indirect_jump_insn;
  return is_indirect_jump_insn$(insn);
}

bool cxxbridge1$is_basic_block_end(::insn_t const &insn, bool call_insn_stops_block) noexcept {
  bool (*is_basic_block_end$)(::insn_t const &, bool) = ::is_basic_block_end;
  return is_basic_block_end$(insn, call_insn_stops_block);
}

bool cxxbridge1$processor_t$has_idp_opts(::processor_t const &self) noexcept {
  bool (::processor_t::*has_idp_opts$)() const = &::processor_t::has_idp_opts;
  return (self.*has_idp_opts$)();
}

bool cxxbridge1$processor_t$has_segregs(::processor_t const &self) noexcept {
  bool (::processor_t::*has_segregs$)() const = &::processor_t::has_segregs;
  return (self.*has_segregs$)();
}

bool cxxbridge1$processor_t$use32(::processor_t const &self) noexcept {
  bool (::processor_t::*use32$)() const = &::processor_t::use32;
  return (self.*use32$)();
}

bool cxxbridge1$processor_t$use64(::processor_t const &self) noexcept {
  bool (::processor_t::*use64$)() const = &::processor_t::use64;
  return (self.*use64$)();
}

bool cxxbridge1$processor_t$ti(::processor_t const &self) noexcept {
  bool (::processor_t::*ti$)() const = &::processor_t::ti;
  return (self.*ti$)();
}

bool cxxbridge1$processor_t$stkup(::processor_t const &self) noexcept {
  bool (::processor_t::*stkup$)() const = &::processor_t::stkup;
  return (self.*stkup$)();
}

bool cxxbridge1$processor_t$use_tbyte(::processor_t const &self) noexcept {
  bool (::processor_t::*use_tbyte$)() const = &::processor_t::use_tbyte;
  return (self.*use_tbyte$)();
}

bool cxxbridge1$processor_t$use_mappings(::processor_t const &self) noexcept {
  bool (::processor_t::*use_mappings$)() const = &::processor_t::use_mappings;
  return (self.*use_mappings$)();
}

bool cxxbridge1$processor_t$has_code16_bit(::processor_t const &self) noexcept {
  bool (::processor_t::*has_code16_bit$)() const = &::processor_t::has_code16_bit;
  return (self.*has_code16_bit$)();
}

bool cxxbridge1$processor_t$supports_macros(::processor_t const &self) noexcept {
  bool (::processor_t::*supports_macros$)() const = &::processor_t::supports_macros;
  return (self.*supports_macros$)();
}

bool cxxbridge1$processor_t$supports_calcrel(::processor_t const &self) noexcept {
  bool (::processor_t::*supports_calcrel$)() const = &::processor_t::supports_calcrel;
  return (self.*supports_calcrel$)();
}

bool cxxbridge1$processor_t$calcrel_in_bits(::processor_t const &self) noexcept {
  bool (::processor_t::*calcrel_in_bits$)() const = &::processor_t::calcrel_in_bits;
  return (self.*calcrel_in_bits$)();
}

void cxxbridge1$processor_t$get_default_segm_bitness(::processor_t const &self, bool is_64bit_app, ::c_int *return$) noexcept {
  ::c_int (::processor_t::*get_default_segm_bitness$)(bool) const = &::processor_t::get_default_segm_bitness;
  new (return$) ::c_int((self.*get_default_segm_bitness$)(is_64bit_app));
}

void cxxbridge1$processor_t$cbsize(::processor_t &self, ::c_int *return$) noexcept {
  ::c_int (::processor_t::*cbsize$)() = &::processor_t::cbsize;
  new (return$) ::c_int((self.*cbsize$)());
}

void cxxbridge1$processor_t$dbsize(::processor_t &self, ::c_int *return$) noexcept {
  ::c_int (::processor_t::*dbsize$)() = &::processor_t::dbsize;
  new (return$) ::c_int((self.*dbsize$)());
}

void cxxbridge1$processor_t$get_proc_index(::processor_t &self, ::c_int *return$) noexcept {
  ::c_int (::processor_t::*get_proc_index$)() = &::processor_t::get_proc_index;
  new (return$) ::c_int((self.*get_proc_index$)());
}

void cxxbridge1$auto_queue_empty_autocxx_wrapper_0x8d0b21477d8c77db(::c_int *type_) noexcept {
  void (*auto_queue_empty_autocxx_wrapper_0x8d0b21477d8c77db$)(::c_int) = ::auto_queue_empty_autocxx_wrapper_0x8d0b21477d8c77db;
  auto_queue_empty_autocxx_wrapper_0x8d0b21477d8c77db$(::std::move(*type_));
}

char const *cxxbridge1$set_idp_options_autocxx_wrapper_0x8d0b21477d8c77db(char const *keyword, ::c_int *vtype, ::c_void const *value, bool idb_loaded) noexcept {
  char const *(*set_idp_options_autocxx_wrapper_0x8d0b21477d8c77db$)(char const *, ::c_int, ::c_void const *, bool) = ::set_idp_options_autocxx_wrapper_0x8d0b21477d8c77db;
  return set_idp_options_autocxx_wrapper_0x8d0b21477d8c77db$(keyword, ::std::move(*vtype), value, idb_loaded);
}

void cxxbridge1$realcvt_autocxx_wrapper_0x8d0b21477d8c77db(::c_void *m, ::fpvalue_t *e, ::c_ushort *swt, ::fpvalue_error_t *return$) noexcept {
  ::fpvalue_error_t (*realcvt_autocxx_wrapper_0x8d0b21477d8c77db$)(::c_void *, ::fpvalue_t *, ::c_ushort) = ::realcvt_autocxx_wrapper_0x8d0b21477d8c77db;
  new (return$) ::fpvalue_error_t(realcvt_autocxx_wrapper_0x8d0b21477d8c77db$(m, e, ::std::move(*swt)));
}

bool cxxbridge1$processor_t$delay_slot_insn(::processor_t &self, ::c_ulonglong *ea, bool *bexec, bool *fexec) noexcept {
  bool (::processor_t::*delay_slot_insn$)(::c_ulonglong *, bool *, bool *) = &::processor_t::delay_slot_insn;
  return (self.*delay_slot_insn$)(ea, bexec, fexec);
}

bool cxxbridge1$get_code16_mode_autocxx_wrapper_0x8d0b21477d8c77db(::c_ulonglong *ea) noexcept {
  bool (*get_code16_mode_autocxx_wrapper_0x8d0b21477d8c77db$)(::c_ulonglong) = ::get_code16_mode_autocxx_wrapper_0x8d0b21477d8c77db;
  return get_code16_mode_autocxx_wrapper_0x8d0b21477d8c77db$(::std::move(*ea));
}

char const *cxxbridge1$get_reg_info_autocxx_wrapper_0x8d0b21477d8c77db(char const *regname, ::bitrange_t *bitrange) noexcept {
  char const *(*get_reg_info_autocxx_wrapper_0x8d0b21477d8c77db$)(char const *, ::bitrange_t *) = ::get_reg_info_autocxx_wrapper_0x8d0b21477d8c77db;
  return get_reg_info_autocxx_wrapper_0x8d0b21477d8c77db$(regname, bitrange);
}

::reg_finder_t *cxxbridge1$get_regfinder_autocxx_wrapper_0x8d0b21477d8c77db() noexcept {
  ::reg_finder_t *(*get_regfinder_autocxx_wrapper_0x8d0b21477d8c77db$)() = ::get_regfinder_autocxx_wrapper_0x8d0b21477d8c77db;
  return get_regfinder_autocxx_wrapper_0x8d0b21477d8c77db$();
}

void cxxbridge1$processor_t$get_stkvar_scale(::processor_t &self, ::c_int *return$) noexcept {
  ::c_int (::processor_t::*get_stkvar_scale$)() = &::processor_t::get_stkvar_scale;
  new (return$) ::c_int((self.*get_stkvar_scale$)());
}

bool cxxbridge1$processor_t_is_canon_insn_autocxx_wrapper_0x8d0b21477d8c77db(::processor_t const &autocxx_gen_this, ::c_ushort *itype) noexcept {
  bool (*processor_t_is_canon_insn_autocxx_wrapper_0x8d0b21477d8c77db$)(::processor_t const &, ::c_ushort) = ::processor_t_is_canon_insn_autocxx_wrapper_0x8d0b21477d8c77db;
  return processor_t_is_canon_insn_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, ::std::move(*itype));
}

char const *cxxbridge1$processor_t_get_canon_mnem_autocxx_wrapper_0x8d0b21477d8c77db(::processor_t const &autocxx_gen_this, ::c_ushort *itype) noexcept {
  char const *(*processor_t_get_canon_mnem_autocxx_wrapper_0x8d0b21477d8c77db$)(::processor_t const &, ::c_ushort) = ::processor_t_get_canon_mnem_autocxx_wrapper_0x8d0b21477d8c77db;
  return processor_t_get_canon_mnem_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, ::std::move(*itype));
}

void cxxbridge1$processor_t_get_canon_feature_autocxx_wrapper_0x8d0b21477d8c77db(::processor_t const &autocxx_gen_this, ::c_ushort *itype, ::c_uint *return$) noexcept {
  ::c_uint (*processor_t_get_canon_feature_autocxx_wrapper_0x8d0b21477d8c77db$)(::processor_t const &, ::c_ushort) = ::processor_t_get_canon_feature_autocxx_wrapper_0x8d0b21477d8c77db;
  new (return$) ::c_uint(processor_t_get_canon_feature_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, ::std::move(*itype)));
}

::std::size_t cxxbridge1$processor_t$sizeof_ldbl(::processor_t const &self) noexcept {
  ::std::size_t (::processor_t::*sizeof_ldbl$)() const = &::processor_t::sizeof_ldbl;
  return (self.*sizeof_ldbl$)();
}

::processor_t *cxxbridge1$get_ph() noexcept {
  ::processor_t *(*get_ph$)() = ::get_ph;
  return get_ph$();
}

void cxxbridge1$str2reg_autocxx1(char const *p, ::c_int *return$) noexcept {
  ::c_int (*str2reg_autocxx1$)(char const *) = ::str2reg;
  new (return$) ::c_int(str2reg_autocxx1$(p));
}

void cxxbridge1$is_align_insn_autocxx1(::c_ulonglong *ea, ::c_int *return$) noexcept {
  ::c_int (*is_align_insn_autocxx1$)(::c_ulonglong) = ::is_align_insn;
  new (return$) ::c_int(is_align_insn_autocxx1$(::std::move(*ea)));
}

::plugin_t *cxxbridge1$find_plugin(char const *name, bool load_if_needed) noexcept {
  ::plugin_t *(*find_plugin$)(char const *, bool) = ::find_plugin;
  return find_plugin$(name, load_if_needed);
}

bool cxxbridge1$run_plugin(::plugin_t const *ptr, ::std::size_t arg) noexcept {
  bool (*run_plugin$)(::plugin_t const *, ::std::size_t) = ::run_plugin;
  return run_plugin$(ptr, arg);
}

void cxxbridge1$range_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(::range_t *autocxx_gen_this, ::range_t *other) noexcept {
  void (*range_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$)(::range_t *, ::range_t *) = ::range_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db;
  range_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, other);
}

void cxxbridge1$range_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(::range_t *autocxx_gen_this, ::range_t const &other) noexcept {
  void (*range_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$)(::range_t *, ::range_t const &) = ::range_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db;
  range_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, other);
}

void cxxbridge1$range_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(::range_t *autocxx_gen_this) noexcept {
  void (*range_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$)(::range_t *) = ::range_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db;
  range_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this);
}

void cxxbridge1$func_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(::func_t *autocxx_gen_this, ::func_t *other) noexcept {
  void (*func_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$)(::func_t *, ::func_t *) = ::func_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db;
  func_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, other);
}

void cxxbridge1$func_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(::func_t *autocxx_gen_this, ::func_t const &other) noexcept {
  void (*func_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$)(::func_t *, ::func_t const &) = ::func_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db;
  func_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, other);
}

void cxxbridge1$func_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(::func_t *autocxx_gen_this) noexcept {
  void (*func_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$)(::func_t *) = ::func_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db;
  func_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this);
}

void cxxbridge1$lock_func_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(::lock_func *autocxx_gen_this, ::lock_func const &other) noexcept {
  void (*lock_func_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$)(::lock_func *, ::lock_func const &) = ::lock_func_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db;
  lock_func_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, other);
}

void cxxbridge1$segment_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(::segment_t *autocxx_gen_this, ::segment_t *other) noexcept {
  void (*segment_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$)(::segment_t *, ::segment_t *) = ::segment_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db;
  segment_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, other);
}

void cxxbridge1$segment_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(::segment_t *autocxx_gen_this, ::segment_t const &other) noexcept {
  void (*segment_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$)(::segment_t *, ::segment_t const &) = ::segment_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db;
  segment_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, other);
}

void cxxbridge1$segment_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(::segment_t *autocxx_gen_this) noexcept {
  void (*segment_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$)(::segment_t *) = ::segment_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db;
  segment_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this);
}

void cxxbridge1$lock_segment_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(::lock_segment *autocxx_gen_this, ::lock_segment const &other) noexcept {
  void (*lock_segment_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$)(::lock_segment *, ::lock_segment const &) = ::lock_segment_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db;
  lock_segment_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, other);
}

void cxxbridge1$xrefblk_t_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db(::xrefblk_t *autocxx_gen_this) noexcept {
  void (*xrefblk_t_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db$)(::xrefblk_t *) = ::xrefblk_t_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db;
  xrefblk_t_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this);
}

void cxxbridge1$xrefblk_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(::xrefblk_t *autocxx_gen_this, ::xrefblk_t *other) noexcept {
  void (*xrefblk_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$)(::xrefblk_t *, ::xrefblk_t *) = ::xrefblk_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db;
  xrefblk_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, other);
}

void cxxbridge1$xrefblk_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(::xrefblk_t *autocxx_gen_this, ::xrefblk_t const &other) noexcept {
  void (*xrefblk_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$)(::xrefblk_t *, ::xrefblk_t const &) = ::xrefblk_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db;
  xrefblk_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, other);
}

void cxxbridge1$xrefblk_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(::xrefblk_t *autocxx_gen_this) noexcept {
  void (*xrefblk_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$)(::xrefblk_t *) = ::xrefblk_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db;
  xrefblk_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this);
}

void cxxbridge1$processor_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(::processor_t *autocxx_gen_this) noexcept {
  void (*processor_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$)(::processor_t *) = ::processor_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db;
  processor_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this);
}

void cxxbridge1$plugin_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(::plugin_t *autocxx_gen_this, ::plugin_t *other) noexcept {
  void (*plugin_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$)(::plugin_t *, ::plugin_t *) = ::plugin_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db;
  plugin_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, other);
}

void cxxbridge1$plugin_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(::plugin_t *autocxx_gen_this, ::plugin_t const &other) noexcept {
  void (*plugin_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$)(::plugin_t *, ::plugin_t const &) = ::plugin_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db;
  plugin_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, other);
}

void cxxbridge1$plugin_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(::plugin_t *autocxx_gen_this) noexcept {
  void (*plugin_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$)(::plugin_t *) = ::plugin_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db;
  plugin_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this);
}

void cxxbridge1$qbasic_block_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(::qbasic_block_t *autocxx_gen_this) noexcept {
  void (*qbasic_block_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$)(::qbasic_block_t *) = ::qbasic_block_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db;
  qbasic_block_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this);
}

::_IO_FILE *cxxbridge1$_IO_FILE_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db() noexcept {
  ::_IO_FILE *(*_IO_FILE_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$)() = ::_IO_FILE_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db;
  return _IO_FILE_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$();
}

void cxxbridge1$_IO_FILE_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(::_IO_FILE *arg0) noexcept {
  void (*_IO_FILE_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$)(::_IO_FILE *) = ::_IO_FILE_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db;
  _IO_FILE_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$(arg0);
}

void cxxbridge1$_IO_FILE_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(::_IO_FILE *autocxx_gen_this, ::_IO_FILE *other) noexcept {
  void (*_IO_FILE_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$)(::_IO_FILE *, ::_IO_FILE *) = ::_IO_FILE_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db;
  _IO_FILE_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, other);
}

void cxxbridge1$_IO_FILE_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(::_IO_FILE *autocxx_gen_this, ::_IO_FILE const &other) noexcept {
  void (*_IO_FILE_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$)(::_IO_FILE *, ::_IO_FILE const &) = ::_IO_FILE_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db;
  _IO_FILE_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, other);
}

::node_iterator *cxxbridge1$node_iterator_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db() noexcept {
  ::node_iterator *(*node_iterator_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$)() = ::node_iterator_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db;
  return node_iterator_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$();
}

void cxxbridge1$node_iterator_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(::node_iterator *arg0) noexcept {
  void (*node_iterator_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$)(::node_iterator *) = ::node_iterator_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db;
  node_iterator_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$(arg0);
}

void cxxbridge1$node_iterator_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(::node_iterator *autocxx_gen_this, ::node_iterator *other) noexcept {
  void (*node_iterator_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$)(::node_iterator *, ::node_iterator *) = ::node_iterator_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db;
  node_iterator_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, other);
}

void cxxbridge1$node_iterator_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(::node_iterator *autocxx_gen_this, ::node_iterator const &other) noexcept {
  void (*node_iterator_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$)(::node_iterator *, ::node_iterator const &) = ::node_iterator_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db;
  node_iterator_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, other);
}

::rangevec_t *cxxbridge1$rangevec_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db() noexcept {
  ::rangevec_t *(*rangevec_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$)() = ::rangevec_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db;
  return rangevec_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$();
}

void cxxbridge1$rangevec_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(::rangevec_t *arg0) noexcept {
  void (*rangevec_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$)(::rangevec_t *) = ::rangevec_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db;
  rangevec_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$(arg0);
}

::fpvalue_t *cxxbridge1$fpvalue_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db() noexcept {
  ::fpvalue_t *(*fpvalue_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$)() = ::fpvalue_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db;
  return fpvalue_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$();
}

void cxxbridge1$fpvalue_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(::fpvalue_t *arg0) noexcept {
  void (*fpvalue_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$)(::fpvalue_t *) = ::fpvalue_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db;
  fpvalue_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$(arg0);
}

void cxxbridge1$fpvalue_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(::fpvalue_t *autocxx_gen_this, ::fpvalue_t *other) noexcept {
  void (*fpvalue_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$)(::fpvalue_t *, ::fpvalue_t *) = ::fpvalue_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db;
  fpvalue_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, other);
}

void cxxbridge1$fpvalue_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(::fpvalue_t *autocxx_gen_this, ::fpvalue_t const &other) noexcept {
  void (*fpvalue_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$)(::fpvalue_t *, ::fpvalue_t const &) = ::fpvalue_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db;
  fpvalue_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, other);
}

::bitrange_t *cxxbridge1$bitrange_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db() noexcept {
  ::bitrange_t *(*bitrange_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$)() = ::bitrange_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db;
  return bitrange_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db$();
}

void cxxbridge1$bitrange_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(::bitrange_t *arg0) noexcept {
  void (*bitrange_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$)(::bitrange_t *) = ::bitrange_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db;
  bitrange_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db$(arg0);
}

void cxxbridge1$bitrange_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(::bitrange_t *autocxx_gen_this, ::bitrange_t *other) noexcept {
  void (*bitrange_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$)(::bitrange_t *, ::bitrange_t *) = ::bitrange_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db;
  bitrange_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, other);
}

void cxxbridge1$bitrange_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(::bitrange_t *autocxx_gen_this, ::bitrange_t const &other) noexcept {
  void (*bitrange_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$)(::bitrange_t *, ::bitrange_t const &) = ::bitrange_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db;
  bitrange_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db$(autocxx_gen_this, other);
}

static_assert(::rust::detail::is_complete<::range_t>::value, "definition of range_t is required");
static_assert(sizeof(::std::unique_ptr<::range_t>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::range_t>) == alignof(void *), "");
void cxxbridge1$unique_ptr$range_t$null(::std::unique_ptr<::range_t> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::range_t>();
}
::range_t *cxxbridge1$unique_ptr$range_t$uninit(::std::unique_ptr<::range_t> *ptr) noexcept {
  ::range_t *uninit = reinterpret_cast<::range_t *>(new ::rust::MaybeUninit<::range_t>);
  ::new (ptr) ::std::unique_ptr<::range_t>(uninit);
  return uninit;
}
void cxxbridge1$unique_ptr$range_t$raw(::std::unique_ptr<::range_t> *ptr, ::range_t *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::range_t>(raw);
}
::range_t const *cxxbridge1$unique_ptr$range_t$get(::std::unique_ptr<::range_t> const &ptr) noexcept {
  return ptr.get();
}
::range_t *cxxbridge1$unique_ptr$range_t$release(::std::unique_ptr<::range_t> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$range_t$drop(::std::unique_ptr<::range_t> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::range_t>::value>{}(ptr);
}

static_assert(sizeof(::std::shared_ptr<::range_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::shared_ptr<::range_t>) == alignof(void *), "");
void cxxbridge1$shared_ptr$range_t$null(::std::shared_ptr<::range_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::range_t>();
}
::range_t *cxxbridge1$shared_ptr$range_t$uninit(::std::shared_ptr<::range_t> *ptr) noexcept {
  ::range_t *uninit = reinterpret_cast<::range_t *>(new ::rust::MaybeUninit<::range_t>);
  ::new (ptr) ::std::shared_ptr<::range_t>(uninit);
  return uninit;
}
void cxxbridge1$shared_ptr$range_t$clone(::std::shared_ptr<::range_t> const &self, ::std::shared_ptr<::range_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::range_t>(self);
}
::range_t const *cxxbridge1$shared_ptr$range_t$get(::std::shared_ptr<::range_t> const &self) noexcept {
  return self.get();
}
void cxxbridge1$shared_ptr$range_t$drop(::std::shared_ptr<::range_t> *self) noexcept {
  self->~shared_ptr();
}

static_assert(sizeof(::std::weak_ptr<::range_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::weak_ptr<::range_t>) == alignof(void *), "");
void cxxbridge1$weak_ptr$range_t$null(::std::weak_ptr<::range_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::range_t>();
}
void cxxbridge1$weak_ptr$range_t$clone(::std::weak_ptr<::range_t> const &self, ::std::weak_ptr<::range_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::range_t>(self);
}
void cxxbridge1$weak_ptr$range_t$downgrade(::std::shared_ptr<::range_t> const &shared, ::std::weak_ptr<::range_t> *weak) noexcept {
  ::new (weak) ::std::weak_ptr<::range_t>(shared);
}
void cxxbridge1$weak_ptr$range_t$upgrade(::std::weak_ptr<::range_t> const &weak, ::std::shared_ptr<::range_t> *shared) noexcept {
  ::new (shared) ::std::shared_ptr<::range_t>(weak.lock());
}
void cxxbridge1$weak_ptr$range_t$drop(::std::weak_ptr<::range_t> *self) noexcept {
  self->~weak_ptr();
}

::std::vector<::range_t> *cxxbridge1$std$vector$range_t$new() noexcept {
  return new ::std::vector<::range_t>();
}
::std::size_t cxxbridge1$std$vector$range_t$size(::std::vector<::range_t> const &s) noexcept {
  return s.size();
}
::range_t *cxxbridge1$std$vector$range_t$get_unchecked(::std::vector<::range_t> *s, ::std::size_t pos) noexcept {
  return &(*s)[pos];
}
void cxxbridge1$std$vector$range_t$push_back(::std::vector<::range_t> *v, ::range_t *value) noexcept {
  v->push_back(::std::move(*value));
  ::rust::destroy(value);
}
void cxxbridge1$std$vector$range_t$pop_back(::std::vector<::range_t> *v, ::range_t *out) noexcept {
  ::new (out) ::range_t(::std::move(v->back()));
  v->pop_back();
}
static_assert(sizeof(::std::unique_ptr<::std::vector<::range_t>>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::std::vector<::range_t>>) == alignof(void *), "");
void cxxbridge1$unique_ptr$std$vector$range_t$null(::std::unique_ptr<::std::vector<::range_t>> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::std::vector<::range_t>>();
}
void cxxbridge1$unique_ptr$std$vector$range_t$raw(::std::unique_ptr<::std::vector<::range_t>> *ptr, ::std::vector<::range_t> *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::std::vector<::range_t>>(raw);
}
::std::vector<::range_t> const *cxxbridge1$unique_ptr$std$vector$range_t$get(::std::unique_ptr<::std::vector<::range_t>> const &ptr) noexcept {
  return ptr.get();
}
::std::vector<::range_t> *cxxbridge1$unique_ptr$std$vector$range_t$release(::std::unique_ptr<::std::vector<::range_t>> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$std$vector$range_t$drop(::std::unique_ptr<::std::vector<::range_t>> *ptr) noexcept {
  ptr->~unique_ptr();
}

static_assert(::rust::detail::is_complete<::filetype_t>::value, "definition of filetype_t is required");
static_assert(sizeof(::std::unique_ptr<::filetype_t>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::filetype_t>) == alignof(void *), "");
void cxxbridge1$unique_ptr$filetype_t$null(::std::unique_ptr<::filetype_t> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::filetype_t>();
}
::filetype_t *cxxbridge1$unique_ptr$filetype_t$uninit(::std::unique_ptr<::filetype_t> *ptr) noexcept {
  ::filetype_t *uninit = reinterpret_cast<::filetype_t *>(new ::rust::MaybeUninit<::filetype_t>);
  ::new (ptr) ::std::unique_ptr<::filetype_t>(uninit);
  return uninit;
}
void cxxbridge1$unique_ptr$filetype_t$raw(::std::unique_ptr<::filetype_t> *ptr, ::filetype_t *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::filetype_t>(raw);
}
::filetype_t const *cxxbridge1$unique_ptr$filetype_t$get(::std::unique_ptr<::filetype_t> const &ptr) noexcept {
  return ptr.get();
}
::filetype_t *cxxbridge1$unique_ptr$filetype_t$release(::std::unique_ptr<::filetype_t> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$filetype_t$drop(::std::unique_ptr<::filetype_t> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::filetype_t>::value>{}(ptr);
}

static_assert(sizeof(::std::shared_ptr<::filetype_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::shared_ptr<::filetype_t>) == alignof(void *), "");
void cxxbridge1$shared_ptr$filetype_t$null(::std::shared_ptr<::filetype_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::filetype_t>();
}
::filetype_t *cxxbridge1$shared_ptr$filetype_t$uninit(::std::shared_ptr<::filetype_t> *ptr) noexcept {
  ::filetype_t *uninit = reinterpret_cast<::filetype_t *>(new ::rust::MaybeUninit<::filetype_t>);
  ::new (ptr) ::std::shared_ptr<::filetype_t>(uninit);
  return uninit;
}
void cxxbridge1$shared_ptr$filetype_t$clone(::std::shared_ptr<::filetype_t> const &self, ::std::shared_ptr<::filetype_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::filetype_t>(self);
}
::filetype_t const *cxxbridge1$shared_ptr$filetype_t$get(::std::shared_ptr<::filetype_t> const &self) noexcept {
  return self.get();
}
void cxxbridge1$shared_ptr$filetype_t$drop(::std::shared_ptr<::filetype_t> *self) noexcept {
  self->~shared_ptr();
}

static_assert(sizeof(::std::weak_ptr<::filetype_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::weak_ptr<::filetype_t>) == alignof(void *), "");
void cxxbridge1$weak_ptr$filetype_t$null(::std::weak_ptr<::filetype_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::filetype_t>();
}
void cxxbridge1$weak_ptr$filetype_t$clone(::std::weak_ptr<::filetype_t> const &self, ::std::weak_ptr<::filetype_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::filetype_t>(self);
}
void cxxbridge1$weak_ptr$filetype_t$downgrade(::std::shared_ptr<::filetype_t> const &shared, ::std::weak_ptr<::filetype_t> *weak) noexcept {
  ::new (weak) ::std::weak_ptr<::filetype_t>(shared);
}
void cxxbridge1$weak_ptr$filetype_t$upgrade(::std::weak_ptr<::filetype_t> const &weak, ::std::shared_ptr<::filetype_t> *shared) noexcept {
  ::new (shared) ::std::shared_ptr<::filetype_t>(weak.lock());
}
void cxxbridge1$weak_ptr$filetype_t$drop(::std::weak_ptr<::filetype_t> *self) noexcept {
  self->~weak_ptr();
}

::std::vector<::filetype_t> *cxxbridge1$std$vector$filetype_t$new() noexcept {
  return new ::std::vector<::filetype_t>();
}
::std::size_t cxxbridge1$std$vector$filetype_t$size(::std::vector<::filetype_t> const &s) noexcept {
  return s.size();
}
::filetype_t *cxxbridge1$std$vector$filetype_t$get_unchecked(::std::vector<::filetype_t> *s, ::std::size_t pos) noexcept {
  return &(*s)[pos];
}
void cxxbridge1$std$vector$filetype_t$push_back(::std::vector<::filetype_t> *v, ::filetype_t *value) noexcept {
  v->push_back(::std::move(*value));
  ::rust::destroy(value);
}
void cxxbridge1$std$vector$filetype_t$pop_back(::std::vector<::filetype_t> *v, ::filetype_t *out) noexcept {
  ::new (out) ::filetype_t(::std::move(v->back()));
  v->pop_back();
}
static_assert(sizeof(::std::unique_ptr<::std::vector<::filetype_t>>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::std::vector<::filetype_t>>) == alignof(void *), "");
void cxxbridge1$unique_ptr$std$vector$filetype_t$null(::std::unique_ptr<::std::vector<::filetype_t>> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::std::vector<::filetype_t>>();
}
void cxxbridge1$unique_ptr$std$vector$filetype_t$raw(::std::unique_ptr<::std::vector<::filetype_t>> *ptr, ::std::vector<::filetype_t> *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::std::vector<::filetype_t>>(raw);
}
::std::vector<::filetype_t> const *cxxbridge1$unique_ptr$std$vector$filetype_t$get(::std::unique_ptr<::std::vector<::filetype_t>> const &ptr) noexcept {
  return ptr.get();
}
::std::vector<::filetype_t> *cxxbridge1$unique_ptr$std$vector$filetype_t$release(::std::unique_ptr<::std::vector<::filetype_t>> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$std$vector$filetype_t$drop(::std::unique_ptr<::std::vector<::filetype_t>> *ptr) noexcept {
  ptr->~unique_ptr();
}

static_assert(::rust::detail::is_complete<::func_t>::value, "definition of func_t is required");
static_assert(sizeof(::std::unique_ptr<::func_t>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::func_t>) == alignof(void *), "");
void cxxbridge1$unique_ptr$func_t$null(::std::unique_ptr<::func_t> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::func_t>();
}
::func_t *cxxbridge1$unique_ptr$func_t$uninit(::std::unique_ptr<::func_t> *ptr) noexcept {
  ::func_t *uninit = reinterpret_cast<::func_t *>(new ::rust::MaybeUninit<::func_t>);
  ::new (ptr) ::std::unique_ptr<::func_t>(uninit);
  return uninit;
}
void cxxbridge1$unique_ptr$func_t$raw(::std::unique_ptr<::func_t> *ptr, ::func_t *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::func_t>(raw);
}
::func_t const *cxxbridge1$unique_ptr$func_t$get(::std::unique_ptr<::func_t> const &ptr) noexcept {
  return ptr.get();
}
::func_t *cxxbridge1$unique_ptr$func_t$release(::std::unique_ptr<::func_t> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$func_t$drop(::std::unique_ptr<::func_t> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::func_t>::value>{}(ptr);
}

static_assert(sizeof(::std::shared_ptr<::func_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::shared_ptr<::func_t>) == alignof(void *), "");
void cxxbridge1$shared_ptr$func_t$null(::std::shared_ptr<::func_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::func_t>();
}
::func_t *cxxbridge1$shared_ptr$func_t$uninit(::std::shared_ptr<::func_t> *ptr) noexcept {
  ::func_t *uninit = reinterpret_cast<::func_t *>(new ::rust::MaybeUninit<::func_t>);
  ::new (ptr) ::std::shared_ptr<::func_t>(uninit);
  return uninit;
}
void cxxbridge1$shared_ptr$func_t$clone(::std::shared_ptr<::func_t> const &self, ::std::shared_ptr<::func_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::func_t>(self);
}
::func_t const *cxxbridge1$shared_ptr$func_t$get(::std::shared_ptr<::func_t> const &self) noexcept {
  return self.get();
}
void cxxbridge1$shared_ptr$func_t$drop(::std::shared_ptr<::func_t> *self) noexcept {
  self->~shared_ptr();
}

static_assert(sizeof(::std::weak_ptr<::func_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::weak_ptr<::func_t>) == alignof(void *), "");
void cxxbridge1$weak_ptr$func_t$null(::std::weak_ptr<::func_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::func_t>();
}
void cxxbridge1$weak_ptr$func_t$clone(::std::weak_ptr<::func_t> const &self, ::std::weak_ptr<::func_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::func_t>(self);
}
void cxxbridge1$weak_ptr$func_t$downgrade(::std::shared_ptr<::func_t> const &shared, ::std::weak_ptr<::func_t> *weak) noexcept {
  ::new (weak) ::std::weak_ptr<::func_t>(shared);
}
void cxxbridge1$weak_ptr$func_t$upgrade(::std::weak_ptr<::func_t> const &weak, ::std::shared_ptr<::func_t> *shared) noexcept {
  ::new (shared) ::std::shared_ptr<::func_t>(weak.lock());
}
void cxxbridge1$weak_ptr$func_t$drop(::std::weak_ptr<::func_t> *self) noexcept {
  self->~weak_ptr();
}

::std::vector<::func_t> *cxxbridge1$std$vector$func_t$new() noexcept {
  return new ::std::vector<::func_t>();
}
::std::size_t cxxbridge1$std$vector$func_t$size(::std::vector<::func_t> const &s) noexcept {
  return s.size();
}
::func_t *cxxbridge1$std$vector$func_t$get_unchecked(::std::vector<::func_t> *s, ::std::size_t pos) noexcept {
  return &(*s)[pos];
}
void cxxbridge1$std$vector$func_t$push_back(::std::vector<::func_t> *v, ::func_t *value) noexcept {
  v->push_back(::std::move(*value));
  ::rust::destroy(value);
}
void cxxbridge1$std$vector$func_t$pop_back(::std::vector<::func_t> *v, ::func_t *out) noexcept {
  ::new (out) ::func_t(::std::move(v->back()));
  v->pop_back();
}
static_assert(sizeof(::std::unique_ptr<::std::vector<::func_t>>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::std::vector<::func_t>>) == alignof(void *), "");
void cxxbridge1$unique_ptr$std$vector$func_t$null(::std::unique_ptr<::std::vector<::func_t>> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::std::vector<::func_t>>();
}
void cxxbridge1$unique_ptr$std$vector$func_t$raw(::std::unique_ptr<::std::vector<::func_t>> *ptr, ::std::vector<::func_t> *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::std::vector<::func_t>>(raw);
}
::std::vector<::func_t> const *cxxbridge1$unique_ptr$std$vector$func_t$get(::std::unique_ptr<::std::vector<::func_t>> const &ptr) noexcept {
  return ptr.get();
}
::std::vector<::func_t> *cxxbridge1$unique_ptr$std$vector$func_t$release(::std::unique_ptr<::std::vector<::func_t>> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$std$vector$func_t$drop(::std::unique_ptr<::std::vector<::func_t>> *ptr) noexcept {
  ptr->~unique_ptr();
}

static_assert(::rust::detail::is_complete<::lock_func>::value, "definition of lock_func is required");
static_assert(sizeof(::std::unique_ptr<::lock_func>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::lock_func>) == alignof(void *), "");
void cxxbridge1$unique_ptr$lock_func$null(::std::unique_ptr<::lock_func> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::lock_func>();
}
::lock_func *cxxbridge1$unique_ptr$lock_func$uninit(::std::unique_ptr<::lock_func> *ptr) noexcept {
  ::lock_func *uninit = reinterpret_cast<::lock_func *>(new ::rust::MaybeUninit<::lock_func>);
  ::new (ptr) ::std::unique_ptr<::lock_func>(uninit);
  return uninit;
}
void cxxbridge1$unique_ptr$lock_func$raw(::std::unique_ptr<::lock_func> *ptr, ::lock_func *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::lock_func>(raw);
}
::lock_func const *cxxbridge1$unique_ptr$lock_func$get(::std::unique_ptr<::lock_func> const &ptr) noexcept {
  return ptr.get();
}
::lock_func *cxxbridge1$unique_ptr$lock_func$release(::std::unique_ptr<::lock_func> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$lock_func$drop(::std::unique_ptr<::lock_func> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::lock_func>::value>{}(ptr);
}

static_assert(sizeof(::std::shared_ptr<::lock_func>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::shared_ptr<::lock_func>) == alignof(void *), "");
void cxxbridge1$shared_ptr$lock_func$null(::std::shared_ptr<::lock_func> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::lock_func>();
}
::lock_func *cxxbridge1$shared_ptr$lock_func$uninit(::std::shared_ptr<::lock_func> *ptr) noexcept {
  ::lock_func *uninit = reinterpret_cast<::lock_func *>(new ::rust::MaybeUninit<::lock_func>);
  ::new (ptr) ::std::shared_ptr<::lock_func>(uninit);
  return uninit;
}
void cxxbridge1$shared_ptr$lock_func$clone(::std::shared_ptr<::lock_func> const &self, ::std::shared_ptr<::lock_func> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::lock_func>(self);
}
::lock_func const *cxxbridge1$shared_ptr$lock_func$get(::std::shared_ptr<::lock_func> const &self) noexcept {
  return self.get();
}
void cxxbridge1$shared_ptr$lock_func$drop(::std::shared_ptr<::lock_func> *self) noexcept {
  self->~shared_ptr();
}

static_assert(sizeof(::std::weak_ptr<::lock_func>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::weak_ptr<::lock_func>) == alignof(void *), "");
void cxxbridge1$weak_ptr$lock_func$null(::std::weak_ptr<::lock_func> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::lock_func>();
}
void cxxbridge1$weak_ptr$lock_func$clone(::std::weak_ptr<::lock_func> const &self, ::std::weak_ptr<::lock_func> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::lock_func>(self);
}
void cxxbridge1$weak_ptr$lock_func$downgrade(::std::shared_ptr<::lock_func> const &shared, ::std::weak_ptr<::lock_func> *weak) noexcept {
  ::new (weak) ::std::weak_ptr<::lock_func>(shared);
}
void cxxbridge1$weak_ptr$lock_func$upgrade(::std::weak_ptr<::lock_func> const &weak, ::std::shared_ptr<::lock_func> *shared) noexcept {
  ::new (shared) ::std::shared_ptr<::lock_func>(weak.lock());
}
void cxxbridge1$weak_ptr$lock_func$drop(::std::weak_ptr<::lock_func> *self) noexcept {
  self->~weak_ptr();
}

static_assert(::rust::detail::is_complete<::fc_block_type_t>::value, "definition of fc_block_type_t is required");
static_assert(sizeof(::std::unique_ptr<::fc_block_type_t>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::fc_block_type_t>) == alignof(void *), "");
void cxxbridge1$unique_ptr$fc_block_type_t$null(::std::unique_ptr<::fc_block_type_t> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::fc_block_type_t>();
}
::fc_block_type_t *cxxbridge1$unique_ptr$fc_block_type_t$uninit(::std::unique_ptr<::fc_block_type_t> *ptr) noexcept {
  ::fc_block_type_t *uninit = reinterpret_cast<::fc_block_type_t *>(new ::rust::MaybeUninit<::fc_block_type_t>);
  ::new (ptr) ::std::unique_ptr<::fc_block_type_t>(uninit);
  return uninit;
}
void cxxbridge1$unique_ptr$fc_block_type_t$raw(::std::unique_ptr<::fc_block_type_t> *ptr, ::fc_block_type_t *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::fc_block_type_t>(raw);
}
::fc_block_type_t const *cxxbridge1$unique_ptr$fc_block_type_t$get(::std::unique_ptr<::fc_block_type_t> const &ptr) noexcept {
  return ptr.get();
}
::fc_block_type_t *cxxbridge1$unique_ptr$fc_block_type_t$release(::std::unique_ptr<::fc_block_type_t> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$fc_block_type_t$drop(::std::unique_ptr<::fc_block_type_t> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::fc_block_type_t>::value>{}(ptr);
}

static_assert(sizeof(::std::shared_ptr<::fc_block_type_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::shared_ptr<::fc_block_type_t>) == alignof(void *), "");
void cxxbridge1$shared_ptr$fc_block_type_t$null(::std::shared_ptr<::fc_block_type_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::fc_block_type_t>();
}
::fc_block_type_t *cxxbridge1$shared_ptr$fc_block_type_t$uninit(::std::shared_ptr<::fc_block_type_t> *ptr) noexcept {
  ::fc_block_type_t *uninit = reinterpret_cast<::fc_block_type_t *>(new ::rust::MaybeUninit<::fc_block_type_t>);
  ::new (ptr) ::std::shared_ptr<::fc_block_type_t>(uninit);
  return uninit;
}
void cxxbridge1$shared_ptr$fc_block_type_t$clone(::std::shared_ptr<::fc_block_type_t> const &self, ::std::shared_ptr<::fc_block_type_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::fc_block_type_t>(self);
}
::fc_block_type_t const *cxxbridge1$shared_ptr$fc_block_type_t$get(::std::shared_ptr<::fc_block_type_t> const &self) noexcept {
  return self.get();
}
void cxxbridge1$shared_ptr$fc_block_type_t$drop(::std::shared_ptr<::fc_block_type_t> *self) noexcept {
  self->~shared_ptr();
}

static_assert(sizeof(::std::weak_ptr<::fc_block_type_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::weak_ptr<::fc_block_type_t>) == alignof(void *), "");
void cxxbridge1$weak_ptr$fc_block_type_t$null(::std::weak_ptr<::fc_block_type_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::fc_block_type_t>();
}
void cxxbridge1$weak_ptr$fc_block_type_t$clone(::std::weak_ptr<::fc_block_type_t> const &self, ::std::weak_ptr<::fc_block_type_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::fc_block_type_t>(self);
}
void cxxbridge1$weak_ptr$fc_block_type_t$downgrade(::std::shared_ptr<::fc_block_type_t> const &shared, ::std::weak_ptr<::fc_block_type_t> *weak) noexcept {
  ::new (weak) ::std::weak_ptr<::fc_block_type_t>(shared);
}
void cxxbridge1$weak_ptr$fc_block_type_t$upgrade(::std::weak_ptr<::fc_block_type_t> const &weak, ::std::shared_ptr<::fc_block_type_t> *shared) noexcept {
  ::new (shared) ::std::shared_ptr<::fc_block_type_t>(weak.lock());
}
void cxxbridge1$weak_ptr$fc_block_type_t$drop(::std::weak_ptr<::fc_block_type_t> *self) noexcept {
  self->~weak_ptr();
}

::std::vector<::fc_block_type_t> *cxxbridge1$std$vector$fc_block_type_t$new() noexcept {
  return new ::std::vector<::fc_block_type_t>();
}
::std::size_t cxxbridge1$std$vector$fc_block_type_t$size(::std::vector<::fc_block_type_t> const &s) noexcept {
  return s.size();
}
::fc_block_type_t *cxxbridge1$std$vector$fc_block_type_t$get_unchecked(::std::vector<::fc_block_type_t> *s, ::std::size_t pos) noexcept {
  return &(*s)[pos];
}
void cxxbridge1$std$vector$fc_block_type_t$push_back(::std::vector<::fc_block_type_t> *v, ::fc_block_type_t *value) noexcept {
  v->push_back(::std::move(*value));
  ::rust::destroy(value);
}
void cxxbridge1$std$vector$fc_block_type_t$pop_back(::std::vector<::fc_block_type_t> *v, ::fc_block_type_t *out) noexcept {
  ::new (out) ::fc_block_type_t(::std::move(v->back()));
  v->pop_back();
}
static_assert(sizeof(::std::unique_ptr<::std::vector<::fc_block_type_t>>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::std::vector<::fc_block_type_t>>) == alignof(void *), "");
void cxxbridge1$unique_ptr$std$vector$fc_block_type_t$null(::std::unique_ptr<::std::vector<::fc_block_type_t>> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::std::vector<::fc_block_type_t>>();
}
void cxxbridge1$unique_ptr$std$vector$fc_block_type_t$raw(::std::unique_ptr<::std::vector<::fc_block_type_t>> *ptr, ::std::vector<::fc_block_type_t> *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::std::vector<::fc_block_type_t>>(raw);
}
::std::vector<::fc_block_type_t> const *cxxbridge1$unique_ptr$std$vector$fc_block_type_t$get(::std::unique_ptr<::std::vector<::fc_block_type_t>> const &ptr) noexcept {
  return ptr.get();
}
::std::vector<::fc_block_type_t> *cxxbridge1$unique_ptr$std$vector$fc_block_type_t$release(::std::unique_ptr<::std::vector<::fc_block_type_t>> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$std$vector$fc_block_type_t$drop(::std::unique_ptr<::std::vector<::fc_block_type_t>> *ptr) noexcept {
  ptr->~unique_ptr();
}

static_assert(::rust::detail::is_complete<::gdl_graph_t>::value, "definition of gdl_graph_t is required");
static_assert(sizeof(::std::unique_ptr<::gdl_graph_t>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::gdl_graph_t>) == alignof(void *), "");
void cxxbridge1$unique_ptr$gdl_graph_t$null(::std::unique_ptr<::gdl_graph_t> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::gdl_graph_t>();
}
void cxxbridge1$unique_ptr$gdl_graph_t$raw(::std::unique_ptr<::gdl_graph_t> *ptr, ::gdl_graph_t *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::gdl_graph_t>(raw);
}
::gdl_graph_t const *cxxbridge1$unique_ptr$gdl_graph_t$get(::std::unique_ptr<::gdl_graph_t> const &ptr) noexcept {
  return ptr.get();
}
::gdl_graph_t *cxxbridge1$unique_ptr$gdl_graph_t$release(::std::unique_ptr<::gdl_graph_t> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$gdl_graph_t$drop(::std::unique_ptr<::gdl_graph_t> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::gdl_graph_t>::value>{}(ptr);
}

static_assert(sizeof(::std::shared_ptr<::gdl_graph_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::shared_ptr<::gdl_graph_t>) == alignof(void *), "");
void cxxbridge1$shared_ptr$gdl_graph_t$null(::std::shared_ptr<::gdl_graph_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::gdl_graph_t>();
}
void cxxbridge1$shared_ptr$gdl_graph_t$clone(::std::shared_ptr<::gdl_graph_t> const &self, ::std::shared_ptr<::gdl_graph_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::gdl_graph_t>(self);
}
::gdl_graph_t const *cxxbridge1$shared_ptr$gdl_graph_t$get(::std::shared_ptr<::gdl_graph_t> const &self) noexcept {
  return self.get();
}
void cxxbridge1$shared_ptr$gdl_graph_t$drop(::std::shared_ptr<::gdl_graph_t> *self) noexcept {
  self->~shared_ptr();
}

static_assert(sizeof(::std::weak_ptr<::gdl_graph_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::weak_ptr<::gdl_graph_t>) == alignof(void *), "");
void cxxbridge1$weak_ptr$gdl_graph_t$null(::std::weak_ptr<::gdl_graph_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::gdl_graph_t>();
}
void cxxbridge1$weak_ptr$gdl_graph_t$clone(::std::weak_ptr<::gdl_graph_t> const &self, ::std::weak_ptr<::gdl_graph_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::gdl_graph_t>(self);
}
void cxxbridge1$weak_ptr$gdl_graph_t$downgrade(::std::shared_ptr<::gdl_graph_t> const &shared, ::std::weak_ptr<::gdl_graph_t> *weak) noexcept {
  ::new (weak) ::std::weak_ptr<::gdl_graph_t>(shared);
}
void cxxbridge1$weak_ptr$gdl_graph_t$upgrade(::std::weak_ptr<::gdl_graph_t> const &weak, ::std::shared_ptr<::gdl_graph_t> *shared) noexcept {
  ::new (shared) ::std::shared_ptr<::gdl_graph_t>(weak.lock());
}
void cxxbridge1$weak_ptr$gdl_graph_t$drop(::std::weak_ptr<::gdl_graph_t> *self) noexcept {
  self->~weak_ptr();
}

static_assert(::rust::detail::is_complete<::qbasic_block_t>::value, "definition of qbasic_block_t is required");
static_assert(sizeof(::std::unique_ptr<::qbasic_block_t>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::qbasic_block_t>) == alignof(void *), "");
void cxxbridge1$unique_ptr$qbasic_block_t$null(::std::unique_ptr<::qbasic_block_t> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::qbasic_block_t>();
}
::qbasic_block_t *cxxbridge1$unique_ptr$qbasic_block_t$uninit(::std::unique_ptr<::qbasic_block_t> *ptr) noexcept {
  ::qbasic_block_t *uninit = reinterpret_cast<::qbasic_block_t *>(new ::rust::MaybeUninit<::qbasic_block_t>);
  ::new (ptr) ::std::unique_ptr<::qbasic_block_t>(uninit);
  return uninit;
}
void cxxbridge1$unique_ptr$qbasic_block_t$raw(::std::unique_ptr<::qbasic_block_t> *ptr, ::qbasic_block_t *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::qbasic_block_t>(raw);
}
::qbasic_block_t const *cxxbridge1$unique_ptr$qbasic_block_t$get(::std::unique_ptr<::qbasic_block_t> const &ptr) noexcept {
  return ptr.get();
}
::qbasic_block_t *cxxbridge1$unique_ptr$qbasic_block_t$release(::std::unique_ptr<::qbasic_block_t> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$qbasic_block_t$drop(::std::unique_ptr<::qbasic_block_t> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::qbasic_block_t>::value>{}(ptr);
}

static_assert(sizeof(::std::shared_ptr<::qbasic_block_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::shared_ptr<::qbasic_block_t>) == alignof(void *), "");
void cxxbridge1$shared_ptr$qbasic_block_t$null(::std::shared_ptr<::qbasic_block_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::qbasic_block_t>();
}
::qbasic_block_t *cxxbridge1$shared_ptr$qbasic_block_t$uninit(::std::shared_ptr<::qbasic_block_t> *ptr) noexcept {
  ::qbasic_block_t *uninit = reinterpret_cast<::qbasic_block_t *>(new ::rust::MaybeUninit<::qbasic_block_t>);
  ::new (ptr) ::std::shared_ptr<::qbasic_block_t>(uninit);
  return uninit;
}
void cxxbridge1$shared_ptr$qbasic_block_t$clone(::std::shared_ptr<::qbasic_block_t> const &self, ::std::shared_ptr<::qbasic_block_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::qbasic_block_t>(self);
}
::qbasic_block_t const *cxxbridge1$shared_ptr$qbasic_block_t$get(::std::shared_ptr<::qbasic_block_t> const &self) noexcept {
  return self.get();
}
void cxxbridge1$shared_ptr$qbasic_block_t$drop(::std::shared_ptr<::qbasic_block_t> *self) noexcept {
  self->~shared_ptr();
}

static_assert(sizeof(::std::weak_ptr<::qbasic_block_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::weak_ptr<::qbasic_block_t>) == alignof(void *), "");
void cxxbridge1$weak_ptr$qbasic_block_t$null(::std::weak_ptr<::qbasic_block_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::qbasic_block_t>();
}
void cxxbridge1$weak_ptr$qbasic_block_t$clone(::std::weak_ptr<::qbasic_block_t> const &self, ::std::weak_ptr<::qbasic_block_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::qbasic_block_t>(self);
}
void cxxbridge1$weak_ptr$qbasic_block_t$downgrade(::std::shared_ptr<::qbasic_block_t> const &shared, ::std::weak_ptr<::qbasic_block_t> *weak) noexcept {
  ::new (weak) ::std::weak_ptr<::qbasic_block_t>(shared);
}
void cxxbridge1$weak_ptr$qbasic_block_t$upgrade(::std::weak_ptr<::qbasic_block_t> const &weak, ::std::shared_ptr<::qbasic_block_t> *shared) noexcept {
  ::new (shared) ::std::shared_ptr<::qbasic_block_t>(weak.lock());
}
void cxxbridge1$weak_ptr$qbasic_block_t$drop(::std::weak_ptr<::qbasic_block_t> *self) noexcept {
  self->~weak_ptr();
}

static_assert(::rust::detail::is_complete<::qflow_chart_t>::value, "definition of qflow_chart_t is required");
static_assert(sizeof(::std::unique_ptr<::qflow_chart_t>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::qflow_chart_t>) == alignof(void *), "");
void cxxbridge1$unique_ptr$qflow_chart_t$null(::std::unique_ptr<::qflow_chart_t> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::qflow_chart_t>();
}
::qflow_chart_t *cxxbridge1$unique_ptr$qflow_chart_t$uninit(::std::unique_ptr<::qflow_chart_t> *ptr) noexcept {
  ::qflow_chart_t *uninit = reinterpret_cast<::qflow_chart_t *>(new ::rust::MaybeUninit<::qflow_chart_t>);
  ::new (ptr) ::std::unique_ptr<::qflow_chart_t>(uninit);
  return uninit;
}
void cxxbridge1$unique_ptr$qflow_chart_t$raw(::std::unique_ptr<::qflow_chart_t> *ptr, ::qflow_chart_t *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::qflow_chart_t>(raw);
}
::qflow_chart_t const *cxxbridge1$unique_ptr$qflow_chart_t$get(::std::unique_ptr<::qflow_chart_t> const &ptr) noexcept {
  return ptr.get();
}
::qflow_chart_t *cxxbridge1$unique_ptr$qflow_chart_t$release(::std::unique_ptr<::qflow_chart_t> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$qflow_chart_t$drop(::std::unique_ptr<::qflow_chart_t> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::qflow_chart_t>::value>{}(ptr);
}

static_assert(sizeof(::std::shared_ptr<::qflow_chart_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::shared_ptr<::qflow_chart_t>) == alignof(void *), "");
void cxxbridge1$shared_ptr$qflow_chart_t$null(::std::shared_ptr<::qflow_chart_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::qflow_chart_t>();
}
::qflow_chart_t *cxxbridge1$shared_ptr$qflow_chart_t$uninit(::std::shared_ptr<::qflow_chart_t> *ptr) noexcept {
  ::qflow_chart_t *uninit = reinterpret_cast<::qflow_chart_t *>(new ::rust::MaybeUninit<::qflow_chart_t>);
  ::new (ptr) ::std::shared_ptr<::qflow_chart_t>(uninit);
  return uninit;
}
void cxxbridge1$shared_ptr$qflow_chart_t$clone(::std::shared_ptr<::qflow_chart_t> const &self, ::std::shared_ptr<::qflow_chart_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::qflow_chart_t>(self);
}
::qflow_chart_t const *cxxbridge1$shared_ptr$qflow_chart_t$get(::std::shared_ptr<::qflow_chart_t> const &self) noexcept {
  return self.get();
}
void cxxbridge1$shared_ptr$qflow_chart_t$drop(::std::shared_ptr<::qflow_chart_t> *self) noexcept {
  self->~shared_ptr();
}

static_assert(sizeof(::std::weak_ptr<::qflow_chart_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::weak_ptr<::qflow_chart_t>) == alignof(void *), "");
void cxxbridge1$weak_ptr$qflow_chart_t$null(::std::weak_ptr<::qflow_chart_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::qflow_chart_t>();
}
void cxxbridge1$weak_ptr$qflow_chart_t$clone(::std::weak_ptr<::qflow_chart_t> const &self, ::std::weak_ptr<::qflow_chart_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::qflow_chart_t>(self);
}
void cxxbridge1$weak_ptr$qflow_chart_t$downgrade(::std::shared_ptr<::qflow_chart_t> const &shared, ::std::weak_ptr<::qflow_chart_t> *weak) noexcept {
  ::new (weak) ::std::weak_ptr<::qflow_chart_t>(shared);
}
void cxxbridge1$weak_ptr$qflow_chart_t$upgrade(::std::weak_ptr<::qflow_chart_t> const &weak, ::std::shared_ptr<::qflow_chart_t> *shared) noexcept {
  ::new (shared) ::std::shared_ptr<::qflow_chart_t>(weak.lock());
}
void cxxbridge1$weak_ptr$qflow_chart_t$drop(::std::weak_ptr<::qflow_chart_t> *self) noexcept {
  self->~weak_ptr();
}

static_assert(::rust::detail::is_complete<::segment_t>::value, "definition of segment_t is required");
static_assert(sizeof(::std::unique_ptr<::segment_t>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::segment_t>) == alignof(void *), "");
void cxxbridge1$unique_ptr$segment_t$null(::std::unique_ptr<::segment_t> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::segment_t>();
}
::segment_t *cxxbridge1$unique_ptr$segment_t$uninit(::std::unique_ptr<::segment_t> *ptr) noexcept {
  ::segment_t *uninit = reinterpret_cast<::segment_t *>(new ::rust::MaybeUninit<::segment_t>);
  ::new (ptr) ::std::unique_ptr<::segment_t>(uninit);
  return uninit;
}
void cxxbridge1$unique_ptr$segment_t$raw(::std::unique_ptr<::segment_t> *ptr, ::segment_t *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::segment_t>(raw);
}
::segment_t const *cxxbridge1$unique_ptr$segment_t$get(::std::unique_ptr<::segment_t> const &ptr) noexcept {
  return ptr.get();
}
::segment_t *cxxbridge1$unique_ptr$segment_t$release(::std::unique_ptr<::segment_t> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$segment_t$drop(::std::unique_ptr<::segment_t> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::segment_t>::value>{}(ptr);
}

static_assert(sizeof(::std::shared_ptr<::segment_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::shared_ptr<::segment_t>) == alignof(void *), "");
void cxxbridge1$shared_ptr$segment_t$null(::std::shared_ptr<::segment_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::segment_t>();
}
::segment_t *cxxbridge1$shared_ptr$segment_t$uninit(::std::shared_ptr<::segment_t> *ptr) noexcept {
  ::segment_t *uninit = reinterpret_cast<::segment_t *>(new ::rust::MaybeUninit<::segment_t>);
  ::new (ptr) ::std::shared_ptr<::segment_t>(uninit);
  return uninit;
}
void cxxbridge1$shared_ptr$segment_t$clone(::std::shared_ptr<::segment_t> const &self, ::std::shared_ptr<::segment_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::segment_t>(self);
}
::segment_t const *cxxbridge1$shared_ptr$segment_t$get(::std::shared_ptr<::segment_t> const &self) noexcept {
  return self.get();
}
void cxxbridge1$shared_ptr$segment_t$drop(::std::shared_ptr<::segment_t> *self) noexcept {
  self->~shared_ptr();
}

static_assert(sizeof(::std::weak_ptr<::segment_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::weak_ptr<::segment_t>) == alignof(void *), "");
void cxxbridge1$weak_ptr$segment_t$null(::std::weak_ptr<::segment_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::segment_t>();
}
void cxxbridge1$weak_ptr$segment_t$clone(::std::weak_ptr<::segment_t> const &self, ::std::weak_ptr<::segment_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::segment_t>(self);
}
void cxxbridge1$weak_ptr$segment_t$downgrade(::std::shared_ptr<::segment_t> const &shared, ::std::weak_ptr<::segment_t> *weak) noexcept {
  ::new (weak) ::std::weak_ptr<::segment_t>(shared);
}
void cxxbridge1$weak_ptr$segment_t$upgrade(::std::weak_ptr<::segment_t> const &weak, ::std::shared_ptr<::segment_t> *shared) noexcept {
  ::new (shared) ::std::shared_ptr<::segment_t>(weak.lock());
}
void cxxbridge1$weak_ptr$segment_t$drop(::std::weak_ptr<::segment_t> *self) noexcept {
  self->~weak_ptr();
}

::std::vector<::segment_t> *cxxbridge1$std$vector$segment_t$new() noexcept {
  return new ::std::vector<::segment_t>();
}
::std::size_t cxxbridge1$std$vector$segment_t$size(::std::vector<::segment_t> const &s) noexcept {
  return s.size();
}
::segment_t *cxxbridge1$std$vector$segment_t$get_unchecked(::std::vector<::segment_t> *s, ::std::size_t pos) noexcept {
  return &(*s)[pos];
}
void cxxbridge1$std$vector$segment_t$push_back(::std::vector<::segment_t> *v, ::segment_t *value) noexcept {
  v->push_back(::std::move(*value));
  ::rust::destroy(value);
}
void cxxbridge1$std$vector$segment_t$pop_back(::std::vector<::segment_t> *v, ::segment_t *out) noexcept {
  ::new (out) ::segment_t(::std::move(v->back()));
  v->pop_back();
}
static_assert(sizeof(::std::unique_ptr<::std::vector<::segment_t>>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::std::vector<::segment_t>>) == alignof(void *), "");
void cxxbridge1$unique_ptr$std$vector$segment_t$null(::std::unique_ptr<::std::vector<::segment_t>> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::std::vector<::segment_t>>();
}
void cxxbridge1$unique_ptr$std$vector$segment_t$raw(::std::unique_ptr<::std::vector<::segment_t>> *ptr, ::std::vector<::segment_t> *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::std::vector<::segment_t>>(raw);
}
::std::vector<::segment_t> const *cxxbridge1$unique_ptr$std$vector$segment_t$get(::std::unique_ptr<::std::vector<::segment_t>> const &ptr) noexcept {
  return ptr.get();
}
::std::vector<::segment_t> *cxxbridge1$unique_ptr$std$vector$segment_t$release(::std::unique_ptr<::std::vector<::segment_t>> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$std$vector$segment_t$drop(::std::unique_ptr<::std::vector<::segment_t>> *ptr) noexcept {
  ptr->~unique_ptr();
}

static_assert(::rust::detail::is_complete<::lock_segment>::value, "definition of lock_segment is required");
static_assert(sizeof(::std::unique_ptr<::lock_segment>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::lock_segment>) == alignof(void *), "");
void cxxbridge1$unique_ptr$lock_segment$null(::std::unique_ptr<::lock_segment> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::lock_segment>();
}
::lock_segment *cxxbridge1$unique_ptr$lock_segment$uninit(::std::unique_ptr<::lock_segment> *ptr) noexcept {
  ::lock_segment *uninit = reinterpret_cast<::lock_segment *>(new ::rust::MaybeUninit<::lock_segment>);
  ::new (ptr) ::std::unique_ptr<::lock_segment>(uninit);
  return uninit;
}
void cxxbridge1$unique_ptr$lock_segment$raw(::std::unique_ptr<::lock_segment> *ptr, ::lock_segment *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::lock_segment>(raw);
}
::lock_segment const *cxxbridge1$unique_ptr$lock_segment$get(::std::unique_ptr<::lock_segment> const &ptr) noexcept {
  return ptr.get();
}
::lock_segment *cxxbridge1$unique_ptr$lock_segment$release(::std::unique_ptr<::lock_segment> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$lock_segment$drop(::std::unique_ptr<::lock_segment> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::lock_segment>::value>{}(ptr);
}

static_assert(sizeof(::std::shared_ptr<::lock_segment>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::shared_ptr<::lock_segment>) == alignof(void *), "");
void cxxbridge1$shared_ptr$lock_segment$null(::std::shared_ptr<::lock_segment> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::lock_segment>();
}
::lock_segment *cxxbridge1$shared_ptr$lock_segment$uninit(::std::shared_ptr<::lock_segment> *ptr) noexcept {
  ::lock_segment *uninit = reinterpret_cast<::lock_segment *>(new ::rust::MaybeUninit<::lock_segment>);
  ::new (ptr) ::std::shared_ptr<::lock_segment>(uninit);
  return uninit;
}
void cxxbridge1$shared_ptr$lock_segment$clone(::std::shared_ptr<::lock_segment> const &self, ::std::shared_ptr<::lock_segment> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::lock_segment>(self);
}
::lock_segment const *cxxbridge1$shared_ptr$lock_segment$get(::std::shared_ptr<::lock_segment> const &self) noexcept {
  return self.get();
}
void cxxbridge1$shared_ptr$lock_segment$drop(::std::shared_ptr<::lock_segment> *self) noexcept {
  self->~shared_ptr();
}

static_assert(sizeof(::std::weak_ptr<::lock_segment>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::weak_ptr<::lock_segment>) == alignof(void *), "");
void cxxbridge1$weak_ptr$lock_segment$null(::std::weak_ptr<::lock_segment> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::lock_segment>();
}
void cxxbridge1$weak_ptr$lock_segment$clone(::std::weak_ptr<::lock_segment> const &self, ::std::weak_ptr<::lock_segment> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::lock_segment>(self);
}
void cxxbridge1$weak_ptr$lock_segment$downgrade(::std::shared_ptr<::lock_segment> const &shared, ::std::weak_ptr<::lock_segment> *weak) noexcept {
  ::new (weak) ::std::weak_ptr<::lock_segment>(shared);
}
void cxxbridge1$weak_ptr$lock_segment$upgrade(::std::weak_ptr<::lock_segment> const &weak, ::std::shared_ptr<::lock_segment> *shared) noexcept {
  ::new (shared) ::std::shared_ptr<::lock_segment>(weak.lock());
}
void cxxbridge1$weak_ptr$lock_segment$drop(::std::weak_ptr<::lock_segment> *self) noexcept {
  self->~weak_ptr();
}

static_assert(::rust::detail::is_complete<::cref_t>::value, "definition of cref_t is required");
static_assert(sizeof(::std::unique_ptr<::cref_t>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::cref_t>) == alignof(void *), "");
void cxxbridge1$unique_ptr$cref_t$null(::std::unique_ptr<::cref_t> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::cref_t>();
}
::cref_t *cxxbridge1$unique_ptr$cref_t$uninit(::std::unique_ptr<::cref_t> *ptr) noexcept {
  ::cref_t *uninit = reinterpret_cast<::cref_t *>(new ::rust::MaybeUninit<::cref_t>);
  ::new (ptr) ::std::unique_ptr<::cref_t>(uninit);
  return uninit;
}
void cxxbridge1$unique_ptr$cref_t$raw(::std::unique_ptr<::cref_t> *ptr, ::cref_t *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::cref_t>(raw);
}
::cref_t const *cxxbridge1$unique_ptr$cref_t$get(::std::unique_ptr<::cref_t> const &ptr) noexcept {
  return ptr.get();
}
::cref_t *cxxbridge1$unique_ptr$cref_t$release(::std::unique_ptr<::cref_t> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$cref_t$drop(::std::unique_ptr<::cref_t> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::cref_t>::value>{}(ptr);
}

static_assert(sizeof(::std::shared_ptr<::cref_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::shared_ptr<::cref_t>) == alignof(void *), "");
void cxxbridge1$shared_ptr$cref_t$null(::std::shared_ptr<::cref_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::cref_t>();
}
::cref_t *cxxbridge1$shared_ptr$cref_t$uninit(::std::shared_ptr<::cref_t> *ptr) noexcept {
  ::cref_t *uninit = reinterpret_cast<::cref_t *>(new ::rust::MaybeUninit<::cref_t>);
  ::new (ptr) ::std::shared_ptr<::cref_t>(uninit);
  return uninit;
}
void cxxbridge1$shared_ptr$cref_t$clone(::std::shared_ptr<::cref_t> const &self, ::std::shared_ptr<::cref_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::cref_t>(self);
}
::cref_t const *cxxbridge1$shared_ptr$cref_t$get(::std::shared_ptr<::cref_t> const &self) noexcept {
  return self.get();
}
void cxxbridge1$shared_ptr$cref_t$drop(::std::shared_ptr<::cref_t> *self) noexcept {
  self->~shared_ptr();
}

static_assert(sizeof(::std::weak_ptr<::cref_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::weak_ptr<::cref_t>) == alignof(void *), "");
void cxxbridge1$weak_ptr$cref_t$null(::std::weak_ptr<::cref_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::cref_t>();
}
void cxxbridge1$weak_ptr$cref_t$clone(::std::weak_ptr<::cref_t> const &self, ::std::weak_ptr<::cref_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::cref_t>(self);
}
void cxxbridge1$weak_ptr$cref_t$downgrade(::std::shared_ptr<::cref_t> const &shared, ::std::weak_ptr<::cref_t> *weak) noexcept {
  ::new (weak) ::std::weak_ptr<::cref_t>(shared);
}
void cxxbridge1$weak_ptr$cref_t$upgrade(::std::weak_ptr<::cref_t> const &weak, ::std::shared_ptr<::cref_t> *shared) noexcept {
  ::new (shared) ::std::shared_ptr<::cref_t>(weak.lock());
}
void cxxbridge1$weak_ptr$cref_t$drop(::std::weak_ptr<::cref_t> *self) noexcept {
  self->~weak_ptr();
}

::std::vector<::cref_t> *cxxbridge1$std$vector$cref_t$new() noexcept {
  return new ::std::vector<::cref_t>();
}
::std::size_t cxxbridge1$std$vector$cref_t$size(::std::vector<::cref_t> const &s) noexcept {
  return s.size();
}
::cref_t *cxxbridge1$std$vector$cref_t$get_unchecked(::std::vector<::cref_t> *s, ::std::size_t pos) noexcept {
  return &(*s)[pos];
}
void cxxbridge1$std$vector$cref_t$push_back(::std::vector<::cref_t> *v, ::cref_t *value) noexcept {
  v->push_back(::std::move(*value));
  ::rust::destroy(value);
}
void cxxbridge1$std$vector$cref_t$pop_back(::std::vector<::cref_t> *v, ::cref_t *out) noexcept {
  ::new (out) ::cref_t(::std::move(v->back()));
  v->pop_back();
}
static_assert(sizeof(::std::unique_ptr<::std::vector<::cref_t>>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::std::vector<::cref_t>>) == alignof(void *), "");
void cxxbridge1$unique_ptr$std$vector$cref_t$null(::std::unique_ptr<::std::vector<::cref_t>> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::std::vector<::cref_t>>();
}
void cxxbridge1$unique_ptr$std$vector$cref_t$raw(::std::unique_ptr<::std::vector<::cref_t>> *ptr, ::std::vector<::cref_t> *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::std::vector<::cref_t>>(raw);
}
::std::vector<::cref_t> const *cxxbridge1$unique_ptr$std$vector$cref_t$get(::std::unique_ptr<::std::vector<::cref_t>> const &ptr) noexcept {
  return ptr.get();
}
::std::vector<::cref_t> *cxxbridge1$unique_ptr$std$vector$cref_t$release(::std::unique_ptr<::std::vector<::cref_t>> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$std$vector$cref_t$drop(::std::unique_ptr<::std::vector<::cref_t>> *ptr) noexcept {
  ptr->~unique_ptr();
}

static_assert(::rust::detail::is_complete<::dref_t>::value, "definition of dref_t is required");
static_assert(sizeof(::std::unique_ptr<::dref_t>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::dref_t>) == alignof(void *), "");
void cxxbridge1$unique_ptr$dref_t$null(::std::unique_ptr<::dref_t> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::dref_t>();
}
::dref_t *cxxbridge1$unique_ptr$dref_t$uninit(::std::unique_ptr<::dref_t> *ptr) noexcept {
  ::dref_t *uninit = reinterpret_cast<::dref_t *>(new ::rust::MaybeUninit<::dref_t>);
  ::new (ptr) ::std::unique_ptr<::dref_t>(uninit);
  return uninit;
}
void cxxbridge1$unique_ptr$dref_t$raw(::std::unique_ptr<::dref_t> *ptr, ::dref_t *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::dref_t>(raw);
}
::dref_t const *cxxbridge1$unique_ptr$dref_t$get(::std::unique_ptr<::dref_t> const &ptr) noexcept {
  return ptr.get();
}
::dref_t *cxxbridge1$unique_ptr$dref_t$release(::std::unique_ptr<::dref_t> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$dref_t$drop(::std::unique_ptr<::dref_t> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::dref_t>::value>{}(ptr);
}

static_assert(sizeof(::std::shared_ptr<::dref_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::shared_ptr<::dref_t>) == alignof(void *), "");
void cxxbridge1$shared_ptr$dref_t$null(::std::shared_ptr<::dref_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::dref_t>();
}
::dref_t *cxxbridge1$shared_ptr$dref_t$uninit(::std::shared_ptr<::dref_t> *ptr) noexcept {
  ::dref_t *uninit = reinterpret_cast<::dref_t *>(new ::rust::MaybeUninit<::dref_t>);
  ::new (ptr) ::std::shared_ptr<::dref_t>(uninit);
  return uninit;
}
void cxxbridge1$shared_ptr$dref_t$clone(::std::shared_ptr<::dref_t> const &self, ::std::shared_ptr<::dref_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::dref_t>(self);
}
::dref_t const *cxxbridge1$shared_ptr$dref_t$get(::std::shared_ptr<::dref_t> const &self) noexcept {
  return self.get();
}
void cxxbridge1$shared_ptr$dref_t$drop(::std::shared_ptr<::dref_t> *self) noexcept {
  self->~shared_ptr();
}

static_assert(sizeof(::std::weak_ptr<::dref_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::weak_ptr<::dref_t>) == alignof(void *), "");
void cxxbridge1$weak_ptr$dref_t$null(::std::weak_ptr<::dref_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::dref_t>();
}
void cxxbridge1$weak_ptr$dref_t$clone(::std::weak_ptr<::dref_t> const &self, ::std::weak_ptr<::dref_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::dref_t>(self);
}
void cxxbridge1$weak_ptr$dref_t$downgrade(::std::shared_ptr<::dref_t> const &shared, ::std::weak_ptr<::dref_t> *weak) noexcept {
  ::new (weak) ::std::weak_ptr<::dref_t>(shared);
}
void cxxbridge1$weak_ptr$dref_t$upgrade(::std::weak_ptr<::dref_t> const &weak, ::std::shared_ptr<::dref_t> *shared) noexcept {
  ::new (shared) ::std::shared_ptr<::dref_t>(weak.lock());
}
void cxxbridge1$weak_ptr$dref_t$drop(::std::weak_ptr<::dref_t> *self) noexcept {
  self->~weak_ptr();
}

::std::vector<::dref_t> *cxxbridge1$std$vector$dref_t$new() noexcept {
  return new ::std::vector<::dref_t>();
}
::std::size_t cxxbridge1$std$vector$dref_t$size(::std::vector<::dref_t> const &s) noexcept {
  return s.size();
}
::dref_t *cxxbridge1$std$vector$dref_t$get_unchecked(::std::vector<::dref_t> *s, ::std::size_t pos) noexcept {
  return &(*s)[pos];
}
void cxxbridge1$std$vector$dref_t$push_back(::std::vector<::dref_t> *v, ::dref_t *value) noexcept {
  v->push_back(::std::move(*value));
  ::rust::destroy(value);
}
void cxxbridge1$std$vector$dref_t$pop_back(::std::vector<::dref_t> *v, ::dref_t *out) noexcept {
  ::new (out) ::dref_t(::std::move(v->back()));
  v->pop_back();
}
static_assert(sizeof(::std::unique_ptr<::std::vector<::dref_t>>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::std::vector<::dref_t>>) == alignof(void *), "");
void cxxbridge1$unique_ptr$std$vector$dref_t$null(::std::unique_ptr<::std::vector<::dref_t>> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::std::vector<::dref_t>>();
}
void cxxbridge1$unique_ptr$std$vector$dref_t$raw(::std::unique_ptr<::std::vector<::dref_t>> *ptr, ::std::vector<::dref_t> *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::std::vector<::dref_t>>(raw);
}
::std::vector<::dref_t> const *cxxbridge1$unique_ptr$std$vector$dref_t$get(::std::unique_ptr<::std::vector<::dref_t>> const &ptr) noexcept {
  return ptr.get();
}
::std::vector<::dref_t> *cxxbridge1$unique_ptr$std$vector$dref_t$release(::std::unique_ptr<::std::vector<::dref_t>> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$std$vector$dref_t$drop(::std::unique_ptr<::std::vector<::dref_t>> *ptr) noexcept {
  ptr->~unique_ptr();
}

static_assert(::rust::detail::is_complete<::xrefblk_t>::value, "definition of xrefblk_t is required");
static_assert(sizeof(::std::unique_ptr<::xrefblk_t>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::xrefblk_t>) == alignof(void *), "");
void cxxbridge1$unique_ptr$xrefblk_t$null(::std::unique_ptr<::xrefblk_t> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::xrefblk_t>();
}
::xrefblk_t *cxxbridge1$unique_ptr$xrefblk_t$uninit(::std::unique_ptr<::xrefblk_t> *ptr) noexcept {
  ::xrefblk_t *uninit = reinterpret_cast<::xrefblk_t *>(new ::rust::MaybeUninit<::xrefblk_t>);
  ::new (ptr) ::std::unique_ptr<::xrefblk_t>(uninit);
  return uninit;
}
void cxxbridge1$unique_ptr$xrefblk_t$raw(::std::unique_ptr<::xrefblk_t> *ptr, ::xrefblk_t *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::xrefblk_t>(raw);
}
::xrefblk_t const *cxxbridge1$unique_ptr$xrefblk_t$get(::std::unique_ptr<::xrefblk_t> const &ptr) noexcept {
  return ptr.get();
}
::xrefblk_t *cxxbridge1$unique_ptr$xrefblk_t$release(::std::unique_ptr<::xrefblk_t> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$xrefblk_t$drop(::std::unique_ptr<::xrefblk_t> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::xrefblk_t>::value>{}(ptr);
}

static_assert(sizeof(::std::shared_ptr<::xrefblk_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::shared_ptr<::xrefblk_t>) == alignof(void *), "");
void cxxbridge1$shared_ptr$xrefblk_t$null(::std::shared_ptr<::xrefblk_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::xrefblk_t>();
}
::xrefblk_t *cxxbridge1$shared_ptr$xrefblk_t$uninit(::std::shared_ptr<::xrefblk_t> *ptr) noexcept {
  ::xrefblk_t *uninit = reinterpret_cast<::xrefblk_t *>(new ::rust::MaybeUninit<::xrefblk_t>);
  ::new (ptr) ::std::shared_ptr<::xrefblk_t>(uninit);
  return uninit;
}
void cxxbridge1$shared_ptr$xrefblk_t$clone(::std::shared_ptr<::xrefblk_t> const &self, ::std::shared_ptr<::xrefblk_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::xrefblk_t>(self);
}
::xrefblk_t const *cxxbridge1$shared_ptr$xrefblk_t$get(::std::shared_ptr<::xrefblk_t> const &self) noexcept {
  return self.get();
}
void cxxbridge1$shared_ptr$xrefblk_t$drop(::std::shared_ptr<::xrefblk_t> *self) noexcept {
  self->~shared_ptr();
}

static_assert(sizeof(::std::weak_ptr<::xrefblk_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::weak_ptr<::xrefblk_t>) == alignof(void *), "");
void cxxbridge1$weak_ptr$xrefblk_t$null(::std::weak_ptr<::xrefblk_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::xrefblk_t>();
}
void cxxbridge1$weak_ptr$xrefblk_t$clone(::std::weak_ptr<::xrefblk_t> const &self, ::std::weak_ptr<::xrefblk_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::xrefblk_t>(self);
}
void cxxbridge1$weak_ptr$xrefblk_t$downgrade(::std::shared_ptr<::xrefblk_t> const &shared, ::std::weak_ptr<::xrefblk_t> *weak) noexcept {
  ::new (weak) ::std::weak_ptr<::xrefblk_t>(shared);
}
void cxxbridge1$weak_ptr$xrefblk_t$upgrade(::std::weak_ptr<::xrefblk_t> const &weak, ::std::shared_ptr<::xrefblk_t> *shared) noexcept {
  ::new (shared) ::std::shared_ptr<::xrefblk_t>(weak.lock());
}
void cxxbridge1$weak_ptr$xrefblk_t$drop(::std::weak_ptr<::xrefblk_t> *self) noexcept {
  self->~weak_ptr();
}

::std::vector<::xrefblk_t> *cxxbridge1$std$vector$xrefblk_t$new() noexcept {
  return new ::std::vector<::xrefblk_t>();
}
::std::size_t cxxbridge1$std$vector$xrefblk_t$size(::std::vector<::xrefblk_t> const &s) noexcept {
  return s.size();
}
::xrefblk_t *cxxbridge1$std$vector$xrefblk_t$get_unchecked(::std::vector<::xrefblk_t> *s, ::std::size_t pos) noexcept {
  return &(*s)[pos];
}
void cxxbridge1$std$vector$xrefblk_t$push_back(::std::vector<::xrefblk_t> *v, ::xrefblk_t *value) noexcept {
  v->push_back(::std::move(*value));
  ::rust::destroy(value);
}
void cxxbridge1$std$vector$xrefblk_t$pop_back(::std::vector<::xrefblk_t> *v, ::xrefblk_t *out) noexcept {
  ::new (out) ::xrefblk_t(::std::move(v->back()));
  v->pop_back();
}
static_assert(sizeof(::std::unique_ptr<::std::vector<::xrefblk_t>>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::std::vector<::xrefblk_t>>) == alignof(void *), "");
void cxxbridge1$unique_ptr$std$vector$xrefblk_t$null(::std::unique_ptr<::std::vector<::xrefblk_t>> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::std::vector<::xrefblk_t>>();
}
void cxxbridge1$unique_ptr$std$vector$xrefblk_t$raw(::std::unique_ptr<::std::vector<::xrefblk_t>> *ptr, ::std::vector<::xrefblk_t> *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::std::vector<::xrefblk_t>>(raw);
}
::std::vector<::xrefblk_t> const *cxxbridge1$unique_ptr$std$vector$xrefblk_t$get(::std::unique_ptr<::std::vector<::xrefblk_t>> const &ptr) noexcept {
  return ptr.get();
}
::std::vector<::xrefblk_t> *cxxbridge1$unique_ptr$std$vector$xrefblk_t$release(::std::unique_ptr<::std::vector<::xrefblk_t>> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$std$vector$xrefblk_t$drop(::std::unique_ptr<::std::vector<::xrefblk_t>> *ptr) noexcept {
  ptr->~unique_ptr();
}

static_assert(::rust::detail::is_complete<::processor_t>::value, "definition of processor_t is required");
static_assert(sizeof(::std::unique_ptr<::processor_t>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::processor_t>) == alignof(void *), "");
void cxxbridge1$unique_ptr$processor_t$null(::std::unique_ptr<::processor_t> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::processor_t>();
}
::processor_t *cxxbridge1$unique_ptr$processor_t$uninit(::std::unique_ptr<::processor_t> *ptr) noexcept {
  ::processor_t *uninit = reinterpret_cast<::processor_t *>(new ::rust::MaybeUninit<::processor_t>);
  ::new (ptr) ::std::unique_ptr<::processor_t>(uninit);
  return uninit;
}
void cxxbridge1$unique_ptr$processor_t$raw(::std::unique_ptr<::processor_t> *ptr, ::processor_t *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::processor_t>(raw);
}
::processor_t const *cxxbridge1$unique_ptr$processor_t$get(::std::unique_ptr<::processor_t> const &ptr) noexcept {
  return ptr.get();
}
::processor_t *cxxbridge1$unique_ptr$processor_t$release(::std::unique_ptr<::processor_t> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$processor_t$drop(::std::unique_ptr<::processor_t> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::processor_t>::value>{}(ptr);
}

static_assert(sizeof(::std::shared_ptr<::processor_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::shared_ptr<::processor_t>) == alignof(void *), "");
void cxxbridge1$shared_ptr$processor_t$null(::std::shared_ptr<::processor_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::processor_t>();
}
::processor_t *cxxbridge1$shared_ptr$processor_t$uninit(::std::shared_ptr<::processor_t> *ptr) noexcept {
  ::processor_t *uninit = reinterpret_cast<::processor_t *>(new ::rust::MaybeUninit<::processor_t>);
  ::new (ptr) ::std::shared_ptr<::processor_t>(uninit);
  return uninit;
}
void cxxbridge1$shared_ptr$processor_t$clone(::std::shared_ptr<::processor_t> const &self, ::std::shared_ptr<::processor_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::processor_t>(self);
}
::processor_t const *cxxbridge1$shared_ptr$processor_t$get(::std::shared_ptr<::processor_t> const &self) noexcept {
  return self.get();
}
void cxxbridge1$shared_ptr$processor_t$drop(::std::shared_ptr<::processor_t> *self) noexcept {
  self->~shared_ptr();
}

static_assert(sizeof(::std::weak_ptr<::processor_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::weak_ptr<::processor_t>) == alignof(void *), "");
void cxxbridge1$weak_ptr$processor_t$null(::std::weak_ptr<::processor_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::processor_t>();
}
void cxxbridge1$weak_ptr$processor_t$clone(::std::weak_ptr<::processor_t> const &self, ::std::weak_ptr<::processor_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::processor_t>(self);
}
void cxxbridge1$weak_ptr$processor_t$downgrade(::std::shared_ptr<::processor_t> const &shared, ::std::weak_ptr<::processor_t> *weak) noexcept {
  ::new (weak) ::std::weak_ptr<::processor_t>(shared);
}
void cxxbridge1$weak_ptr$processor_t$upgrade(::std::weak_ptr<::processor_t> const &weak, ::std::shared_ptr<::processor_t> *shared) noexcept {
  ::new (shared) ::std::shared_ptr<::processor_t>(weak.lock());
}
void cxxbridge1$weak_ptr$processor_t$drop(::std::weak_ptr<::processor_t> *self) noexcept {
  self->~weak_ptr();
}

static_assert(::rust::detail::is_complete<::plugin_t>::value, "definition of plugin_t is required");
static_assert(sizeof(::std::unique_ptr<::plugin_t>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::plugin_t>) == alignof(void *), "");
void cxxbridge1$unique_ptr$plugin_t$null(::std::unique_ptr<::plugin_t> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::plugin_t>();
}
::plugin_t *cxxbridge1$unique_ptr$plugin_t$uninit(::std::unique_ptr<::plugin_t> *ptr) noexcept {
  ::plugin_t *uninit = reinterpret_cast<::plugin_t *>(new ::rust::MaybeUninit<::plugin_t>);
  ::new (ptr) ::std::unique_ptr<::plugin_t>(uninit);
  return uninit;
}
void cxxbridge1$unique_ptr$plugin_t$raw(::std::unique_ptr<::plugin_t> *ptr, ::plugin_t *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::plugin_t>(raw);
}
::plugin_t const *cxxbridge1$unique_ptr$plugin_t$get(::std::unique_ptr<::plugin_t> const &ptr) noexcept {
  return ptr.get();
}
::plugin_t *cxxbridge1$unique_ptr$plugin_t$release(::std::unique_ptr<::plugin_t> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$plugin_t$drop(::std::unique_ptr<::plugin_t> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::plugin_t>::value>{}(ptr);
}

static_assert(sizeof(::std::shared_ptr<::plugin_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::shared_ptr<::plugin_t>) == alignof(void *), "");
void cxxbridge1$shared_ptr$plugin_t$null(::std::shared_ptr<::plugin_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::plugin_t>();
}
::plugin_t *cxxbridge1$shared_ptr$plugin_t$uninit(::std::shared_ptr<::plugin_t> *ptr) noexcept {
  ::plugin_t *uninit = reinterpret_cast<::plugin_t *>(new ::rust::MaybeUninit<::plugin_t>);
  ::new (ptr) ::std::shared_ptr<::plugin_t>(uninit);
  return uninit;
}
void cxxbridge1$shared_ptr$plugin_t$clone(::std::shared_ptr<::plugin_t> const &self, ::std::shared_ptr<::plugin_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::plugin_t>(self);
}
::plugin_t const *cxxbridge1$shared_ptr$plugin_t$get(::std::shared_ptr<::plugin_t> const &self) noexcept {
  return self.get();
}
void cxxbridge1$shared_ptr$plugin_t$drop(::std::shared_ptr<::plugin_t> *self) noexcept {
  self->~shared_ptr();
}

static_assert(sizeof(::std::weak_ptr<::plugin_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::weak_ptr<::plugin_t>) == alignof(void *), "");
void cxxbridge1$weak_ptr$plugin_t$null(::std::weak_ptr<::plugin_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::plugin_t>();
}
void cxxbridge1$weak_ptr$plugin_t$clone(::std::weak_ptr<::plugin_t> const &self, ::std::weak_ptr<::plugin_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::plugin_t>(self);
}
void cxxbridge1$weak_ptr$plugin_t$downgrade(::std::shared_ptr<::plugin_t> const &shared, ::std::weak_ptr<::plugin_t> *weak) noexcept {
  ::new (weak) ::std::weak_ptr<::plugin_t>(shared);
}
void cxxbridge1$weak_ptr$plugin_t$upgrade(::std::weak_ptr<::plugin_t> const &weak, ::std::shared_ptr<::plugin_t> *shared) noexcept {
  ::new (shared) ::std::shared_ptr<::plugin_t>(weak.lock());
}
void cxxbridge1$weak_ptr$plugin_t$drop(::std::weak_ptr<::plugin_t> *self) noexcept {
  self->~weak_ptr();
}

::std::vector<::plugin_t> *cxxbridge1$std$vector$plugin_t$new() noexcept {
  return new ::std::vector<::plugin_t>();
}
::std::size_t cxxbridge1$std$vector$plugin_t$size(::std::vector<::plugin_t> const &s) noexcept {
  return s.size();
}
::plugin_t *cxxbridge1$std$vector$plugin_t$get_unchecked(::std::vector<::plugin_t> *s, ::std::size_t pos) noexcept {
  return &(*s)[pos];
}
void cxxbridge1$std$vector$plugin_t$push_back(::std::vector<::plugin_t> *v, ::plugin_t *value) noexcept {
  v->push_back(::std::move(*value));
  ::rust::destroy(value);
}
void cxxbridge1$std$vector$plugin_t$pop_back(::std::vector<::plugin_t> *v, ::plugin_t *out) noexcept {
  ::new (out) ::plugin_t(::std::move(v->back()));
  v->pop_back();
}
static_assert(sizeof(::std::unique_ptr<::std::vector<::plugin_t>>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::std::vector<::plugin_t>>) == alignof(void *), "");
void cxxbridge1$unique_ptr$std$vector$plugin_t$null(::std::unique_ptr<::std::vector<::plugin_t>> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::std::vector<::plugin_t>>();
}
void cxxbridge1$unique_ptr$std$vector$plugin_t$raw(::std::unique_ptr<::std::vector<::plugin_t>> *ptr, ::std::vector<::plugin_t> *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::std::vector<::plugin_t>>(raw);
}
::std::vector<::plugin_t> const *cxxbridge1$unique_ptr$std$vector$plugin_t$get(::std::unique_ptr<::std::vector<::plugin_t>> const &ptr) noexcept {
  return ptr.get();
}
::std::vector<::plugin_t> *cxxbridge1$unique_ptr$std$vector$plugin_t$release(::std::unique_ptr<::std::vector<::plugin_t>> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$std$vector$plugin_t$drop(::std::unique_ptr<::std::vector<::plugin_t>> *ptr) noexcept {
  ptr->~unique_ptr();
}

static_assert(::rust::detail::is_complete<::qstring_char_AutocxxConcrete>::value, "definition of qstring_char_AutocxxConcrete is required");
static_assert(sizeof(::std::unique_ptr<::qstring_char_AutocxxConcrete>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::qstring_char_AutocxxConcrete>) == alignof(void *), "");
void cxxbridge1$unique_ptr$qstring_char_AutocxxConcrete$null(::std::unique_ptr<::qstring_char_AutocxxConcrete> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::qstring_char_AutocxxConcrete>();
}
void cxxbridge1$unique_ptr$qstring_char_AutocxxConcrete$raw(::std::unique_ptr<::qstring_char_AutocxxConcrete> *ptr, ::qstring_char_AutocxxConcrete *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::qstring_char_AutocxxConcrete>(raw);
}
::qstring_char_AutocxxConcrete const *cxxbridge1$unique_ptr$qstring_char_AutocxxConcrete$get(::std::unique_ptr<::qstring_char_AutocxxConcrete> const &ptr) noexcept {
  return ptr.get();
}
::qstring_char_AutocxxConcrete *cxxbridge1$unique_ptr$qstring_char_AutocxxConcrete$release(::std::unique_ptr<::qstring_char_AutocxxConcrete> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$qstring_char_AutocxxConcrete$drop(::std::unique_ptr<::qstring_char_AutocxxConcrete> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::qstring_char_AutocxxConcrete>::value>{}(ptr);
}

static_assert(sizeof(::std::shared_ptr<::qstring_char_AutocxxConcrete>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::shared_ptr<::qstring_char_AutocxxConcrete>) == alignof(void *), "");
void cxxbridge1$shared_ptr$qstring_char_AutocxxConcrete$null(::std::shared_ptr<::qstring_char_AutocxxConcrete> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::qstring_char_AutocxxConcrete>();
}
void cxxbridge1$shared_ptr$qstring_char_AutocxxConcrete$clone(::std::shared_ptr<::qstring_char_AutocxxConcrete> const &self, ::std::shared_ptr<::qstring_char_AutocxxConcrete> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::qstring_char_AutocxxConcrete>(self);
}
::qstring_char_AutocxxConcrete const *cxxbridge1$shared_ptr$qstring_char_AutocxxConcrete$get(::std::shared_ptr<::qstring_char_AutocxxConcrete> const &self) noexcept {
  return self.get();
}
void cxxbridge1$shared_ptr$qstring_char_AutocxxConcrete$drop(::std::shared_ptr<::qstring_char_AutocxxConcrete> *self) noexcept {
  self->~shared_ptr();
}

static_assert(sizeof(::std::weak_ptr<::qstring_char_AutocxxConcrete>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::weak_ptr<::qstring_char_AutocxxConcrete>) == alignof(void *), "");
void cxxbridge1$weak_ptr$qstring_char_AutocxxConcrete$null(::std::weak_ptr<::qstring_char_AutocxxConcrete> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::qstring_char_AutocxxConcrete>();
}
void cxxbridge1$weak_ptr$qstring_char_AutocxxConcrete$clone(::std::weak_ptr<::qstring_char_AutocxxConcrete> const &self, ::std::weak_ptr<::qstring_char_AutocxxConcrete> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::qstring_char_AutocxxConcrete>(self);
}
void cxxbridge1$weak_ptr$qstring_char_AutocxxConcrete$downgrade(::std::shared_ptr<::qstring_char_AutocxxConcrete> const &shared, ::std::weak_ptr<::qstring_char_AutocxxConcrete> *weak) noexcept {
  ::new (weak) ::std::weak_ptr<::qstring_char_AutocxxConcrete>(shared);
}
void cxxbridge1$weak_ptr$qstring_char_AutocxxConcrete$upgrade(::std::weak_ptr<::qstring_char_AutocxxConcrete> const &weak, ::std::shared_ptr<::qstring_char_AutocxxConcrete> *shared) noexcept {
  ::new (shared) ::std::shared_ptr<::qstring_char_AutocxxConcrete>(weak.lock());
}
void cxxbridge1$weak_ptr$qstring_char_AutocxxConcrete$drop(::std::weak_ptr<::qstring_char_AutocxxConcrete> *self) noexcept {
  self->~weak_ptr();
}

static_assert(::rust::detail::is_complete<::_IO_FILE>::value, "definition of _IO_FILE is required");
static_assert(sizeof(::std::unique_ptr<::_IO_FILE>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::_IO_FILE>) == alignof(void *), "");
void cxxbridge1$unique_ptr$_IO_FILE$null(::std::unique_ptr<::_IO_FILE> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::_IO_FILE>();
}
::_IO_FILE *cxxbridge1$unique_ptr$_IO_FILE$uninit(::std::unique_ptr<::_IO_FILE> *ptr) noexcept {
  ::_IO_FILE *uninit = reinterpret_cast<::_IO_FILE *>(new ::rust::MaybeUninit<::_IO_FILE>);
  ::new (ptr) ::std::unique_ptr<::_IO_FILE>(uninit);
  return uninit;
}
void cxxbridge1$unique_ptr$_IO_FILE$raw(::std::unique_ptr<::_IO_FILE> *ptr, ::_IO_FILE *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::_IO_FILE>(raw);
}
::_IO_FILE const *cxxbridge1$unique_ptr$_IO_FILE$get(::std::unique_ptr<::_IO_FILE> const &ptr) noexcept {
  return ptr.get();
}
::_IO_FILE *cxxbridge1$unique_ptr$_IO_FILE$release(::std::unique_ptr<::_IO_FILE> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$_IO_FILE$drop(::std::unique_ptr<::_IO_FILE> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::_IO_FILE>::value>{}(ptr);
}

static_assert(sizeof(::std::shared_ptr<::_IO_FILE>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::shared_ptr<::_IO_FILE>) == alignof(void *), "");
void cxxbridge1$shared_ptr$_IO_FILE$null(::std::shared_ptr<::_IO_FILE> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::_IO_FILE>();
}
::_IO_FILE *cxxbridge1$shared_ptr$_IO_FILE$uninit(::std::shared_ptr<::_IO_FILE> *ptr) noexcept {
  ::_IO_FILE *uninit = reinterpret_cast<::_IO_FILE *>(new ::rust::MaybeUninit<::_IO_FILE>);
  ::new (ptr) ::std::shared_ptr<::_IO_FILE>(uninit);
  return uninit;
}
void cxxbridge1$shared_ptr$_IO_FILE$clone(::std::shared_ptr<::_IO_FILE> const &self, ::std::shared_ptr<::_IO_FILE> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::_IO_FILE>(self);
}
::_IO_FILE const *cxxbridge1$shared_ptr$_IO_FILE$get(::std::shared_ptr<::_IO_FILE> const &self) noexcept {
  return self.get();
}
void cxxbridge1$shared_ptr$_IO_FILE$drop(::std::shared_ptr<::_IO_FILE> *self) noexcept {
  self->~shared_ptr();
}

static_assert(sizeof(::std::weak_ptr<::_IO_FILE>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::weak_ptr<::_IO_FILE>) == alignof(void *), "");
void cxxbridge1$weak_ptr$_IO_FILE$null(::std::weak_ptr<::_IO_FILE> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::_IO_FILE>();
}
void cxxbridge1$weak_ptr$_IO_FILE$clone(::std::weak_ptr<::_IO_FILE> const &self, ::std::weak_ptr<::_IO_FILE> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::_IO_FILE>(self);
}
void cxxbridge1$weak_ptr$_IO_FILE$downgrade(::std::shared_ptr<::_IO_FILE> const &shared, ::std::weak_ptr<::_IO_FILE> *weak) noexcept {
  ::new (weak) ::std::weak_ptr<::_IO_FILE>(shared);
}
void cxxbridge1$weak_ptr$_IO_FILE$upgrade(::std::weak_ptr<::_IO_FILE> const &weak, ::std::shared_ptr<::_IO_FILE> *shared) noexcept {
  ::new (shared) ::std::shared_ptr<::_IO_FILE>(weak.lock());
}
void cxxbridge1$weak_ptr$_IO_FILE$drop(::std::weak_ptr<::_IO_FILE> *self) noexcept {
  self->~weak_ptr();
}

::std::vector<::_IO_FILE> *cxxbridge1$std$vector$_IO_FILE$new() noexcept {
  return new ::std::vector<::_IO_FILE>();
}
::std::size_t cxxbridge1$std$vector$_IO_FILE$size(::std::vector<::_IO_FILE> const &s) noexcept {
  return s.size();
}
::_IO_FILE *cxxbridge1$std$vector$_IO_FILE$get_unchecked(::std::vector<::_IO_FILE> *s, ::std::size_t pos) noexcept {
  return &(*s)[pos];
}
void cxxbridge1$std$vector$_IO_FILE$push_back(::std::vector<::_IO_FILE> *v, ::_IO_FILE *value) noexcept {
  v->push_back(::std::move(*value));
  ::rust::destroy(value);
}
void cxxbridge1$std$vector$_IO_FILE$pop_back(::std::vector<::_IO_FILE> *v, ::_IO_FILE *out) noexcept {
  ::new (out) ::_IO_FILE(::std::move(v->back()));
  v->pop_back();
}
static_assert(sizeof(::std::unique_ptr<::std::vector<::_IO_FILE>>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::std::vector<::_IO_FILE>>) == alignof(void *), "");
void cxxbridge1$unique_ptr$std$vector$_IO_FILE$null(::std::unique_ptr<::std::vector<::_IO_FILE>> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::std::vector<::_IO_FILE>>();
}
void cxxbridge1$unique_ptr$std$vector$_IO_FILE$raw(::std::unique_ptr<::std::vector<::_IO_FILE>> *ptr, ::std::vector<::_IO_FILE> *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::std::vector<::_IO_FILE>>(raw);
}
::std::vector<::_IO_FILE> const *cxxbridge1$unique_ptr$std$vector$_IO_FILE$get(::std::unique_ptr<::std::vector<::_IO_FILE>> const &ptr) noexcept {
  return ptr.get();
}
::std::vector<::_IO_FILE> *cxxbridge1$unique_ptr$std$vector$_IO_FILE$release(::std::unique_ptr<::std::vector<::_IO_FILE>> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$std$vector$_IO_FILE$drop(::std::unique_ptr<::std::vector<::_IO_FILE>> *ptr) noexcept {
  ptr->~unique_ptr();
}

static_assert(::rust::detail::is_complete<::node_iterator>::value, "definition of node_iterator is required");
static_assert(sizeof(::std::unique_ptr<::node_iterator>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::node_iterator>) == alignof(void *), "");
void cxxbridge1$unique_ptr$node_iterator$null(::std::unique_ptr<::node_iterator> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::node_iterator>();
}
::node_iterator *cxxbridge1$unique_ptr$node_iterator$uninit(::std::unique_ptr<::node_iterator> *ptr) noexcept {
  ::node_iterator *uninit = reinterpret_cast<::node_iterator *>(new ::rust::MaybeUninit<::node_iterator>);
  ::new (ptr) ::std::unique_ptr<::node_iterator>(uninit);
  return uninit;
}
void cxxbridge1$unique_ptr$node_iterator$raw(::std::unique_ptr<::node_iterator> *ptr, ::node_iterator *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::node_iterator>(raw);
}
::node_iterator const *cxxbridge1$unique_ptr$node_iterator$get(::std::unique_ptr<::node_iterator> const &ptr) noexcept {
  return ptr.get();
}
::node_iterator *cxxbridge1$unique_ptr$node_iterator$release(::std::unique_ptr<::node_iterator> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$node_iterator$drop(::std::unique_ptr<::node_iterator> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::node_iterator>::value>{}(ptr);
}

static_assert(sizeof(::std::shared_ptr<::node_iterator>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::shared_ptr<::node_iterator>) == alignof(void *), "");
void cxxbridge1$shared_ptr$node_iterator$null(::std::shared_ptr<::node_iterator> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::node_iterator>();
}
::node_iterator *cxxbridge1$shared_ptr$node_iterator$uninit(::std::shared_ptr<::node_iterator> *ptr) noexcept {
  ::node_iterator *uninit = reinterpret_cast<::node_iterator *>(new ::rust::MaybeUninit<::node_iterator>);
  ::new (ptr) ::std::shared_ptr<::node_iterator>(uninit);
  return uninit;
}
void cxxbridge1$shared_ptr$node_iterator$clone(::std::shared_ptr<::node_iterator> const &self, ::std::shared_ptr<::node_iterator> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::node_iterator>(self);
}
::node_iterator const *cxxbridge1$shared_ptr$node_iterator$get(::std::shared_ptr<::node_iterator> const &self) noexcept {
  return self.get();
}
void cxxbridge1$shared_ptr$node_iterator$drop(::std::shared_ptr<::node_iterator> *self) noexcept {
  self->~shared_ptr();
}

static_assert(sizeof(::std::weak_ptr<::node_iterator>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::weak_ptr<::node_iterator>) == alignof(void *), "");
void cxxbridge1$weak_ptr$node_iterator$null(::std::weak_ptr<::node_iterator> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::node_iterator>();
}
void cxxbridge1$weak_ptr$node_iterator$clone(::std::weak_ptr<::node_iterator> const &self, ::std::weak_ptr<::node_iterator> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::node_iterator>(self);
}
void cxxbridge1$weak_ptr$node_iterator$downgrade(::std::shared_ptr<::node_iterator> const &shared, ::std::weak_ptr<::node_iterator> *weak) noexcept {
  ::new (weak) ::std::weak_ptr<::node_iterator>(shared);
}
void cxxbridge1$weak_ptr$node_iterator$upgrade(::std::weak_ptr<::node_iterator> const &weak, ::std::shared_ptr<::node_iterator> *shared) noexcept {
  ::new (shared) ::std::shared_ptr<::node_iterator>(weak.lock());
}
void cxxbridge1$weak_ptr$node_iterator$drop(::std::weak_ptr<::node_iterator> *self) noexcept {
  self->~weak_ptr();
}

::std::vector<::node_iterator> *cxxbridge1$std$vector$node_iterator$new() noexcept {
  return new ::std::vector<::node_iterator>();
}
::std::size_t cxxbridge1$std$vector$node_iterator$size(::std::vector<::node_iterator> const &s) noexcept {
  return s.size();
}
::node_iterator *cxxbridge1$std$vector$node_iterator$get_unchecked(::std::vector<::node_iterator> *s, ::std::size_t pos) noexcept {
  return &(*s)[pos];
}
void cxxbridge1$std$vector$node_iterator$push_back(::std::vector<::node_iterator> *v, ::node_iterator *value) noexcept {
  v->push_back(::std::move(*value));
  ::rust::destroy(value);
}
void cxxbridge1$std$vector$node_iterator$pop_back(::std::vector<::node_iterator> *v, ::node_iterator *out) noexcept {
  ::new (out) ::node_iterator(::std::move(v->back()));
  v->pop_back();
}
static_assert(sizeof(::std::unique_ptr<::std::vector<::node_iterator>>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::std::vector<::node_iterator>>) == alignof(void *), "");
void cxxbridge1$unique_ptr$std$vector$node_iterator$null(::std::unique_ptr<::std::vector<::node_iterator>> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::std::vector<::node_iterator>>();
}
void cxxbridge1$unique_ptr$std$vector$node_iterator$raw(::std::unique_ptr<::std::vector<::node_iterator>> *ptr, ::std::vector<::node_iterator> *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::std::vector<::node_iterator>>(raw);
}
::std::vector<::node_iterator> const *cxxbridge1$unique_ptr$std$vector$node_iterator$get(::std::unique_ptr<::std::vector<::node_iterator>> const &ptr) noexcept {
  return ptr.get();
}
::std::vector<::node_iterator> *cxxbridge1$unique_ptr$std$vector$node_iterator$release(::std::unique_ptr<::std::vector<::node_iterator>> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$std$vector$node_iterator$drop(::std::unique_ptr<::std::vector<::node_iterator>> *ptr) noexcept {
  ptr->~unique_ptr();
}

static_assert(::rust::detail::is_complete<::rangevec_t>::value, "definition of rangevec_t is required");
static_assert(sizeof(::std::unique_ptr<::rangevec_t>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::rangevec_t>) == alignof(void *), "");
void cxxbridge1$unique_ptr$rangevec_t$null(::std::unique_ptr<::rangevec_t> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::rangevec_t>();
}
::rangevec_t *cxxbridge1$unique_ptr$rangevec_t$uninit(::std::unique_ptr<::rangevec_t> *ptr) noexcept {
  ::rangevec_t *uninit = reinterpret_cast<::rangevec_t *>(new ::rust::MaybeUninit<::rangevec_t>);
  ::new (ptr) ::std::unique_ptr<::rangevec_t>(uninit);
  return uninit;
}
void cxxbridge1$unique_ptr$rangevec_t$raw(::std::unique_ptr<::rangevec_t> *ptr, ::rangevec_t *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::rangevec_t>(raw);
}
::rangevec_t const *cxxbridge1$unique_ptr$rangevec_t$get(::std::unique_ptr<::rangevec_t> const &ptr) noexcept {
  return ptr.get();
}
::rangevec_t *cxxbridge1$unique_ptr$rangevec_t$release(::std::unique_ptr<::rangevec_t> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$rangevec_t$drop(::std::unique_ptr<::rangevec_t> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::rangevec_t>::value>{}(ptr);
}

static_assert(sizeof(::std::shared_ptr<::rangevec_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::shared_ptr<::rangevec_t>) == alignof(void *), "");
void cxxbridge1$shared_ptr$rangevec_t$null(::std::shared_ptr<::rangevec_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::rangevec_t>();
}
::rangevec_t *cxxbridge1$shared_ptr$rangevec_t$uninit(::std::shared_ptr<::rangevec_t> *ptr) noexcept {
  ::rangevec_t *uninit = reinterpret_cast<::rangevec_t *>(new ::rust::MaybeUninit<::rangevec_t>);
  ::new (ptr) ::std::shared_ptr<::rangevec_t>(uninit);
  return uninit;
}
void cxxbridge1$shared_ptr$rangevec_t$clone(::std::shared_ptr<::rangevec_t> const &self, ::std::shared_ptr<::rangevec_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::rangevec_t>(self);
}
::rangevec_t const *cxxbridge1$shared_ptr$rangevec_t$get(::std::shared_ptr<::rangevec_t> const &self) noexcept {
  return self.get();
}
void cxxbridge1$shared_ptr$rangevec_t$drop(::std::shared_ptr<::rangevec_t> *self) noexcept {
  self->~shared_ptr();
}

static_assert(sizeof(::std::weak_ptr<::rangevec_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::weak_ptr<::rangevec_t>) == alignof(void *), "");
void cxxbridge1$weak_ptr$rangevec_t$null(::std::weak_ptr<::rangevec_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::rangevec_t>();
}
void cxxbridge1$weak_ptr$rangevec_t$clone(::std::weak_ptr<::rangevec_t> const &self, ::std::weak_ptr<::rangevec_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::rangevec_t>(self);
}
void cxxbridge1$weak_ptr$rangevec_t$downgrade(::std::shared_ptr<::rangevec_t> const &shared, ::std::weak_ptr<::rangevec_t> *weak) noexcept {
  ::new (weak) ::std::weak_ptr<::rangevec_t>(shared);
}
void cxxbridge1$weak_ptr$rangevec_t$upgrade(::std::weak_ptr<::rangevec_t> const &weak, ::std::shared_ptr<::rangevec_t> *shared) noexcept {
  ::new (shared) ::std::shared_ptr<::rangevec_t>(weak.lock());
}
void cxxbridge1$weak_ptr$rangevec_t$drop(::std::weak_ptr<::rangevec_t> *self) noexcept {
  self->~weak_ptr();
}

static_assert(::rust::detail::is_complete<::fpvalue_t>::value, "definition of fpvalue_t is required");
static_assert(sizeof(::std::unique_ptr<::fpvalue_t>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::fpvalue_t>) == alignof(void *), "");
void cxxbridge1$unique_ptr$fpvalue_t$null(::std::unique_ptr<::fpvalue_t> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::fpvalue_t>();
}
::fpvalue_t *cxxbridge1$unique_ptr$fpvalue_t$uninit(::std::unique_ptr<::fpvalue_t> *ptr) noexcept {
  ::fpvalue_t *uninit = reinterpret_cast<::fpvalue_t *>(new ::rust::MaybeUninit<::fpvalue_t>);
  ::new (ptr) ::std::unique_ptr<::fpvalue_t>(uninit);
  return uninit;
}
void cxxbridge1$unique_ptr$fpvalue_t$raw(::std::unique_ptr<::fpvalue_t> *ptr, ::fpvalue_t *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::fpvalue_t>(raw);
}
::fpvalue_t const *cxxbridge1$unique_ptr$fpvalue_t$get(::std::unique_ptr<::fpvalue_t> const &ptr) noexcept {
  return ptr.get();
}
::fpvalue_t *cxxbridge1$unique_ptr$fpvalue_t$release(::std::unique_ptr<::fpvalue_t> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$fpvalue_t$drop(::std::unique_ptr<::fpvalue_t> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::fpvalue_t>::value>{}(ptr);
}

static_assert(sizeof(::std::shared_ptr<::fpvalue_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::shared_ptr<::fpvalue_t>) == alignof(void *), "");
void cxxbridge1$shared_ptr$fpvalue_t$null(::std::shared_ptr<::fpvalue_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::fpvalue_t>();
}
::fpvalue_t *cxxbridge1$shared_ptr$fpvalue_t$uninit(::std::shared_ptr<::fpvalue_t> *ptr) noexcept {
  ::fpvalue_t *uninit = reinterpret_cast<::fpvalue_t *>(new ::rust::MaybeUninit<::fpvalue_t>);
  ::new (ptr) ::std::shared_ptr<::fpvalue_t>(uninit);
  return uninit;
}
void cxxbridge1$shared_ptr$fpvalue_t$clone(::std::shared_ptr<::fpvalue_t> const &self, ::std::shared_ptr<::fpvalue_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::fpvalue_t>(self);
}
::fpvalue_t const *cxxbridge1$shared_ptr$fpvalue_t$get(::std::shared_ptr<::fpvalue_t> const &self) noexcept {
  return self.get();
}
void cxxbridge1$shared_ptr$fpvalue_t$drop(::std::shared_ptr<::fpvalue_t> *self) noexcept {
  self->~shared_ptr();
}

static_assert(sizeof(::std::weak_ptr<::fpvalue_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::weak_ptr<::fpvalue_t>) == alignof(void *), "");
void cxxbridge1$weak_ptr$fpvalue_t$null(::std::weak_ptr<::fpvalue_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::fpvalue_t>();
}
void cxxbridge1$weak_ptr$fpvalue_t$clone(::std::weak_ptr<::fpvalue_t> const &self, ::std::weak_ptr<::fpvalue_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::fpvalue_t>(self);
}
void cxxbridge1$weak_ptr$fpvalue_t$downgrade(::std::shared_ptr<::fpvalue_t> const &shared, ::std::weak_ptr<::fpvalue_t> *weak) noexcept {
  ::new (weak) ::std::weak_ptr<::fpvalue_t>(shared);
}
void cxxbridge1$weak_ptr$fpvalue_t$upgrade(::std::weak_ptr<::fpvalue_t> const &weak, ::std::shared_ptr<::fpvalue_t> *shared) noexcept {
  ::new (shared) ::std::shared_ptr<::fpvalue_t>(weak.lock());
}
void cxxbridge1$weak_ptr$fpvalue_t$drop(::std::weak_ptr<::fpvalue_t> *self) noexcept {
  self->~weak_ptr();
}

::std::vector<::fpvalue_t> *cxxbridge1$std$vector$fpvalue_t$new() noexcept {
  return new ::std::vector<::fpvalue_t>();
}
::std::size_t cxxbridge1$std$vector$fpvalue_t$size(::std::vector<::fpvalue_t> const &s) noexcept {
  return s.size();
}
::fpvalue_t *cxxbridge1$std$vector$fpvalue_t$get_unchecked(::std::vector<::fpvalue_t> *s, ::std::size_t pos) noexcept {
  return &(*s)[pos];
}
void cxxbridge1$std$vector$fpvalue_t$push_back(::std::vector<::fpvalue_t> *v, ::fpvalue_t *value) noexcept {
  v->push_back(::std::move(*value));
  ::rust::destroy(value);
}
void cxxbridge1$std$vector$fpvalue_t$pop_back(::std::vector<::fpvalue_t> *v, ::fpvalue_t *out) noexcept {
  ::new (out) ::fpvalue_t(::std::move(v->back()));
  v->pop_back();
}
static_assert(sizeof(::std::unique_ptr<::std::vector<::fpvalue_t>>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::std::vector<::fpvalue_t>>) == alignof(void *), "");
void cxxbridge1$unique_ptr$std$vector$fpvalue_t$null(::std::unique_ptr<::std::vector<::fpvalue_t>> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::std::vector<::fpvalue_t>>();
}
void cxxbridge1$unique_ptr$std$vector$fpvalue_t$raw(::std::unique_ptr<::std::vector<::fpvalue_t>> *ptr, ::std::vector<::fpvalue_t> *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::std::vector<::fpvalue_t>>(raw);
}
::std::vector<::fpvalue_t> const *cxxbridge1$unique_ptr$std$vector$fpvalue_t$get(::std::unique_ptr<::std::vector<::fpvalue_t>> const &ptr) noexcept {
  return ptr.get();
}
::std::vector<::fpvalue_t> *cxxbridge1$unique_ptr$std$vector$fpvalue_t$release(::std::unique_ptr<::std::vector<::fpvalue_t>> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$std$vector$fpvalue_t$drop(::std::unique_ptr<::std::vector<::fpvalue_t>> *ptr) noexcept {
  ptr->~unique_ptr();
}

static_assert(::rust::detail::is_complete<::fpvalue_error_t>::value, "definition of fpvalue_error_t is required");
static_assert(sizeof(::std::unique_ptr<::fpvalue_error_t>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::fpvalue_error_t>) == alignof(void *), "");
void cxxbridge1$unique_ptr$fpvalue_error_t$null(::std::unique_ptr<::fpvalue_error_t> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::fpvalue_error_t>();
}
::fpvalue_error_t *cxxbridge1$unique_ptr$fpvalue_error_t$uninit(::std::unique_ptr<::fpvalue_error_t> *ptr) noexcept {
  ::fpvalue_error_t *uninit = reinterpret_cast<::fpvalue_error_t *>(new ::rust::MaybeUninit<::fpvalue_error_t>);
  ::new (ptr) ::std::unique_ptr<::fpvalue_error_t>(uninit);
  return uninit;
}
void cxxbridge1$unique_ptr$fpvalue_error_t$raw(::std::unique_ptr<::fpvalue_error_t> *ptr, ::fpvalue_error_t *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::fpvalue_error_t>(raw);
}
::fpvalue_error_t const *cxxbridge1$unique_ptr$fpvalue_error_t$get(::std::unique_ptr<::fpvalue_error_t> const &ptr) noexcept {
  return ptr.get();
}
::fpvalue_error_t *cxxbridge1$unique_ptr$fpvalue_error_t$release(::std::unique_ptr<::fpvalue_error_t> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$fpvalue_error_t$drop(::std::unique_ptr<::fpvalue_error_t> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::fpvalue_error_t>::value>{}(ptr);
}

static_assert(sizeof(::std::shared_ptr<::fpvalue_error_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::shared_ptr<::fpvalue_error_t>) == alignof(void *), "");
void cxxbridge1$shared_ptr$fpvalue_error_t$null(::std::shared_ptr<::fpvalue_error_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::fpvalue_error_t>();
}
::fpvalue_error_t *cxxbridge1$shared_ptr$fpvalue_error_t$uninit(::std::shared_ptr<::fpvalue_error_t> *ptr) noexcept {
  ::fpvalue_error_t *uninit = reinterpret_cast<::fpvalue_error_t *>(new ::rust::MaybeUninit<::fpvalue_error_t>);
  ::new (ptr) ::std::shared_ptr<::fpvalue_error_t>(uninit);
  return uninit;
}
void cxxbridge1$shared_ptr$fpvalue_error_t$clone(::std::shared_ptr<::fpvalue_error_t> const &self, ::std::shared_ptr<::fpvalue_error_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::fpvalue_error_t>(self);
}
::fpvalue_error_t const *cxxbridge1$shared_ptr$fpvalue_error_t$get(::std::shared_ptr<::fpvalue_error_t> const &self) noexcept {
  return self.get();
}
void cxxbridge1$shared_ptr$fpvalue_error_t$drop(::std::shared_ptr<::fpvalue_error_t> *self) noexcept {
  self->~shared_ptr();
}

static_assert(sizeof(::std::weak_ptr<::fpvalue_error_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::weak_ptr<::fpvalue_error_t>) == alignof(void *), "");
void cxxbridge1$weak_ptr$fpvalue_error_t$null(::std::weak_ptr<::fpvalue_error_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::fpvalue_error_t>();
}
void cxxbridge1$weak_ptr$fpvalue_error_t$clone(::std::weak_ptr<::fpvalue_error_t> const &self, ::std::weak_ptr<::fpvalue_error_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::fpvalue_error_t>(self);
}
void cxxbridge1$weak_ptr$fpvalue_error_t$downgrade(::std::shared_ptr<::fpvalue_error_t> const &shared, ::std::weak_ptr<::fpvalue_error_t> *weak) noexcept {
  ::new (weak) ::std::weak_ptr<::fpvalue_error_t>(shared);
}
void cxxbridge1$weak_ptr$fpvalue_error_t$upgrade(::std::weak_ptr<::fpvalue_error_t> const &weak, ::std::shared_ptr<::fpvalue_error_t> *shared) noexcept {
  ::new (shared) ::std::shared_ptr<::fpvalue_error_t>(weak.lock());
}
void cxxbridge1$weak_ptr$fpvalue_error_t$drop(::std::weak_ptr<::fpvalue_error_t> *self) noexcept {
  self->~weak_ptr();
}

::std::vector<::fpvalue_error_t> *cxxbridge1$std$vector$fpvalue_error_t$new() noexcept {
  return new ::std::vector<::fpvalue_error_t>();
}
::std::size_t cxxbridge1$std$vector$fpvalue_error_t$size(::std::vector<::fpvalue_error_t> const &s) noexcept {
  return s.size();
}
::fpvalue_error_t *cxxbridge1$std$vector$fpvalue_error_t$get_unchecked(::std::vector<::fpvalue_error_t> *s, ::std::size_t pos) noexcept {
  return &(*s)[pos];
}
void cxxbridge1$std$vector$fpvalue_error_t$push_back(::std::vector<::fpvalue_error_t> *v, ::fpvalue_error_t *value) noexcept {
  v->push_back(::std::move(*value));
  ::rust::destroy(value);
}
void cxxbridge1$std$vector$fpvalue_error_t$pop_back(::std::vector<::fpvalue_error_t> *v, ::fpvalue_error_t *out) noexcept {
  ::new (out) ::fpvalue_error_t(::std::move(v->back()));
  v->pop_back();
}
static_assert(sizeof(::std::unique_ptr<::std::vector<::fpvalue_error_t>>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::std::vector<::fpvalue_error_t>>) == alignof(void *), "");
void cxxbridge1$unique_ptr$std$vector$fpvalue_error_t$null(::std::unique_ptr<::std::vector<::fpvalue_error_t>> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::std::vector<::fpvalue_error_t>>();
}
void cxxbridge1$unique_ptr$std$vector$fpvalue_error_t$raw(::std::unique_ptr<::std::vector<::fpvalue_error_t>> *ptr, ::std::vector<::fpvalue_error_t> *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::std::vector<::fpvalue_error_t>>(raw);
}
::std::vector<::fpvalue_error_t> const *cxxbridge1$unique_ptr$std$vector$fpvalue_error_t$get(::std::unique_ptr<::std::vector<::fpvalue_error_t>> const &ptr) noexcept {
  return ptr.get();
}
::std::vector<::fpvalue_error_t> *cxxbridge1$unique_ptr$std$vector$fpvalue_error_t$release(::std::unique_ptr<::std::vector<::fpvalue_error_t>> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$std$vector$fpvalue_error_t$drop(::std::unique_ptr<::std::vector<::fpvalue_error_t>> *ptr) noexcept {
  ptr->~unique_ptr();
}

static_assert(::rust::detail::is_complete<::bitrange_t>::value, "definition of bitrange_t is required");
static_assert(sizeof(::std::unique_ptr<::bitrange_t>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::bitrange_t>) == alignof(void *), "");
void cxxbridge1$unique_ptr$bitrange_t$null(::std::unique_ptr<::bitrange_t> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::bitrange_t>();
}
::bitrange_t *cxxbridge1$unique_ptr$bitrange_t$uninit(::std::unique_ptr<::bitrange_t> *ptr) noexcept {
  ::bitrange_t *uninit = reinterpret_cast<::bitrange_t *>(new ::rust::MaybeUninit<::bitrange_t>);
  ::new (ptr) ::std::unique_ptr<::bitrange_t>(uninit);
  return uninit;
}
void cxxbridge1$unique_ptr$bitrange_t$raw(::std::unique_ptr<::bitrange_t> *ptr, ::bitrange_t *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::bitrange_t>(raw);
}
::bitrange_t const *cxxbridge1$unique_ptr$bitrange_t$get(::std::unique_ptr<::bitrange_t> const &ptr) noexcept {
  return ptr.get();
}
::bitrange_t *cxxbridge1$unique_ptr$bitrange_t$release(::std::unique_ptr<::bitrange_t> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$bitrange_t$drop(::std::unique_ptr<::bitrange_t> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::bitrange_t>::value>{}(ptr);
}

static_assert(sizeof(::std::shared_ptr<::bitrange_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::shared_ptr<::bitrange_t>) == alignof(void *), "");
void cxxbridge1$shared_ptr$bitrange_t$null(::std::shared_ptr<::bitrange_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::bitrange_t>();
}
::bitrange_t *cxxbridge1$shared_ptr$bitrange_t$uninit(::std::shared_ptr<::bitrange_t> *ptr) noexcept {
  ::bitrange_t *uninit = reinterpret_cast<::bitrange_t *>(new ::rust::MaybeUninit<::bitrange_t>);
  ::new (ptr) ::std::shared_ptr<::bitrange_t>(uninit);
  return uninit;
}
void cxxbridge1$shared_ptr$bitrange_t$clone(::std::shared_ptr<::bitrange_t> const &self, ::std::shared_ptr<::bitrange_t> *ptr) noexcept {
  ::new (ptr) ::std::shared_ptr<::bitrange_t>(self);
}
::bitrange_t const *cxxbridge1$shared_ptr$bitrange_t$get(::std::shared_ptr<::bitrange_t> const &self) noexcept {
  return self.get();
}
void cxxbridge1$shared_ptr$bitrange_t$drop(::std::shared_ptr<::bitrange_t> *self) noexcept {
  self->~shared_ptr();
}

static_assert(sizeof(::std::weak_ptr<::bitrange_t>) == 2 * sizeof(void *), "");
static_assert(alignof(::std::weak_ptr<::bitrange_t>) == alignof(void *), "");
void cxxbridge1$weak_ptr$bitrange_t$null(::std::weak_ptr<::bitrange_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::bitrange_t>();
}
void cxxbridge1$weak_ptr$bitrange_t$clone(::std::weak_ptr<::bitrange_t> const &self, ::std::weak_ptr<::bitrange_t> *ptr) noexcept {
  ::new (ptr) ::std::weak_ptr<::bitrange_t>(self);
}
void cxxbridge1$weak_ptr$bitrange_t$downgrade(::std::shared_ptr<::bitrange_t> const &shared, ::std::weak_ptr<::bitrange_t> *weak) noexcept {
  ::new (weak) ::std::weak_ptr<::bitrange_t>(shared);
}
void cxxbridge1$weak_ptr$bitrange_t$upgrade(::std::weak_ptr<::bitrange_t> const &weak, ::std::shared_ptr<::bitrange_t> *shared) noexcept {
  ::new (shared) ::std::shared_ptr<::bitrange_t>(weak.lock());
}
void cxxbridge1$weak_ptr$bitrange_t$drop(::std::weak_ptr<::bitrange_t> *self) noexcept {
  self->~weak_ptr();
}

::std::vector<::bitrange_t> *cxxbridge1$std$vector$bitrange_t$new() noexcept {
  return new ::std::vector<::bitrange_t>();
}
::std::size_t cxxbridge1$std$vector$bitrange_t$size(::std::vector<::bitrange_t> const &s) noexcept {
  return s.size();
}
::bitrange_t *cxxbridge1$std$vector$bitrange_t$get_unchecked(::std::vector<::bitrange_t> *s, ::std::size_t pos) noexcept {
  return &(*s)[pos];
}
void cxxbridge1$std$vector$bitrange_t$push_back(::std::vector<::bitrange_t> *v, ::bitrange_t *value) noexcept {
  v->push_back(::std::move(*value));
  ::rust::destroy(value);
}
void cxxbridge1$std$vector$bitrange_t$pop_back(::std::vector<::bitrange_t> *v, ::bitrange_t *out) noexcept {
  ::new (out) ::bitrange_t(::std::move(v->back()));
  v->pop_back();
}
static_assert(sizeof(::std::unique_ptr<::std::vector<::bitrange_t>>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::std::vector<::bitrange_t>>) == alignof(void *), "");
void cxxbridge1$unique_ptr$std$vector$bitrange_t$null(::std::unique_ptr<::std::vector<::bitrange_t>> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::std::vector<::bitrange_t>>();
}
void cxxbridge1$unique_ptr$std$vector$bitrange_t$raw(::std::unique_ptr<::std::vector<::bitrange_t>> *ptr, ::std::vector<::bitrange_t> *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::std::vector<::bitrange_t>>(raw);
}
::std::vector<::bitrange_t> const *cxxbridge1$unique_ptr$std$vector$bitrange_t$get(::std::unique_ptr<::std::vector<::bitrange_t>> const &ptr) noexcept {
  return ptr.get();
}
::std::vector<::bitrange_t> *cxxbridge1$unique_ptr$std$vector$bitrange_t$release(::std::unique_ptr<::std::vector<::bitrange_t>> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$std$vector$bitrange_t$drop(::std::unique_ptr<::std::vector<::bitrange_t>> *ptr) noexcept {
  ptr->~unique_ptr();
}
} // extern "C"
