/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:19:58 by okrahl            #+#    #+#             */
/*   Updated: 2024/12/09 17:37:05 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# include <string>

class ScalarConverter
{
private:
	// Private constructor to prevent instantiation
	ScalarConverter(void);
	// Private copy constructor
	ScalarConverter(const ScalarConverter &src);
	// Private assignment operator
	ScalarConverter &operator=(const ScalarConverter &src);
	// Private destructor
	~ScalarConverter(void);

public:
	// Only public method - static convert function
	static void convert(const std::string &literal);
};

#endif 