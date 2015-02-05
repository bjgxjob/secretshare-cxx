#ifndef INC_GUARD_GBJSJ1K0UDF9JNQQUKHXNVXY4DOUJH
#define INC_GUARD_GBJSJ1K0UDF9JNQQUKHXNVXY4DOUJH

#include <cassert>
#include <cstddef>
#include <stdexcept>
#include <type_traits>

#define REQUIRES_VALID_ARRAY_PTR_CONVERSION(X, Y) \
	,class = typename std::enable_if< \
		std::is_convertible<X*, Y*>::value && \
		(sizeof(X) == sizeof(Y)) \
	>::type

template<class T>
class slice
{
public:
	template<class U REQUIRES_VALID_ARRAY_PTR_CONVERSION(U, T)>
	explicit slice(U* base, std::size_t len) : base(base), len(len) {}

	template<class U, std::size_t N REQUIRES_VALID_ARRAY_PTR_CONVERSION(U, T)>
	slice(U (&arr)[N]) : base(arr), len(N) {}

	template<class U REQUIRES_VALID_ARRAY_PTR_CONVERSION(U, T)>
	slice(slice<U> x) : base(x.base), len(x.len) {}

	std::size_t size() const { return len; }
	bool empty() const { return len==0; }
	explicit operator bool() const { return len!=0; }
	T* begin() const { return base; }
	T* end() const { return base + len; }

	T& operator[](std::size_t index) const
	{
		assert(index < len);
		return base[index];
	}

	T& shift()
	{
		if (empty()) throw std::logic_error("slice already empty");
		auto old = base;
		++base;
		--len;
		return *old;
	}

	T& pop()
	{
		if (empty()) throw std::logic_error("slice already empty");
		--len;
		return base[len];
	}

private:
	T* base;
	std::size_t len;
};

#undef REQUIRES_VALID_ARRAY_PTR_CONVERSION

#endif /* include guard */

