/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:56:48 by okrahl            #+#    #+#             */
/*   Updated: 2024/12/09 16:56:51 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <ctime>

// Randomly instantiate A, B, or C and return as a Base pointer
Base* generate() {
	std::srand(std::time(0)); // Seed for random number generation
	int random = std::rand() % 3;

	if (random == 0)
		return new A();
	else if (random == 1)
		return new B();
	else
		return new C();
} 