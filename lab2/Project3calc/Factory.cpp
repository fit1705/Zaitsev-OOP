#include "Factory.h"
#include "Exceptions.h"


Factory* Factory::get_instance()
{
	static Factory factory;
	return &factory;
}

void Factory::make_command(std::string key, OperatorCreater *value) {
	
	factory_map[key] = value;

}

Operator* Factory::get_operator(std::string name) {
	if (factory_map.find(name) == factory_map.end())
		throw no_operation();
	return factory_map.at(name)->create();
}
Factory::~Factory()
{
	for (auto i = factory_map.begin(); i != factory_map.end(); i++)
		delete i->second;
}
