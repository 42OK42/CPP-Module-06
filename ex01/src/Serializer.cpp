/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:19:51 by okrahl            #+#    #+#             */
/*   Updated: 2024/12/09 16:44:13 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

// Private constructor to prevent instantiation
Serializer::Serializer(void) {}

Serializer::Serializer(const Serializer &src) { (void)src; }

Serializer &Serializer::operator=(const Serializer &src) {
	(void)src;
	return *this;
}

Serializer::~Serializer(void) {}

// Convert a Data pointer to a uintptr_t
uintptr_t Serializer::serialize(Data* ptr) {
	return reinterpret_cast<uintptr_t>(ptr);
}

// Convert a uintptr_t back to a Data pointer
Data* Serializer::deserialize(uintptr_t raw) {
	return reinterpret_cast<Data*>(raw);
} 