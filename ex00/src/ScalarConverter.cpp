/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:19:51 by okrahl            #+#    #+#             */
/*   Updated: 2024/12/10 16:31:41 by okrahl           ###   ########.fr       */
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
	
	// Check for char literal
	if (literal.length() == 1 && !std::isdigit(literal[0]))  // Single non-digit character
		return CHAR;
	if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'')  // 'c' or '0'
		return CHAR;
	
	// Check for special values
	if (literal == "nan" || literal == "+inf" || literal == "-inf" || literal == "inf")
		return DOUBLE;
	if (literal == "nanf" || literal == "+inff" || literal == "-inff" || literal == "inff")
		return FLOAT;

	size_t point_count = 0;
	size_t f_count = 0;
	bool has_digit = false;
	bool has_digit_after_point = false;

	size_t start = (literal[0] == '-' || literal[0] == '+') ? 1 : 0;
	
	for (size_t i = start; i < literal.length(); i++) {
		if (literal[i] == '.') {
			point_count++;
			if (i == literal.length() - 1) // Point cannot be at the end
				return INVALID;
		} else if (literal[i] == 'f') {
			f_count++;
			if (i != literal.length() - 1 || !point_count) // 'f' must be at the end and there must be a point before
				return INVALID;
		} else if (!std::isdigit(literal[i])) {
			return INVALID;
		} else {
			has_digit = true;
			if (point_count > 0)
				has_digit_after_point = true;
		}
	}

	if (!has_digit || point_count > 1 || f_count > 1)
		return INVALID;

	// Float must have a point and at least one digit after it
	if (f_count == 1) {
		if (!point_count || !has_digit_after_point)
			return INVALID;
		return FLOAT;
	}

	// Double must have a point and at least one digit after it
	if (point_count == 1) {
		if (!has_digit_after_point)
			return INVALID;
		return DOUBLE;
	}

	return INT;
}

template<typename T>
static T convert_literal(const std::string &literal) {
	if (literal == "nan" || literal == "nanf")
		return std::numeric_limits<T>::quiet_NaN();
	if (literal == "+inf" || literal == "inf" || literal == "+inff" || literal == "inff")
		return std::numeric_limits<T>::infinity();
	if (literal == "-inf" || literal == "-inff")
		return -std::numeric_limits<T>::infinity();

	std::stringstream ss(literal);
	T value;
	ss >> value;
	if (ss.fail())
		throw std::runtime_error("Conversion failed");
	return value;
}

void ScalarConverter::convert(const std::string &literal) {
	LiteralType type = detect_type(literal);

	//print detected type
	std::cout << "Detected type: ";
	switch (type) {
		case CHAR: std::cout << "CHAR" << std::endl; break;
		case INT: std::cout << "INT" << std::endl; break;
		case FLOAT: std::cout << "FLOAT" << std::endl; break;
		case DOUBLE: std::cout << "DOUBLE" << std::endl; break;
		default: std::cout << "INVALID" << std::endl; break;
	}

	if (type == INVALID) {
		std::cout << "Invalid literal" << std::endl;
		return;
	}

	try {
		switch (type) {
			case CHAR: {
				char c;
				if (literal.length() == 1)
					c = literal[0];  // Direktes Zeichen
				else
					c = literal[1];  // Zeichen zwischen Anführungszeichen
				
				std::cout << "char: '" << c << "'" << std::endl;
				std::cout << "int: " << static_cast<int>(c) << std::endl;
				std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
				std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
				break;
			}
			case INT: {
				long long value;
				std::stringstream ss(literal);
				ss >> value;
				
				if (ss.fail() || value > std::numeric_limits<int>::max() || value < std::numeric_limits<int>::min())
					throw std::runtime_error("Integer overflow");
					
				int i = static_cast<int>(value);
				
				// Char conversion
				if (i > std::numeric_limits<char>::max() || i < std::numeric_limits<char>::min())
					std::cout << "char: impossible" << std::endl;
				else if (!std::isprint(static_cast<char>(i)))
					std::cout << "char: Non displayable" << std::endl;
				else
					std::cout << "char: '" << static_cast<char>(i) << "'" << std::endl;
				
				std::cout << "int: " << i << std::endl;
				std::cout << "float: " << static_cast<float>(i) << ".0f" << std::endl;
				std::cout << "double: " << static_cast<double>(i) << ".0" << std::endl;
				break;
			}
			case FLOAT: {
				float f;
				if (literal == "nanf" || literal == "+inff" || literal == "-inff" || literal == "inff") {
					f = (literal == "nanf") ? std::numeric_limits<float>::quiet_NaN() :
						(literal == "+inff" || literal == "inff") ? std::numeric_limits<float>::infinity() :
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
				if (literal == "nan" || literal == "+inf" || literal == "-inf" || literal == "inf") {
					d = (literal == "nan") ? std::numeric_limits<double>::quiet_NaN() :
						(literal == "+inf" || literal == "inf") ? std::numeric_limits<double>::infinity() :
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