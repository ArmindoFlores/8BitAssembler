#ifndef __EXCEPTIONS_H_INCLUDED__
#define __EXCEPTIONS_H_INCLUDED__

#include <exception>
#include <string>

using namespace std;

void catchException(exception *exc, int line, int col, string *source);

namespace asmExceptions {
	class invalidTokenException : public exception
	{
		virtual const char* what() const throw()
		{
			return "Error: Invalid token";
		}
	};

	class  invalidArgumentsException : public exception
	{
		virtual const char* what() const throw()
		{
			return "Error: Invalid arguments";
		}
	};

	class  invalidArgumentNumberException : public exception
	{
		virtual const char* what() const throw()
		{
			return "Error: Wrong number of arguments";
		}
	};

	class blankLabelException : public exception
	{
		virtual const char* what() const throw()
		{
			return "Error: Labels cannot be blank";
		}

	};

	class misplacedTokenException : public exception
	{
		virtual const char* what() const throw()
		{
			return "Error: This token is invalid here";
		}
	};

	class noSeparatorException : public exception
	{
		virtual const char* what() const throw()
		{
			return "Error: No separation was found between arguments";
		}
	};
}

#endif