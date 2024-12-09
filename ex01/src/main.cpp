/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:19:46 by okrahl            #+#    #+#             */
/*   Updated: 2024/12/09 17:36:36 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>
#include <string>

int main(void)
{
	// Create a Data structure with test data
	Data* originalData = new Data;
	originalData->value = 42;
	originalData->text = "Hello 42!";

	std::cout << "\n=== Original Data ===\n";
	std::cout << "Pointer address: " << originalData << std::endl;
	std::cout << "Value: " << originalData->value << std::endl;
	std::cout << "Text: " << originalData->text << std::endl;

	// Serialize the pointer
	uintptr_t serialized = Serializer::serialize(originalData);
	std::cout << "\n=== Serialized Form ===\n";
	std::cout << "As uintptr_t: " << serialized << std::endl;

	// Deserialize back to a pointer
	Data* deserialized = Serializer::deserialize(serialized);
	std::cout << "\n=== Deserialized Data ===\n";
	std::cout << "Pointer address: " << deserialized << std::endl;
	std::cout << "Value: " << deserialized->value << std::endl;
	std::cout << "Text: " << deserialized->text << std::endl;

	// Check if the pointers are identical
	std::cout << "\n=== Pointer Comparison ===\n";
	std::cout << "Are the pointers identical? " << (originalData == deserialized ? "YES" : "NO") << std::endl;

	// Clean up
	delete originalData;
	return 0;
} 