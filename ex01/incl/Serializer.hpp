#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP

#include <stdint.h>
#include "Data.hpp"

class Serializer {
private:
	// Private constructors to prevent instantiation
	Serializer(void);
	Serializer(const Serializer &src);
	Serializer &operator=(const Serializer &src);
	~Serializer(void);

public:
	// Convert a Data pointer to a uintptr_t
	static uintptr_t serialize(Data* ptr);
	// Convert a uintptr_t back to a Data pointer
	static Data* deserialize(uintptr_t raw);
};

#endif 