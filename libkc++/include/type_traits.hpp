#ifndef LIBKCXX_VECTOR_HPP
#define LIBKCXX_VECTOR_HPP

namespace kstd
{

template <typename T>
struct type_traits
{
    constexpr static const char* type_name = "??"; // TODO: maybe improve type name serialization
};

#define TYPE_NAME(type) \
    template <> \
    struct type_traits <type> \
    { \
        constexpr static const char* type_name = #type; \
    }

TYPE_NAME(char);
TYPE_NAME(short);
TYPE_NAME(int);
TYPE_NAME(long);
TYPE_NAME(long long);
TYPE_NAME(unsigned char);
TYPE_NAME(unsigned short);
TYPE_NAME(unsigned int);
TYPE_NAME(unsigned long);
TYPE_NAME(unsigned long long);
TYPE_NAME(float);
TYPE_NAME(double);
TYPE_NAME(long double);
TYPE_NAME(nullptr_t);
TYPE_NAME(wchar_t);
TYPE_NAME(bool);

#undef TYPE_NAME

}

#endif // end of include guard: LIBKCXX_VECTOR_HPP

