#pragma once


#include <memory>


#define DECLARE_STD_PTR(x)\
	using x##UPtr = std::unique_ptr<x>;\
	using x##UCPtr = std::unique_ptr<x const>;\
	using x##Ptr = std::shared_ptr<x>;\
	using x##CPtr = std::shared_ptr<x const>;