#ifndef INC_METTLE_OUTPUT_STRING_HPP
#define INC_METTLE_OUTPUT_STRING_HPP

// Try to use N4480's string_view class, or fall back to Boost's.
#if defined(METTLE_USE_STDLIB_EXTS)
#  include <boost/utility/string_ref.hpp>
#  define METTLE_STRING_VIEW boost::basic_string_ref
#elif !defined(METTLE_NO_STDLIB_EXTS) && defined(__has_include)
#  if __has_include(<experimental/string_view>)
#    include <experimental/string_view>
#    define METTLE_STRING_VIEW std::experimental::basic_string_view
#  else
#    include <boost/utility/string_ref.hpp>
#    define METTLE_STRING_VIEW boost::basic_string_ref
#  endif
#else
#  include <boost/utility/string_ref.hpp>
#  define METTLE_STRING_VIEW boost::basic_string_ref
#endif

#include <codecvt>
#include <ostream>
#include <string>

namespace mettle {

namespace detail {
  template<typename Char, typename Traits>
  void escape_char(std::basic_ostream<Char, Traits> &os, Char c, Char delim) {
    const char escape = '\\';
    if(c < 32 || c == 0x7f) {
      os << escape;
      switch(c) {
      case '\0': os << os.widen('0'); break;
      case '\a': os << os.widen('a'); break;
      case '\b': os << os.widen('b'); break;
      case '\f': os << os.widen('f'); break;
      case '\n': os << os.widen('n'); break;
      case '\r': os << os.widen('r'); break;
      case '\t': os << os.widen('t'); break;
      case '\v': os << os.widen('v'); break;
      default:   os << os.widen('x') << static_cast<unsigned long>(c);
      }
    }
    else if(c == delim || c == escape) {
      os << escape << c;
    }
    else {
      os << c;
    }
  }

  template<typename Char = char, typename Traits = std::char_traits<Char>,
           typename Alloc = std::allocator<Char>>
  std::basic_string<Char, Traits, Alloc>
  null_str() {
    std::basic_ostringstream<Char, Traits, Alloc> ss;
    ss << static_cast<const void *>(nullptr);
    return ss.str();
  }
}

template<typename Char, typename Traits, typename Alloc = std::allocator<Char>>
std::basic_string<Char, Traits, Alloc>
escape_string(const METTLE_STRING_VIEW<Char, Traits> &s, Char delim = '"') {
  std::basic_ostringstream<Char, Traits, Alloc> ss;
  ss << std::hex << delim;
  for(const auto &c : s)
    detail::escape_char(ss, c, delim);
  ss << delim;
  return ss.str();
}

template<typename Char, typename Traits, typename Alloc>
std::basic_string<Char, Traits>
escape_string(const std::basic_string<Char, Traits, Alloc> &s,
              Char delim = '"') {
  return escape_string<Char, Traits, Alloc>(
    METTLE_STRING_VIEW<Char, Traits>(s), delim
  );
}

template<typename Char, typename Traits = std::char_traits<Char>,
         typename Alloc = std::allocator<Char>>
std::basic_string<Char, Traits, Alloc>
escape_string(const Char *s, Char delim = '"') {
  return escape_string<Char, Traits, Alloc>(METTLE_STRING_VIEW<Char>(s), delim);
}

inline METTLE_STRING_VIEW<char>
string_convert(const METTLE_STRING_VIEW<char> &s) {
  return s;
}

inline std::string
string_convert(const METTLE_STRING_VIEW<wchar_t> &s) {
  std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> conv;
  return conv.to_bytes(s.data(), s.data() + s.size());
}

inline std::string
string_convert(const METTLE_STRING_VIEW<char16_t> &s) {
#if defined(_MSC_VER) && !defined(__clang__)
  // MSVC 2015's codecvt expects uint16_t instead of char16_t because char16_t
  // used to just be a typedef of uint16_t.
  std::wstring_convert<std::codecvt_utf8_utf16<std::uint16_t>,
                       std::uint16_t> conv;
  return conv.to_bytes(
    reinterpret_cast<const std::uint16_t *>(s.data()),
    reinterpret_cast<const std::uint16_t *>(s.data() + s.size())
  );
#else
  std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> conv;
  return conv.to_bytes(s.data(), s.data() + s.size());
#endif
}

inline std::string
string_convert(const METTLE_STRING_VIEW<char32_t> &s) {
#if defined(_MSC_VER) && !defined(__clang__)
  // MSVC 2015's codecvt expects uint32_t instead of char32_t because char32_t
  // used to just be a typedef of uint32_t.
  std::wstring_convert<std::codecvt_utf8<std::uint32_t>, std::uint32_t> conv;
  return conv.to_bytes(
    reinterpret_cast<const std::uint32_t *>(s.data()),
    reinterpret_cast<const std::uint32_t *>(s.data() + s.size())
  );
#else
  std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
  return conv.to_bytes(s.data(), s.data() + s.size());
#endif
}

} // namespace mettle

#endif
