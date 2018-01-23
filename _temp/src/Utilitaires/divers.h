#ifndef DIVERS_H
#define DIVERS_H
#include <type_traits>

template<typename T,typename U>
bool est(const T& X)
{
	if (!std::is_base_of<U, T>())
		return false;
	return (dynamic_cast<U*>(&X) != nullptr);
}

#endif // !DIVERS_H
