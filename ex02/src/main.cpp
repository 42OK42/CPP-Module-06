/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:57:05 by okrahl            #+#    #+#             */
/*   Updated: 2024/12/09 16:57:18 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include <iostream>


Base* generate();
void identify(Base* p);
void identify(Base& p);

int main() {
	Base* basePtr = generate();

	std::cout << "Identifying by pointer:" << std::endl;
	identify(basePtr);

	std::cout << "Identifying by reference:" << std::endl;
	identify(*basePtr);

	delete basePtr;
	return 0;
}
