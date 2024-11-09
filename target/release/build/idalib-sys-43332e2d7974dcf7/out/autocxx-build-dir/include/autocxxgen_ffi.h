#ifndef __AUTOCXXGEN_H__
#define __AUTOCXXGEN_H__

#include <memory>
#include <string>
#include "cxx.h"
#include <stddef.h>
#ifndef AUTOCXX_NEW_AND_DELETE_PRELUDE
#define AUTOCXX_NEW_AND_DELETE_PRELUDE
// Mechanics to call custom operator new and delete
template <typename T>
auto delete_imp(T *ptr, int) -> decltype((void)T::operator delete(ptr)) {
  T::operator delete(ptr);
}
template <typename T> void delete_imp(T *ptr, long) { ::operator delete(ptr); }
template <typename T> void delete_appropriately(T *obj) {
  // 0 is a better match for the first 'delete_imp' so will match
  // preferentially.
  delete_imp(obj, 0);
}
template <typename T>
auto new_imp(size_t count, int) -> decltype(T::operator new(count)) {
  return T::operator new(count);
}
template <typename T> void *new_imp(size_t count, long) {
  return ::operator new(count);
}
template <typename T> T *new_appropriately() {
  // 0 is a better match for the first 'delete_imp' so will match
  // preferentially.
  return static_cast<T *>(new_imp<T>(sizeof(T), 0));
}
#endif // AUTOCXX_NEW_AND_DELETE_PRELUDE
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

typedef _qstring<char> qstring_char_AutocxxConcrete;
typedef unsigned long long c_ulonglong;
typedef int c_int;
typedef unsigned int c_uint;
typedef void c_void;
typedef unsigned short c_ushort;

inline std::unique_ptr<std::string> autocxx_make_string_0x8d0b21477d8c77db(::rust::Str str) { return std::make_unique<std::string>(std::string(str)); }
inline range_t* range_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db()  { return new_appropriately<range_t>();; }
inline void range_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(range_t* arg0)  { delete_appropriately<range_t>(arg0);; }
static_assert(::rust::IsRelocatable<range_t>::value, "type range_t should be trivially move constructible and trivially destructible to be used with generate_pod! in autocxx");
inline const range_t& cast_func_t_to_range_t_autocxx_wrapper_0x8d0b21477d8c77db(const func_t& arg0)  { return arg0; }
inline func_t* func_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db()  { return new_appropriately<func_t>();; }
inline void func_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(func_t* arg0)  { delete_appropriately<func_t>(arg0);; }
inline lock_func* lock_func_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db()  { return new_appropriately<lock_func>();; }
inline void lock_func_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(lock_func* arg0)  { delete_appropriately<lock_func>(arg0);; }
inline gdl_graph_t* gdl_graph_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db()  { return new_appropriately<gdl_graph_t>();; }
inline void gdl_graph_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(gdl_graph_t* arg0)  { delete_appropriately<gdl_graph_t>(arg0);; }
inline const range_t& cast_qbasic_block_t_to_range_t_autocxx_wrapper_0x8d0b21477d8c77db(const qbasic_block_t& arg0)  { return arg0; }
inline qbasic_block_t* qbasic_block_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db()  { return new_appropriately<qbasic_block_t>();; }
inline void qbasic_block_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(qbasic_block_t* arg0)  { delete_appropriately<qbasic_block_t>(arg0);; }
inline qflow_chart_t* qflow_chart_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db()  { return new_appropriately<qflow_chart_t>();; }
inline void qflow_chart_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(qflow_chart_t* arg0)  { delete_appropriately<qflow_chart_t>(arg0);; }
inline const range_t& cast_segment_t_to_range_t_autocxx_wrapper_0x8d0b21477d8c77db(const segment_t& arg0)  { return arg0; }
inline segment_t* segment_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db()  { return new_appropriately<segment_t>();; }
inline void segment_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(segment_t* arg0)  { delete_appropriately<segment_t>(arg0);; }
inline lock_segment* lock_segment_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db()  { return new_appropriately<lock_segment>();; }
inline void lock_segment_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(lock_segment* arg0)  { delete_appropriately<lock_segment>(arg0);; }
inline xrefblk_t* xrefblk_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db()  { return new_appropriately<xrefblk_t>();; }
inline void xrefblk_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(xrefblk_t* arg0)  { delete_appropriately<xrefblk_t>(arg0);; }
static_assert(::rust::IsRelocatable<xrefblk_t>::value, "type xrefblk_t should be trivially move constructible and trivially destructible to be used with generate_pod! in autocxx");
inline processor_t* processor_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db()  { return new_appropriately<processor_t>();; }
inline void processor_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(processor_t* arg0)  { delete_appropriately<processor_t>(arg0);; }
inline plugin_t* plugin_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db()  { return new_appropriately<plugin_t>();; }
inline void plugin_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(plugin_t* arg0)  { delete_appropriately<plugin_t>(arg0);; }
inline void range_t_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db(range_t* autocxx_gen_this, unsigned long long arg1, unsigned long long arg2)  { new (autocxx_gen_this) range_t(arg1, arg2); }
inline int func_t_compare_autocxx_wrapper_0x8d0b21477d8c77db(const func_t& autocxx_gen_this, const func_t& arg1)  { return autocxx_gen_this.compare(arg1); }
inline void func_t_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db(func_t* autocxx_gen_this, unsigned long long arg1, unsigned long long arg2, unsigned long long arg3)  { new (autocxx_gen_this) func_t(arg1, arg2, arg3); }
inline void lock_func_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db(lock_func* autocxx_gen_this, const func_t* arg1)  { new (autocxx_gen_this) lock_func(arg1); }
inline void lock_func_destructor_autocxx_wrapper_0x8d0b21477d8c77db(lock_func* arg0)  { arg0->lock_func::~lock_func(); }
inline void begin_autocxx_wrapper_0x8d0b21477d8c77db(const gdl_graph_t& autocxx_gen_this, node_iterator* arg1)  { new(arg1) node_iterator(autocxx_gen_this.begin()); }
inline void gdl_graph_t_end_autocxx_wrapper_0x8d0b21477d8c77db(const gdl_graph_t& autocxx_gen_this, node_iterator* arg1)  { new(arg1) node_iterator(autocxx_gen_this.end()); }
inline void gdl_graph_t_destructor_autocxx_wrapper_0x8d0b21477d8c77db(gdl_graph_t* arg0)  { arg0->gdl_graph_t::~gdl_graph_t(); }
inline char* get_node_label_autocxx_wrapper_0x8d0b21477d8c77db(const gdl_graph_t& autocxx_gen_this, char* arg1, int arg2, int arg3)  { return autocxx_gen_this.get_node_label(arg1, arg2, arg3); }
inline void print_graph_attributes_autocxx_wrapper_0x8d0b21477d8c77db(const gdl_graph_t& autocxx_gen_this, _IO_FILE* arg1)  { autocxx_gen_this.print_graph_attributes(arg1); }
inline bool print_node_autocxx_wrapper_0x8d0b21477d8c77db(const gdl_graph_t& autocxx_gen_this, _IO_FILE* arg1, int arg2)  { return autocxx_gen_this.print_node(arg1, arg2); }
inline bool print_edge_autocxx_wrapper_0x8d0b21477d8c77db(const gdl_graph_t& autocxx_gen_this, _IO_FILE* arg1, int arg2, int arg3)  { return autocxx_gen_this.print_edge(arg1, arg2, arg3); }
inline void print_node_attributes_autocxx_wrapper_0x8d0b21477d8c77db(const gdl_graph_t& autocxx_gen_this, _IO_FILE* arg1, int arg2)  { autocxx_gen_this.print_node_attributes(arg1, arg2); }
inline int gdl_graph_t_size_autocxx_wrapper_0x8d0b21477d8c77db(const gdl_graph_t& autocxx_gen_this)  { return autocxx_gen_this.size(); }
inline int node_qty_autocxx_wrapper_0x8d0b21477d8c77db(const gdl_graph_t& autocxx_gen_this)  { return autocxx_gen_this.node_qty(); }
inline bool exists_autocxx_wrapper_0x8d0b21477d8c77db(const gdl_graph_t& autocxx_gen_this, int arg1)  { return autocxx_gen_this.exists(arg1); }
inline int entry_autocxx_wrapper_0x8d0b21477d8c77db(const gdl_graph_t& autocxx_gen_this)  { return autocxx_gen_this.entry(); }
inline int exit_autocxx_wrapper_0x8d0b21477d8c77db(const gdl_graph_t& autocxx_gen_this)  { return autocxx_gen_this.exit(); }
inline int nsucc_autocxx_wrapper_0x8d0b21477d8c77db(const gdl_graph_t& autocxx_gen_this, int arg1)  { return autocxx_gen_this.nsucc(arg1); }
inline int npred_autocxx_wrapper_0x8d0b21477d8c77db(const gdl_graph_t& autocxx_gen_this, int arg1)  { return autocxx_gen_this.npred(arg1); }
inline int succ_autocxx_wrapper_0x8d0b21477d8c77db(const gdl_graph_t& autocxx_gen_this, int arg1, int arg2)  { return autocxx_gen_this.succ(arg1, arg2); }
inline int pred_autocxx_wrapper_0x8d0b21477d8c77db(const gdl_graph_t& autocxx_gen_this, int arg1, int arg2)  { return autocxx_gen_this.pred(arg1, arg2); }
inline bool gdl_graph_t_empty_autocxx_wrapper_0x8d0b21477d8c77db(const gdl_graph_t& autocxx_gen_this)  { return autocxx_gen_this.empty(); }
inline unsigned int get_node_color_autocxx_wrapper_0x8d0b21477d8c77db(const gdl_graph_t& autocxx_gen_this, int arg1)  { return autocxx_gen_this.get_node_color(arg1); }
inline unsigned int get_edge_color_autocxx_wrapper_0x8d0b21477d8c77db(const gdl_graph_t& autocxx_gen_this, int arg1, int arg2)  { return autocxx_gen_this.get_edge_color(arg1, arg2); }
inline void qflow_chart_t_create_autocxx_wrapper_0x8d0b21477d8c77db(qflow_chart_t& autocxx_gen_this, const char* arg1, func_t* arg2, unsigned long long arg3, unsigned long long arg4, int arg5)  { autocxx_gen_this.create(arg1, arg2, arg3, arg4, arg5); }
inline void qflow_chart_t_create1_autocxx_wrapper_0x8d0b21477d8c77db(qflow_chart_t& autocxx_gen_this, const char* arg1, const rangevec_t& arg2, int arg3)  { autocxx_gen_this.create(arg1, arg2, arg3); }
inline void qflow_chart_t_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db(qflow_chart_t* autocxx_gen_this)  { new (autocxx_gen_this) qflow_chart_t(); }
inline void qflow_chart_t_new1_autocxx_wrapper_0x8d0b21477d8c77db(qflow_chart_t* autocxx_gen_this, const char* arg1, func_t* arg2, unsigned long long arg3, unsigned long long arg4, int arg5)  { new (autocxx_gen_this) qflow_chart_t(arg1, arg2, arg3, arg4, arg5); }
inline void qflow_chart_t_destructor_autocxx_wrapper_0x8d0b21477d8c77db(qflow_chart_t* arg0)  { arg0->qflow_chart_t::~qflow_chart_t(); }
inline void qflow_chart_t_print_node_attributes_autocxx_wrapper_0x8d0b21477d8c77db(const qflow_chart_t& autocxx_gen_this, _IO_FILE* arg1, int arg2)  { autocxx_gen_this.print_node_attributes(arg1, arg2); }
inline int qflow_chart_t_nsucc_autocxx_wrapper_0x8d0b21477d8c77db(const qflow_chart_t& autocxx_gen_this, int arg1)  { return autocxx_gen_this.nsucc(arg1); }
inline int qflow_chart_t_npred_autocxx_wrapper_0x8d0b21477d8c77db(const qflow_chart_t& autocxx_gen_this, int arg1)  { return autocxx_gen_this.npred(arg1); }
inline int qflow_chart_t_succ_autocxx_wrapper_0x8d0b21477d8c77db(const qflow_chart_t& autocxx_gen_this, int arg1, int arg2)  { return autocxx_gen_this.succ(arg1, arg2); }
inline int qflow_chart_t_pred_autocxx_wrapper_0x8d0b21477d8c77db(const qflow_chart_t& autocxx_gen_this, int arg1, int arg2)  { return autocxx_gen_this.pred(arg1, arg2); }
inline char* qflow_chart_t_get_node_label_autocxx_wrapper_0x8d0b21477d8c77db(const qflow_chart_t& autocxx_gen_this, char* arg1, int arg2, int arg3)  { return autocxx_gen_this.get_node_label(arg1, arg2, arg3); }
inline int qflow_chart_t_size_autocxx_wrapper_0x8d0b21477d8c77db(const qflow_chart_t& autocxx_gen_this)  { return autocxx_gen_this.size(); }
inline int segment_t_compare_autocxx_wrapper_0x8d0b21477d8c77db(const segment_t& autocxx_gen_this, const segment_t& arg1)  { return autocxx_gen_this.compare(arg1); }
inline void segment_t_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db(segment_t* autocxx_gen_this)  { new (autocxx_gen_this) segment_t(); }
inline void lock_segment_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db(lock_segment* autocxx_gen_this, const segment_t* arg1)  { new (autocxx_gen_this) lock_segment(arg1); }
inline void lock_segment_destructor_autocxx_wrapper_0x8d0b21477d8c77db(lock_segment* arg0)  { arg0->lock_segment::~lock_segment(); }
inline void auto_queue_empty_autocxx_wrapper_0x8d0b21477d8c77db(int arg0)  { processor_t::auto_queue_empty(arg0); }
inline const char* set_idp_options_autocxx_wrapper_0x8d0b21477d8c77db(const char* arg0, int arg1, const void* arg2, bool arg3)  { return processor_t::set_idp_options(arg0, arg1, arg2, arg3); }
inline fpvalue_error_t realcvt_autocxx_wrapper_0x8d0b21477d8c77db(void* arg0, fpvalue_t* arg1, unsigned short arg2)  { return processor_t::realcvt(arg0, arg1, arg2); }
inline bool get_code16_mode_autocxx_wrapper_0x8d0b21477d8c77db(unsigned long long arg0)  { return processor_t::get_code16_mode(arg0); }
inline const char* get_reg_info_autocxx_wrapper_0x8d0b21477d8c77db(const char* arg0, bitrange_t* arg1)  { return processor_t::get_reg_info(arg0, arg1); }
inline reg_finder_t* get_regfinder_autocxx_wrapper_0x8d0b21477d8c77db()  { return processor_t::get_regfinder(); }
inline bool processor_t_is_canon_insn_autocxx_wrapper_0x8d0b21477d8c77db(const processor_t& autocxx_gen_this, unsigned short arg1)  { return autocxx_gen_this.is_canon_insn(arg1); }
inline const char* processor_t_get_canon_mnem_autocxx_wrapper_0x8d0b21477d8c77db(const processor_t& autocxx_gen_this, unsigned short arg1)  { return autocxx_gen_this.get_canon_mnem(arg1); }
inline unsigned int processor_t_get_canon_feature_autocxx_wrapper_0x8d0b21477d8c77db(const processor_t& autocxx_gen_this, unsigned short arg1)  { return autocxx_gen_this.get_canon_feature(arg1); }
inline void range_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(range_t* autocxx_gen_this, range_t* arg1)  { new (autocxx_gen_this) range_t(std::move(*arg1)); }
inline void range_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(range_t* autocxx_gen_this, const range_t& arg1)  { new (autocxx_gen_this) range_t(arg1); }
inline void range_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(range_t* arg0)  { arg0->range_t::~range_t(); }
inline void func_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(func_t* autocxx_gen_this, func_t* arg1)  { new (autocxx_gen_this) func_t(std::move(*arg1)); }
inline void func_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(func_t* autocxx_gen_this, const func_t& arg1)  { new (autocxx_gen_this) func_t(arg1); }
inline void func_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(func_t* arg0)  { arg0->func_t::~func_t(); }
inline void lock_func_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(lock_func* autocxx_gen_this, const lock_func& arg1)  { new (autocxx_gen_this) lock_func(arg1); }
inline void segment_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(segment_t* autocxx_gen_this, segment_t* arg1)  { new (autocxx_gen_this) segment_t(std::move(*arg1)); }
inline void segment_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(segment_t* autocxx_gen_this, const segment_t& arg1)  { new (autocxx_gen_this) segment_t(arg1); }
inline void segment_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(segment_t* arg0)  { arg0->segment_t::~segment_t(); }
inline void lock_segment_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(lock_segment* autocxx_gen_this, const lock_segment& arg1)  { new (autocxx_gen_this) lock_segment(arg1); }
inline void xrefblk_t_new_autocxx_autocxx_wrapper_0x8d0b21477d8c77db(xrefblk_t* autocxx_gen_this)  { new (autocxx_gen_this) xrefblk_t(); }
inline void xrefblk_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(xrefblk_t* autocxx_gen_this, xrefblk_t* arg1)  { new (autocxx_gen_this) xrefblk_t(std::move(*arg1)); }
inline void xrefblk_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(xrefblk_t* autocxx_gen_this, const xrefblk_t& arg1)  { new (autocxx_gen_this) xrefblk_t(arg1); }
inline void xrefblk_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(xrefblk_t* arg0)  { arg0->xrefblk_t::~xrefblk_t(); }
inline void processor_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(processor_t* arg0)  { arg0->processor_t::~processor_t(); }
inline void plugin_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(plugin_t* autocxx_gen_this, plugin_t* arg1)  { new (autocxx_gen_this) plugin_t(std::move(*arg1)); }
inline void plugin_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(plugin_t* autocxx_gen_this, const plugin_t& arg1)  { new (autocxx_gen_this) plugin_t(arg1); }
inline void plugin_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(plugin_t* arg0)  { arg0->plugin_t::~plugin_t(); }
inline void qbasic_block_t_synthetic_destructor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(qbasic_block_t* arg0)  { arg0->qbasic_block_t::~qbasic_block_t(); }
inline _IO_FILE* _IO_FILE_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db()  { return new_appropriately<_IO_FILE>();; }
inline void _IO_FILE_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(_IO_FILE* arg0)  { delete_appropriately<_IO_FILE>(arg0);; }
inline void _IO_FILE_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(_IO_FILE* autocxx_gen_this, _IO_FILE* arg1)  { new (autocxx_gen_this) _IO_FILE(std::move(*arg1)); }
inline void _IO_FILE_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(_IO_FILE* autocxx_gen_this, const _IO_FILE& arg1)  { new (autocxx_gen_this) _IO_FILE(arg1); }
inline node_iterator* node_iterator_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db()  { return new_appropriately<node_iterator>();; }
inline void node_iterator_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(node_iterator* arg0)  { delete_appropriately<node_iterator>(arg0);; }
inline void node_iterator_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(node_iterator* autocxx_gen_this, node_iterator* arg1)  { new (autocxx_gen_this) node_iterator(std::move(*arg1)); }
inline void node_iterator_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(node_iterator* autocxx_gen_this, const node_iterator& arg1)  { new (autocxx_gen_this) node_iterator(arg1); }
inline rangevec_t* rangevec_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db()  { return new_appropriately<rangevec_t>();; }
inline void rangevec_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(rangevec_t* arg0)  { delete_appropriately<rangevec_t>(arg0);; }
inline fpvalue_t* fpvalue_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db()  { return new_appropriately<fpvalue_t>();; }
inline void fpvalue_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(fpvalue_t* arg0)  { delete_appropriately<fpvalue_t>(arg0);; }
inline void fpvalue_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(fpvalue_t* autocxx_gen_this, fpvalue_t* arg1)  { new (autocxx_gen_this) fpvalue_t(std::move(*arg1)); }
inline void fpvalue_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(fpvalue_t* autocxx_gen_this, const fpvalue_t& arg1)  { new (autocxx_gen_this) fpvalue_t(arg1); }
inline bitrange_t* bitrange_t_autocxx_alloc_autocxx_wrapper_0x8d0b21477d8c77db()  { return new_appropriately<bitrange_t>();; }
inline void bitrange_t_autocxx_free_autocxx_wrapper_0x8d0b21477d8c77db(bitrange_t* arg0)  { delete_appropriately<bitrange_t>(arg0);; }
inline void bitrange_t_new_synthetic_move_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(bitrange_t* autocxx_gen_this, bitrange_t* arg1)  { new (autocxx_gen_this) bitrange_t(std::move(*arg1)); }
inline void bitrange_t_new_synthetic_const_copy_ctor_0x8d0b21477d8c77db_autocxx_wrapper_0x8d0b21477d8c77db(bitrange_t* autocxx_gen_this, const bitrange_t& arg1)  { new (autocxx_gen_this) bitrange_t(arg1); }
#endif // __AUTOCXXGEN_H__
