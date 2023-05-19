#ifndef REF_H
#define REF_H

#include <memory>

namespace SignE {
    // Borrew from Hazel
    //https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Hazel/Core/Base.h
	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Unique = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Unique<T> CreateUnique(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
}

#endif // !#ifndef REF_H
