#include "Unit.h"

using namespace state;

Unit::Unit()
{
	type = Type::neutre;
	return;
}

Unit::Unit(Type type)
{
	this->type = type;
	return;
}
