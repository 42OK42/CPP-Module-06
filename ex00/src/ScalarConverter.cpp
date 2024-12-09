/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:19:51 by okrahl            #+#    #+#             */
/*   Updated: 2024/12/09 19:43:24 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>
#include <string>
#include <cctype>
#include <limits>
#include <cstdlib>
#include <cmath>
#include <sstream>

enum LiteralType {
	CHAR,
	INT,
	FLOAT,
	DOUBLE,
	INVALID
};

static LiteralType detect_type(const std::string &literal) {
	if (literal.empty())
		return INVALID;
	
	// Check for char literal ('c')
	if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'')
		return CHAR;
	
	// Check for special values
	if (literal == "nan" || literal == "+inf" || literal == "-inf")
		return DOUBLE;
	if (literal == "nanf" || literal == "+inff" || literal == "-inff")
		return FLOAT;

	// Check for float (contains 'f' at the end)
	if (literal[literal.length() - 1] == 'f')
		return FLOAT;

	// Check for decimal point (must be double since float was already checked)
	if (literal.find('.') != std::string::npos)
		return DOUBLE;

	// Try to interpret as integer
	for (size_t i = 0; i < literal.length(); i++) {
		if (i == 0 && (literal[i] == '-' || literal[i] == '+'))
			continue;
		if (!std::isdigit(literal[i]))
			return INVALID;
	}
	return INT;
}

void ScalarConverter::convert(const std::string &literal) {
	LiteralType type = detect_type(literal);

	try {
		switch (type) {
			case CHAR: {
				char c = literal[1];
				std::cout << "char: " << c << std::endl;
				std::cout << "int: " << static_cast<int>(c) << std::endl;
				std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
				std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
				break;
			}
			case INT: {
				int i = std::atoi(literal.c_str());
				std::cout << "char: " << (std::isprint(i) ? std::string(1, static_cast<char>(i)) : "Non displayable") << std::endl;
				std::cout << "int: " << i << std::endl;
				std::cout << "float: " << static_cast<float>(i) << ".0f" << std::endl;
				std::cout << "double: " << static_cast<double>(i) << ".0" << std::endl;
				break;
			}
			case FLOAT: {
				float f;
				if (literal == "nanf" || literal == "+inff" || literal == "-inff") {
					f = (literal == "nanf") ? std::numeric_limits<float>::quiet_NaN() :
						(literal == "+inff") ? std::numeric_limits<float>::infinity() :
						-std::numeric_limits<float>::infinity();
					std::cout << "char: impossible" << std::endl;
					std::cout << "int: impossible" << std::endl;
				} else {
					std::stringstream ss(literal);
					ss >> f;
					if (ss.fail())
						throw std::runtime_error("Float conversion failed");
					
					// Char conversion
					if (f > std::numeric_limits<char>::max() || f < std::numeric_limits<char>::min() || std::isnan(f))
						std::cout << "char: impossible" << std::endl;
					else if (!std::isprint(static_cast<char>(f)))
						std::cout << "char: Non displayable" << std::endl;
					else
						std::cout << "char: '" << static_cast<char>(f) << "'" << std::endl;
					
					// Int conversion
					if (f > std::numeric_limits<int>::max() || f < std::numeric_limits<int>::min() || std::isnan(f))
						std::cout << "int: impossible" << std::endl;
					else
						std::cout << "int: " << static_cast<int>(f) << std::endl;
				}

				std::cout << "float: ";
				if (f == static_cast<int>(f))
					std::cout << f << ".0f";
				else
					std::cout << f << "f";
				std::cout << std::endl;
				
				std::cout << "double: ";
				if (f == static_cast<int>(f))
					std::cout << static_cast<double>(f) << ".0";
				else
					std::cout << static_cast<double>(f);
				std::cout << std::endl;
				break;
			}
			case DOUBLE: {
				double d;
				if (literal == "nan" || literal == "+inf" || literal == "-inf") {
					d = (literal == "nan") ? std::numeric_limits<double>::quiet_NaN() :
						(literal == "+inf") ? std::numeric_limits<double>::infinity() :
						-std::numeric_limits<double>::infinity();
					std::cout << "char: impossible" << std::endl;
					std::cout << "int: impossible" << std::endl;
				} else {
					std::stringstream ss(literal);
					ss >> d;
					if (ss.fail())
						throw std::runtime_error("Double conversion failed");
					
					// Char conversion
					if (d > std::numeric_limits<char>::max() || d < std::numeric_limits<char>::min() || std::isnan(d))
						std::cout << "char: impossible" << std::endl;
					else if (!std::isprint(static_cast<char>(d)))
						std::cout << "char: Non displayable" << std::endl;
					else
						std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;
					
					// Int conversion
					if (d > std::numeric_limits<int>::max() || d < std::numeric_limits<int>::min() || std::isnan(d))
						std::cout << "int: impossible" << std::endl;
					else
						std::cout << "int: " << static_cast<int>(d) << std::endl;
				}
				
				std::cout << "float: ";
				if (d == static_cast<int>(d))
					std::cout << static_cast<float>(d) << ".0f";
				else
					std::cout << static_cast<float>(d) << "f";
				std::cout << std::endl;
				
				std::cout << "double: ";
				if (d == static_cast<int>(d))
					std::cout << d << ".0";
				else
					std::cout << d;
				std::cout << std::endl;
				break;
			}
			default:
				std::cout << "Invalid literal" << std::endl;
				break;
		}
	} catch (const std::exception &e) {
		std::cout << "Conversion error: " << e.what() << std::endl;
	}
} 