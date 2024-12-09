/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:56:58 by okrahl            #+#    #+#             */
/*   Updated: 2024/12/09 17:05:23 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>

// Identify the type of the object pointed to by p
void identify(Base* p) {
	if (dynamic_cast<A*>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "C" << std::endl;
}

// Identify the type of the object referenced by p
void identify(Base& p) {
	try {
		(void)dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
		return;
	} catch (...) {}

	try {
		(void)dynamic_cast<B&>(p);
		std::cout << "B" << std::endl;
		return;
	} catch (...) {}

	try {
		(void)dynamic_cast<C&>(p);
		std::cout << "C" << std::endl;
		return;
	} catch (...) {}
} 