// Generated by the protocol buffer compiler.  DO NOT EDIT!
// NO CHECKED-IN PROTOBUF GENCODE
// source: UsrHeader.proto
// Protobuf C++ Version: 5.29.3

#include "UsrHeader.pb.h"

#include <algorithm>
#include <type_traits>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/generated_message_tctable_impl.h"
#include "google/protobuf/extension_set.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/wire_format_lite.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/reflection_ops.h"
#include "google/protobuf/wire_format.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"
PROTOBUF_PRAGMA_INIT_SEG
namespace _pb = ::google::protobuf;
namespace _pbi = ::google::protobuf::internal;
namespace _fl = ::google::protobuf::internal::field_layout;

inline constexpr UsrHeader::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : offset_{::uint64_t{0u}},
        size_{::uint64_t{0u}},
        capacity_{::uint64_t{0u}},
        usr_type_{static_cast< ::UsrType >(0)},
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR UsrHeader::UsrHeader(::_pbi::ConstantInitialized)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(_class_data_.base()),
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(),
#endif  // PROTOBUF_CUSTOM_VTABLE
      _impl_(::_pbi::ConstantInitialized()) {
}
struct UsrHeaderDefaultTypeInternal {
  PROTOBUF_CONSTEXPR UsrHeaderDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~UsrHeaderDefaultTypeInternal() {}
  union {
    UsrHeader _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 UsrHeaderDefaultTypeInternal _UsrHeader_default_instance_;
              template <typename>
PROTOBUF_CONSTEXPR UsrHeaders_UsrHeadersEntry_DoNotUse::UsrHeaders_UsrHeadersEntry_DoNotUse(::_pbi::ConstantInitialized)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : UsrHeaders_UsrHeadersEntry_DoNotUse::MapEntry(_class_data_.base()){}
#else   // PROTOBUF_CUSTOM_VTABLE
    : UsrHeaders_UsrHeadersEntry_DoNotUse::MapEntry() {
}
#endif  // PROTOBUF_CUSTOM_VTABLE
struct UsrHeaders_UsrHeadersEntry_DoNotUseDefaultTypeInternal {
  PROTOBUF_CONSTEXPR UsrHeaders_UsrHeadersEntry_DoNotUseDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~UsrHeaders_UsrHeadersEntry_DoNotUseDefaultTypeInternal() {}
  union {
    UsrHeaders_UsrHeadersEntry_DoNotUse _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 UsrHeaders_UsrHeadersEntry_DoNotUseDefaultTypeInternal _UsrHeaders_UsrHeadersEntry_DoNotUse_default_instance_;

inline constexpr UsrHeaders::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : usr_headers_{},
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR UsrHeaders::UsrHeaders(::_pbi::ConstantInitialized)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(_class_data_.base()),
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(),
#endif  // PROTOBUF_CUSTOM_VTABLE
      _impl_(::_pbi::ConstantInitialized()) {
}
struct UsrHeadersDefaultTypeInternal {
  PROTOBUF_CONSTEXPR UsrHeadersDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~UsrHeadersDefaultTypeInternal() {}
  union {
    UsrHeaders _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 UsrHeadersDefaultTypeInternal _UsrHeaders_default_instance_;
static const ::_pb::EnumDescriptor* file_level_enum_descriptors_UsrHeader_2eproto[1];
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_UsrHeader_2eproto = nullptr;
const ::uint32_t
    TableStruct_UsrHeader_2eproto::offsets[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
        protodesc_cold) = {
        ~0u,  // no _has_bits_
        PROTOBUF_FIELD_OFFSET(::UsrHeader, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        PROTOBUF_FIELD_OFFSET(::UsrHeader, _impl_.offset_),
        PROTOBUF_FIELD_OFFSET(::UsrHeader, _impl_.size_),
        PROTOBUF_FIELD_OFFSET(::UsrHeader, _impl_.capacity_),
        PROTOBUF_FIELD_OFFSET(::UsrHeader, _impl_.usr_type_),
        PROTOBUF_FIELD_OFFSET(::UsrHeaders_UsrHeadersEntry_DoNotUse, _impl_._has_bits_),
        PROTOBUF_FIELD_OFFSET(::UsrHeaders_UsrHeadersEntry_DoNotUse, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        PROTOBUF_FIELD_OFFSET(::UsrHeaders_UsrHeadersEntry_DoNotUse, _impl_.key_),
        PROTOBUF_FIELD_OFFSET(::UsrHeaders_UsrHeadersEntry_DoNotUse, _impl_.value_),
        0,
        1,
        ~0u,  // no _has_bits_
        PROTOBUF_FIELD_OFFSET(::UsrHeaders, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        PROTOBUF_FIELD_OFFSET(::UsrHeaders, _impl_.usr_headers_),
};

static const ::_pbi::MigrationSchema
    schemas[] ABSL_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
        {0, -1, -1, sizeof(::UsrHeader)},
        {12, 22, -1, sizeof(::UsrHeaders_UsrHeadersEntry_DoNotUse)},
        {24, -1, -1, sizeof(::UsrHeaders)},
};
static const ::_pb::Message* const file_default_instances[] = {
    &::_UsrHeader_default_instance_._instance,
    &::_UsrHeaders_UsrHeadersEntry_DoNotUse_default_instance_._instance,
    &::_UsrHeaders_default_instance_._instance,
};
const char descriptor_table_protodef_UsrHeader_2eproto[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
    protodesc_cold) = {
    "\n\017UsrHeader.proto\"W\n\tUsrHeader\022\016\n\006offset"
    "\030\001 \001(\004\022\014\n\004size\030\002 \001(\004\022\020\n\010capacity\030\003 \001(\004\022\032"
    "\n\010usr_type\030\004 \001(\0162\010.UsrType\"}\n\nUsrHeaders"
    "\0220\n\013usr_headers\030\001 \003(\0132\033.UsrHeaders.UsrHe"
    "adersEntry\032=\n\017UsrHeadersEntry\022\013\n\003key\030\001 \001"
    "(\r\022\031\n\005value\030\002 \001(\0132\n.UsrHeader:\0028\001*O\n\007Usr"
    "Type\022\027\n\023USR_TYPE_UNSPECIFIE\020\000\022\022\n\016USR_TYP"
    "E_PROTO\020\001\022\027\n\023USR_TYPE_RAW_BUFFER\020\002b\006prot"
    "o3"
};
static ::absl::once_flag descriptor_table_UsrHeader_2eproto_once;
PROTOBUF_CONSTINIT const ::_pbi::DescriptorTable descriptor_table_UsrHeader_2eproto = {
    false,
    false,
    322,
    descriptor_table_protodef_UsrHeader_2eproto,
    "UsrHeader.proto",
    &descriptor_table_UsrHeader_2eproto_once,
    nullptr,
    0,
    3,
    schemas,
    file_default_instances,
    TableStruct_UsrHeader_2eproto::offsets,
    file_level_enum_descriptors_UsrHeader_2eproto,
    file_level_service_descriptors_UsrHeader_2eproto,
};
const ::google::protobuf::EnumDescriptor* UsrType_descriptor() {
  ::google::protobuf::internal::AssignDescriptors(&descriptor_table_UsrHeader_2eproto);
  return file_level_enum_descriptors_UsrHeader_2eproto[0];
}
PROTOBUF_CONSTINIT const uint32_t UsrType_internal_data_[] = {
    196608u, 0u, };
bool UsrType_IsValid(int value) {
  return 0 <= value && value <= 2;
}
// ===================================================================

class UsrHeader::_Internal {
 public:
};

UsrHeader::UsrHeader(::google::protobuf::Arena* arena)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(arena, _class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:UsrHeader)
}
UsrHeader::UsrHeader(
    ::google::protobuf::Arena* arena, const UsrHeader& from)
    : UsrHeader(arena) {
  MergeFrom(from);
}
inline PROTOBUF_NDEBUG_INLINE UsrHeader::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : _cached_size_{0} {}

inline void UsrHeader::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
  ::memset(reinterpret_cast<char *>(&_impl_) +
               offsetof(Impl_, offset_),
           0,
           offsetof(Impl_, usr_type_) -
               offsetof(Impl_, offset_) +
               sizeof(Impl_::usr_type_));
}
UsrHeader::~UsrHeader() {
  // @@protoc_insertion_point(destructor:UsrHeader)
  SharedDtor(*this);
}
inline void UsrHeader::SharedDtor(MessageLite& self) {
  UsrHeader& this_ = static_cast<UsrHeader&>(self);
  this_._internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  ABSL_DCHECK(this_.GetArena() == nullptr);
  this_._impl_.~Impl_();
}

inline void* UsrHeader::PlacementNew_(const void*, void* mem,
                                        ::google::protobuf::Arena* arena) {
  return ::new (mem) UsrHeader(arena);
}
constexpr auto UsrHeader::InternalNewImpl_() {
  return ::google::protobuf::internal::MessageCreator::ZeroInit(sizeof(UsrHeader),
                                            alignof(UsrHeader));
}
PROTOBUF_CONSTINIT
PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::google::protobuf::internal::ClassDataFull UsrHeader::_class_data_ = {
    ::google::protobuf::internal::ClassData{
        &_UsrHeader_default_instance_._instance,
        &_table_.header,
        nullptr,  // OnDemandRegisterArenaDtor
        nullptr,  // IsInitialized
        &UsrHeader::MergeImpl,
        ::google::protobuf::Message::GetNewImpl<UsrHeader>(),
#if defined(PROTOBUF_CUSTOM_VTABLE)
        &UsrHeader::SharedDtor,
        ::google::protobuf::Message::GetClearImpl<UsrHeader>(), &UsrHeader::ByteSizeLong,
            &UsrHeader::_InternalSerialize,
#endif  // PROTOBUF_CUSTOM_VTABLE
        PROTOBUF_FIELD_OFFSET(UsrHeader, _impl_._cached_size_),
        false,
    },
    &UsrHeader::kDescriptorMethods,
    &descriptor_table_UsrHeader_2eproto,
    nullptr,  // tracker
};
const ::google::protobuf::internal::ClassData* UsrHeader::GetClassData() const {
  ::google::protobuf::internal::PrefetchToLocalCache(&_class_data_);
  ::google::protobuf::internal::PrefetchToLocalCache(_class_data_.tc_table);
  return _class_data_.base();
}
PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<2, 4, 0, 0, 2> UsrHeader::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    4, 24,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967280,  // skipmap
    offsetof(decltype(_table_), field_entries),
    4,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    _class_data_.base(),
    nullptr,  // post_loop_handler
    ::_pbi::TcParser::GenericFallback,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::UsrHeader>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    // .UsrType usr_type = 4;
    {::_pbi::TcParser::SingularVarintNoZag1<::uint32_t, offsetof(UsrHeader, _impl_.usr_type_), 63>(),
     {32, 63, 0, PROTOBUF_FIELD_OFFSET(UsrHeader, _impl_.usr_type_)}},
    // uint64 offset = 1;
    {::_pbi::TcParser::SingularVarintNoZag1<::uint64_t, offsetof(UsrHeader, _impl_.offset_), 63>(),
     {8, 63, 0, PROTOBUF_FIELD_OFFSET(UsrHeader, _impl_.offset_)}},
    // uint64 size = 2;
    {::_pbi::TcParser::SingularVarintNoZag1<::uint64_t, offsetof(UsrHeader, _impl_.size_), 63>(),
     {16, 63, 0, PROTOBUF_FIELD_OFFSET(UsrHeader, _impl_.size_)}},
    // uint64 capacity = 3;
    {::_pbi::TcParser::SingularVarintNoZag1<::uint64_t, offsetof(UsrHeader, _impl_.capacity_), 63>(),
     {24, 63, 0, PROTOBUF_FIELD_OFFSET(UsrHeader, _impl_.capacity_)}},
  }}, {{
    65535, 65535
  }}, {{
    // uint64 offset = 1;
    {PROTOBUF_FIELD_OFFSET(UsrHeader, _impl_.offset_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUInt64)},
    // uint64 size = 2;
    {PROTOBUF_FIELD_OFFSET(UsrHeader, _impl_.size_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUInt64)},
    // uint64 capacity = 3;
    {PROTOBUF_FIELD_OFFSET(UsrHeader, _impl_.capacity_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUInt64)},
    // .UsrType usr_type = 4;
    {PROTOBUF_FIELD_OFFSET(UsrHeader, _impl_.usr_type_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kOpenEnum)},
  }},
  // no aux_entries
  {{
  }},
};

PROTOBUF_NOINLINE void UsrHeader::Clear() {
// @@protoc_insertion_point(message_clear_start:UsrHeader)
  ::google::protobuf::internal::TSanWrite(&_impl_);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&_impl_.offset_, 0, static_cast<::size_t>(
      reinterpret_cast<char*>(&_impl_.usr_type_) -
      reinterpret_cast<char*>(&_impl_.offset_)) + sizeof(_impl_.usr_type_));
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

#if defined(PROTOBUF_CUSTOM_VTABLE)
        ::uint8_t* UsrHeader::_InternalSerialize(
            const MessageLite& base, ::uint8_t* target,
            ::google::protobuf::io::EpsCopyOutputStream* stream) {
          const UsrHeader& this_ = static_cast<const UsrHeader&>(base);
#else   // PROTOBUF_CUSTOM_VTABLE
        ::uint8_t* UsrHeader::_InternalSerialize(
            ::uint8_t* target,
            ::google::protobuf::io::EpsCopyOutputStream* stream) const {
          const UsrHeader& this_ = *this;
#endif  // PROTOBUF_CUSTOM_VTABLE
          // @@protoc_insertion_point(serialize_to_array_start:UsrHeader)
          ::uint32_t cached_has_bits = 0;
          (void)cached_has_bits;

          // uint64 offset = 1;
          if (this_._internal_offset() != 0) {
            target = stream->EnsureSpace(target);
            target = ::_pbi::WireFormatLite::WriteUInt64ToArray(
                1, this_._internal_offset(), target);
          }

          // uint64 size = 2;
          if (this_._internal_size() != 0) {
            target = stream->EnsureSpace(target);
            target = ::_pbi::WireFormatLite::WriteUInt64ToArray(
                2, this_._internal_size(), target);
          }

          // uint64 capacity = 3;
          if (this_._internal_capacity() != 0) {
            target = stream->EnsureSpace(target);
            target = ::_pbi::WireFormatLite::WriteUInt64ToArray(
                3, this_._internal_capacity(), target);
          }

          // .UsrType usr_type = 4;
          if (this_._internal_usr_type() != 0) {
            target = stream->EnsureSpace(target);
            target = ::_pbi::WireFormatLite::WriteEnumToArray(
                4, this_._internal_usr_type(), target);
          }

          if (PROTOBUF_PREDICT_FALSE(this_._internal_metadata_.have_unknown_fields())) {
            target =
                ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
                    this_._internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
          }
          // @@protoc_insertion_point(serialize_to_array_end:UsrHeader)
          return target;
        }

#if defined(PROTOBUF_CUSTOM_VTABLE)
        ::size_t UsrHeader::ByteSizeLong(const MessageLite& base) {
          const UsrHeader& this_ = static_cast<const UsrHeader&>(base);
#else   // PROTOBUF_CUSTOM_VTABLE
        ::size_t UsrHeader::ByteSizeLong() const {
          const UsrHeader& this_ = *this;
#endif  // PROTOBUF_CUSTOM_VTABLE
          // @@protoc_insertion_point(message_byte_size_start:UsrHeader)
          ::size_t total_size = 0;

          ::uint32_t cached_has_bits = 0;
          // Prevent compiler warnings about cached_has_bits being unused
          (void)cached_has_bits;

          ::_pbi::Prefetch5LinesFrom7Lines(&this_);
           {
            // uint64 offset = 1;
            if (this_._internal_offset() != 0) {
              total_size += ::_pbi::WireFormatLite::UInt64SizePlusOne(
                  this_._internal_offset());
            }
            // uint64 size = 2;
            if (this_._internal_size() != 0) {
              total_size += ::_pbi::WireFormatLite::UInt64SizePlusOne(
                  this_._internal_size());
            }
            // uint64 capacity = 3;
            if (this_._internal_capacity() != 0) {
              total_size += ::_pbi::WireFormatLite::UInt64SizePlusOne(
                  this_._internal_capacity());
            }
            // .UsrType usr_type = 4;
            if (this_._internal_usr_type() != 0) {
              total_size += 1 +
                            ::_pbi::WireFormatLite::EnumSize(this_._internal_usr_type());
            }
          }
          return this_.MaybeComputeUnknownFieldsSize(total_size,
                                                     &this_._impl_._cached_size_);
        }

void UsrHeader::MergeImpl(::google::protobuf::MessageLite& to_msg, const ::google::protobuf::MessageLite& from_msg) {
  auto* const _this = static_cast<UsrHeader*>(&to_msg);
  auto& from = static_cast<const UsrHeader&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:UsrHeader)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_offset() != 0) {
    _this->_impl_.offset_ = from._impl_.offset_;
  }
  if (from._internal_size() != 0) {
    _this->_impl_.size_ = from._impl_.size_;
  }
  if (from._internal_capacity() != 0) {
    _this->_impl_.capacity_ = from._impl_.capacity_;
  }
  if (from._internal_usr_type() != 0) {
    _this->_impl_.usr_type_ = from._impl_.usr_type_;
  }
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void UsrHeader::CopyFrom(const UsrHeader& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:UsrHeader)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}


void UsrHeader::InternalSwap(UsrHeader* PROTOBUF_RESTRICT other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::google::protobuf::internal::memswap<
      PROTOBUF_FIELD_OFFSET(UsrHeader, _impl_.usr_type_)
      + sizeof(UsrHeader::_impl_.usr_type_)
      - PROTOBUF_FIELD_OFFSET(UsrHeader, _impl_.offset_)>(
          reinterpret_cast<char*>(&_impl_.offset_),
          reinterpret_cast<char*>(&other->_impl_.offset_));
}

::google::protobuf::Metadata UsrHeader::GetMetadata() const {
  return ::google::protobuf::Message::GetMetadataImpl(GetClassData()->full());
}
// ===================================================================

#if defined(PROTOBUF_CUSTOM_VTABLE)
              UsrHeaders_UsrHeadersEntry_DoNotUse::UsrHeaders_UsrHeadersEntry_DoNotUse() : SuperType(_class_data_.base()) {}
              UsrHeaders_UsrHeadersEntry_DoNotUse::UsrHeaders_UsrHeadersEntry_DoNotUse(::google::protobuf::Arena* arena)
                  : SuperType(arena, _class_data_.base()) {}
#else   // PROTOBUF_CUSTOM_VTABLE
              UsrHeaders_UsrHeadersEntry_DoNotUse::UsrHeaders_UsrHeadersEntry_DoNotUse() : SuperType() {}
              UsrHeaders_UsrHeadersEntry_DoNotUse::UsrHeaders_UsrHeadersEntry_DoNotUse(::google::protobuf::Arena* arena) : SuperType(arena) {}
#endif  // PROTOBUF_CUSTOM_VTABLE
              inline void* UsrHeaders_UsrHeadersEntry_DoNotUse::PlacementNew_(const void*, void* mem,
                                                      ::google::protobuf::Arena* arena) {
                return ::new (mem) UsrHeaders_UsrHeadersEntry_DoNotUse(arena);
              }
              constexpr auto UsrHeaders_UsrHeadersEntry_DoNotUse::InternalNewImpl_() {
                return ::google::protobuf::internal::MessageCreator::ZeroInit(sizeof(UsrHeaders_UsrHeadersEntry_DoNotUse),
                                                          alignof(UsrHeaders_UsrHeadersEntry_DoNotUse));
              }
              PROTOBUF_CONSTINIT
              PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
              const ::google::protobuf::internal::ClassDataFull UsrHeaders_UsrHeadersEntry_DoNotUse::_class_data_ = {
                  ::google::protobuf::internal::ClassData{
                      &_UsrHeaders_UsrHeadersEntry_DoNotUse_default_instance_._instance,
                      &_table_.header,
                      nullptr,  // OnDemandRegisterArenaDtor
                      nullptr,  // IsInitialized
                      &UsrHeaders_UsrHeadersEntry_DoNotUse::MergeImpl,
                      ::google::protobuf::Message::GetNewImpl<UsrHeaders_UsrHeadersEntry_DoNotUse>(),
              #if defined(PROTOBUF_CUSTOM_VTABLE)
                      &UsrHeaders_UsrHeadersEntry_DoNotUse::SharedDtor,
                      static_cast<void (::google::protobuf::MessageLite::*)()>(
                          &UsrHeaders_UsrHeadersEntry_DoNotUse::ClearImpl),
                          ::google::protobuf::Message::ByteSizeLongImpl, ::google::protobuf::Message::_InternalSerializeImpl
                          ,
              #endif  // PROTOBUF_CUSTOM_VTABLE
                      PROTOBUF_FIELD_OFFSET(UsrHeaders_UsrHeadersEntry_DoNotUse, _impl_._cached_size_),
                      false,
                  },
                  &UsrHeaders_UsrHeadersEntry_DoNotUse::kDescriptorMethods,
                  &descriptor_table_UsrHeader_2eproto,
                  nullptr,  // tracker
              };
              const ::google::protobuf::internal::ClassData* UsrHeaders_UsrHeadersEntry_DoNotUse::GetClassData() const {
                ::google::protobuf::internal::PrefetchToLocalCache(&_class_data_);
                ::google::protobuf::internal::PrefetchToLocalCache(_class_data_.tc_table);
                return _class_data_.base();
              }
PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<1, 2, 1, 0, 2> UsrHeaders_UsrHeadersEntry_DoNotUse::_table_ = {
  {
    PROTOBUF_FIELD_OFFSET(UsrHeaders_UsrHeadersEntry_DoNotUse, _impl_._has_bits_),
    0, // no _extensions_
    2, 8,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967292,  // skipmap
    offsetof(decltype(_table_), field_entries),
    2,  // num_field_entries
    1,  // num_aux_entries
    offsetof(decltype(_table_), aux_entries),
    _class_data_.base(),
    nullptr,  // post_loop_handler
    ::_pbi::TcParser::DiscardEverythingFallback,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::UsrHeaders_UsrHeadersEntry_DoNotUse>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    // .UsrHeader value = 2;
    {::_pbi::TcParser::FastMtS1,
     {18, 0, 0, PROTOBUF_FIELD_OFFSET(UsrHeaders_UsrHeadersEntry_DoNotUse, _impl_.value_)}},
    // uint32 key = 1;
    {::_pbi::TcParser::SingularVarintNoZag1<::uint32_t, offsetof(UsrHeaders_UsrHeadersEntry_DoNotUse, _impl_.key_), 63>(),
     {8, 63, 0, PROTOBUF_FIELD_OFFSET(UsrHeaders_UsrHeadersEntry_DoNotUse, _impl_.key_)}},
  }}, {{
    65535, 65535
  }}, {{
    // uint32 key = 1;
    {PROTOBUF_FIELD_OFFSET(UsrHeaders_UsrHeadersEntry_DoNotUse, _impl_.key_), -1, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUInt32)},
    // .UsrHeader value = 2;
    {PROTOBUF_FIELD_OFFSET(UsrHeaders_UsrHeadersEntry_DoNotUse, _impl_.value_), _Internal::kHasBitsOffset + 0, 0,
    (0 | ::_fl::kFcOptional | ::_fl::kMessage | ::_fl::kTvTable)},
  }}, {{
    {::_pbi::TcParser::GetTable<::UsrHeader>()},
  }}, {{
  }},
};

// ===================================================================

class UsrHeaders::_Internal {
 public:
};

UsrHeaders::UsrHeaders(::google::protobuf::Arena* arena)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(arena, _class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:UsrHeaders)
}
inline PROTOBUF_NDEBUG_INLINE UsrHeaders::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from, const ::UsrHeaders& from_msg)
      : usr_headers_{visibility, arena, from.usr_headers_},
        _cached_size_{0} {}

UsrHeaders::UsrHeaders(
    ::google::protobuf::Arena* arena,
    const UsrHeaders& from)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(arena, _class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  UsrHeaders* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_, from);

  // @@protoc_insertion_point(copy_constructor:UsrHeaders)
}
inline PROTOBUF_NDEBUG_INLINE UsrHeaders::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : usr_headers_{visibility, arena},
        _cached_size_{0} {}

inline void UsrHeaders::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
}
UsrHeaders::~UsrHeaders() {
  // @@protoc_insertion_point(destructor:UsrHeaders)
  SharedDtor(*this);
}
inline void UsrHeaders::SharedDtor(MessageLite& self) {
  UsrHeaders& this_ = static_cast<UsrHeaders&>(self);
  this_._internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  ABSL_DCHECK(this_.GetArena() == nullptr);
  this_._impl_.~Impl_();
}

inline void* UsrHeaders::PlacementNew_(const void*, void* mem,
                                        ::google::protobuf::Arena* arena) {
  return ::new (mem) UsrHeaders(arena);
}
constexpr auto UsrHeaders::InternalNewImpl_() {
  constexpr auto arena_bits = ::google::protobuf::internal::EncodePlacementArenaOffsets({
      PROTOBUF_FIELD_OFFSET(UsrHeaders, _impl_.usr_headers_) +
          decltype(UsrHeaders::_impl_.usr_headers_)::
              InternalGetArenaOffset(
                  ::google::protobuf::Message::internal_visibility()),
      PROTOBUF_FIELD_OFFSET(UsrHeaders, _impl_.usr_headers_) +
          decltype(UsrHeaders::_impl_.usr_headers_)::
              InternalGetArenaOffsetAlt(
                  ::google::protobuf::Message::internal_visibility()),
  });
  if (arena_bits.has_value()) {
    return ::google::protobuf::internal::MessageCreator::CopyInit(
        sizeof(UsrHeaders), alignof(UsrHeaders), *arena_bits);
  } else {
    return ::google::protobuf::internal::MessageCreator(&UsrHeaders::PlacementNew_,
                                 sizeof(UsrHeaders),
                                 alignof(UsrHeaders));
  }
}
PROTOBUF_CONSTINIT
PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::google::protobuf::internal::ClassDataFull UsrHeaders::_class_data_ = {
    ::google::protobuf::internal::ClassData{
        &_UsrHeaders_default_instance_._instance,
        &_table_.header,
        nullptr,  // OnDemandRegisterArenaDtor
        nullptr,  // IsInitialized
        &UsrHeaders::MergeImpl,
        ::google::protobuf::Message::GetNewImpl<UsrHeaders>(),
#if defined(PROTOBUF_CUSTOM_VTABLE)
        &UsrHeaders::SharedDtor,
        ::google::protobuf::Message::GetClearImpl<UsrHeaders>(), &UsrHeaders::ByteSizeLong,
            &UsrHeaders::_InternalSerialize,
#endif  // PROTOBUF_CUSTOM_VTABLE
        PROTOBUF_FIELD_OFFSET(UsrHeaders, _impl_._cached_size_),
        false,
    },
    &UsrHeaders::kDescriptorMethods,
    &descriptor_table_UsrHeader_2eproto,
    nullptr,  // tracker
};
const ::google::protobuf::internal::ClassData* UsrHeaders::GetClassData() const {
  ::google::protobuf::internal::PrefetchToLocalCache(&_class_data_);
  ::google::protobuf::internal::PrefetchToLocalCache(_class_data_.tc_table);
  return _class_data_.base();
}
PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<0, 1, 2, 0, 2> UsrHeaders::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    1, 0,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967294,  // skipmap
    offsetof(decltype(_table_), field_entries),
    1,  // num_field_entries
    2,  // num_aux_entries
    offsetof(decltype(_table_), aux_entries),
    _class_data_.base(),
    nullptr,  // post_loop_handler
    ::_pbi::TcParser::GenericFallback,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::UsrHeaders>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    {::_pbi::TcParser::MiniParse, {}},
  }}, {{
    65535, 65535
  }}, {{
    // map<uint32, .UsrHeader> usr_headers = 1;
    {PROTOBUF_FIELD_OFFSET(UsrHeaders, _impl_.usr_headers_), 0, 0,
    (0 | ::_fl::kFcRepeated | ::_fl::kMap)},
  }}, {{
    {::_pbi::TcParser::GetMapAuxInfo<
        decltype(UsrHeaders()._impl_.usr_headers_)>(
        0, 0, 0, 13,
        11)},
    {::_pbi::TcParser::GetTable<::UsrHeader>()},
  }}, {{
  }},
};

PROTOBUF_NOINLINE void UsrHeaders::Clear() {
// @@protoc_insertion_point(message_clear_start:UsrHeaders)
  ::google::protobuf::internal::TSanWrite(&_impl_);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.usr_headers_.Clear();
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

#if defined(PROTOBUF_CUSTOM_VTABLE)
        ::uint8_t* UsrHeaders::_InternalSerialize(
            const MessageLite& base, ::uint8_t* target,
            ::google::protobuf::io::EpsCopyOutputStream* stream) {
          const UsrHeaders& this_ = static_cast<const UsrHeaders&>(base);
#else   // PROTOBUF_CUSTOM_VTABLE
        ::uint8_t* UsrHeaders::_InternalSerialize(
            ::uint8_t* target,
            ::google::protobuf::io::EpsCopyOutputStream* stream) const {
          const UsrHeaders& this_ = *this;
#endif  // PROTOBUF_CUSTOM_VTABLE
          // @@protoc_insertion_point(serialize_to_array_start:UsrHeaders)
          ::uint32_t cached_has_bits = 0;
          (void)cached_has_bits;

          // map<uint32, .UsrHeader> usr_headers = 1;
          if (!this_._internal_usr_headers().empty()) {
            using MapType = ::google::protobuf::Map<::uint32_t, ::UsrHeader>;
            using WireHelper = _pbi::MapEntryFuncs<::uint32_t, ::UsrHeader,
                                           _pbi::WireFormatLite::TYPE_UINT32,
                                           _pbi::WireFormatLite::TYPE_MESSAGE>;
            const auto& field = this_._internal_usr_headers();

            if (stream->IsSerializationDeterministic() && field.size() > 1) {
              for (const auto& entry : ::google::protobuf::internal::MapSorterFlat<MapType>(field)) {
                target = WireHelper::InternalSerialize(
                    1, entry.first, entry.second, target, stream);
              }
            } else {
              for (const auto& entry : field) {
                target = WireHelper::InternalSerialize(
                    1, entry.first, entry.second, target, stream);
              }
            }
          }

          if (PROTOBUF_PREDICT_FALSE(this_._internal_metadata_.have_unknown_fields())) {
            target =
                ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
                    this_._internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
          }
          // @@protoc_insertion_point(serialize_to_array_end:UsrHeaders)
          return target;
        }

#if defined(PROTOBUF_CUSTOM_VTABLE)
        ::size_t UsrHeaders::ByteSizeLong(const MessageLite& base) {
          const UsrHeaders& this_ = static_cast<const UsrHeaders&>(base);
#else   // PROTOBUF_CUSTOM_VTABLE
        ::size_t UsrHeaders::ByteSizeLong() const {
          const UsrHeaders& this_ = *this;
#endif  // PROTOBUF_CUSTOM_VTABLE
          // @@protoc_insertion_point(message_byte_size_start:UsrHeaders)
          ::size_t total_size = 0;

          ::uint32_t cached_has_bits = 0;
          // Prevent compiler warnings about cached_has_bits being unused
          (void)cached_has_bits;

          ::_pbi::Prefetch5LinesFrom7Lines(&this_);
           {
            // map<uint32, .UsrHeader> usr_headers = 1;
            {
              total_size +=
                  1 * ::google::protobuf::internal::FromIntSize(this_._internal_usr_headers_size());
              for (const auto& entry : this_._internal_usr_headers()) {
                total_size += _pbi::MapEntryFuncs<::uint32_t, ::UsrHeader,
                                               _pbi::WireFormatLite::TYPE_UINT32,
                                               _pbi::WireFormatLite::TYPE_MESSAGE>::ByteSizeLong(entry.first, entry.second);
              }
            }
          }
          return this_.MaybeComputeUnknownFieldsSize(total_size,
                                                     &this_._impl_._cached_size_);
        }

void UsrHeaders::MergeImpl(::google::protobuf::MessageLite& to_msg, const ::google::protobuf::MessageLite& from_msg) {
  auto* const _this = static_cast<UsrHeaders*>(&to_msg);
  auto& from = static_cast<const UsrHeaders&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:UsrHeaders)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_impl_.usr_headers_.MergeFrom(from._impl_.usr_headers_);
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void UsrHeaders::CopyFrom(const UsrHeaders& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:UsrHeaders)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}


void UsrHeaders::InternalSwap(UsrHeaders* PROTOBUF_RESTRICT other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  _impl_.usr_headers_.InternalSwap(&other->_impl_.usr_headers_);
}

::google::protobuf::Metadata UsrHeaders::GetMetadata() const {
  return ::google::protobuf::Message::GetMetadataImpl(GetClassData()->full());
}
// @@protoc_insertion_point(namespace_scope)
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google
// @@protoc_insertion_point(global_scope)
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::std::false_type
    _static_init2_ PROTOBUF_UNUSED =
        (::_pbi::AddDescriptors(&descriptor_table_UsrHeader_2eproto),
         ::std::false_type{});
#include "google/protobuf/port_undef.inc"
