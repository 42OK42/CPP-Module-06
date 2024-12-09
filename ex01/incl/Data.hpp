/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:41:54 by okrahl            #+#    #+#             */
/*   Updated: 2024/12/09 17:02:16 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_HPP
# define DATA_HPP

#include <string>

struct Data
{
	int value;
	std::string text;

	// Default constructor
	Data() : value(0), text("") {}
	
	// Copy constructor
	Data(const Data& src) : value(src.value), text(src.text) {}
	
	// Assignment operator
	Data& operator=(const Data& src) {
		if (this != &src) {
			value = src.value;
			text = src.text;
		}
		return *this;
	}
	
	// Destructor
	~Data() {}
};

#endif 