/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:56:48 by okrahl            #+#    #+#             */
/*   Updated: 2024/12/09 17:24:50 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <iostream>
#include <ctime>

// Randomly instantiate A, B, or C and return as a Base pointer
Base* generate() {
	std::srand(std::time(0)); // Seed for random number generation
	int random = std::rand() % 3;
	Base* result = NULL;

	if (random == 0) {
		result = new A();
		std::cout << "Generated class A" << std::endl;
	}
	else if (random == 1) {
		result = new B();
		std::cout << "Generated class B" << std::endl;
	}
	else {
		result = new C();
		std::cout << "Generated class C" << std::endl;
	}

	return result;
} 