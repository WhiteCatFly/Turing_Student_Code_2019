#ifndef _COWR_UTILS_UTIL

#define _COWR_UTILS_UTIL

#include <algorithm>
#include <memory>
#include <sstream>
#include <string>
#include <type_traits>
#include <typeinfo>

#ifdef __GNUC__

#include <cxxabi.h>

#endif

namespace cowr {

#define DEBUG_THROW(type, msg) ({               \
    std::stringstream ss;                       \
    ss << "At " << __FILE__ << ":" << __LINE__; \
    ss << " " << msg;                           \
    type(ss.str());                             \
})

class Object {
public:
    virtual ~Object() = default;
};

// //Copied from cppreference

// struct nonesuch {
//     nonesuch() = delete;
//     ~nonesuch() = delete;
//     nonesuch(nonesuch const&) = delete;
//     void operator=(nonesuch const&) = delete;
// };

// namespace detail {
//     template <class Default, class AlwaysVoid,
//         template <class...> class Op, class... Args>
//     struct detector {
//         using value_t = std::false_type;
//         using type = Default;
//     };

//     template <class Default, template <class...> class Op, class... Args>
//     struct detector<Default, std::void_t<Op<Args...>>, Op, Args...> {
//         // Note that std::void_t is a C++17 feature
//         using value_t = std::true_type;
//         using type = Op<Args...>;
//     };

// } // namespace detail

// template <template <class...> class Op, class... Args>
// using is_detected = typename detail::detector<nonesuch, void, Op, Args...>::value_t;

// template <template <class...> class Op, class... Args>
// using detected_t = typename detail::detector<nonesuch, void, Op, Args...>::type;

// template <class Default, template <class...> class Op, class... Args>
// using detected_or = detail::detector<Default, void, Op, Args...>;

template <typename T>
constexpr T& convertToReference(T* ptr)
{
    return reinterpret_cast<T&>(*reinterpret_cast<std::conditional_t<std::is_const_v<T>, const int*, int*>>(ptr));
}

template <typename T>
constexpr T&& convertToRvalueReference(T* ptr)
{
    return reinterpret_cast<T&&>(*reinterpret_cast<std::conditional_t<std::is_const_v<T>, const int*, int*>>(ptr));
}

template <typename T>
auto& getPointedType(T* p)
{
    auto& r = convertToReference(p);
    return typeid(r);
}

template <typename T>
std::string getClassName(T&& p)
{
    const std::type_info* pinfo;
    if constexpr (std::is_pointer_v<T>) {
        if (p == nullptr)
            pinfo = &typeid(nullptr);
        else
            pinfo = &getPointedType(reinterpret_cast<const Object*>(p));
    } else {
        pinfo = &typeid(p);
    }

    int status;
    std::string real_name; //abi::__cxa_demangle(type.name(), 0, 0, &status);

#ifdef __GNUC__
    real_name = abi::__cxa_demangle(pinfo->name(), 0, 0, &status);
#else
    real_name = type.name();
#endif
    return real_name;
}

std::string escape_string(std::string str);

// trim from start (in place)
static inline void ltrim(std::string& s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string& s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(),
        s.end());
}

// trim from both ends (in place)
static inline void trim(std::string& s)
{
    ltrim(s);
    rtrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s)
{
    ltrim(s);
    return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s)
{
    rtrim(s);
    return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s)
{
    trim(s);
    return s;
}

}

#endif
