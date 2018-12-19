#include "Basic.h"
#include <math.h>
#include <string>
#include "Factory.h"
#include "Exceptions.h"
#include "Creator.h"

namespace {
	bool add_commands() noexcept
	{
		AddCreator* add = new AddCreator;
		Factory::get_instance()->make_command("+", add);
		SubCreator* sub = new SubCreator;
		Factory::get_instance()->make_command("-", sub);
		MulCreator* mul = new MulCreator;
		Factory::get_instance()->make_command("*", mul);
		DivCreator* div = new DivCreator;
		Factory::get_instance()->make_command("/", div);
		SqrtCreator* sqrt = new SqrtCreator;
		Factory::get_instance()->make_command("SQRT", sqrt);
		PopCreator* pop = new PopCreator;
		Factory::get_instance()->make_command("POP", pop);
		PushCreator* push = new PushCreator;
		Factory::get_instance()->make_command("PUSH", push);
		PrintCreator* print = new PrintCreator;
		Factory::get_instance()->make_command("PRINT", print);
		DefineCreator* define = new DefineCreator;
		Factory::get_instance()->make_command("DEFINE", define);
		return 1;
	}

	bool fake = add_commands();
}

//функция проверки числа на наличие лишних символов
bool check(std::string buffer){
	int i = 0;
	while (buffer[i] >= 48 && buffer[i] <= 57 || buffer[i] == '.')
		i++;
	if (i == buffer.length() - 1)
		return 1;
	return 0;
}

void Push::make_operation(Context& context){

	double arg = DBL_MIN;
	//если есть define
	if (!context.is_empty_var())
		arg = context.find_var(context.back_());
	if (arg == DBL_MIN){
		//если в числе хранятся посторонние символы
		if (!check(context.back_()))
			throw invalid_arg();

		arg = std::stod(context.back_());
	}
	context.pop_back_();
	context.push_arg(arg);
}

void Pop::make_operation(Context& context){
	//если пустой стек
	if (context.size_arg() <= 0)
		throw empty_stack();
	context.pop_arg();
}

void Print::make_operation(Context& context){
	//если пустой стек
	if (!context.size_arg())
		throw empty_stack();
	std::cout << context.top_arg();
}

void Define::make_operation(Context& context){
	//если нечего заменять
	if (!context.size_())
		throw empty_args();
	std::string variable = context.back_();
	context.pop_back_();
	std::string name = context.back_();
	if (!check(context.back_()))
		throw invalid_arg();
	context.add_var(name, std::stod(variable));
}

void Add::make_operation(Context& context){
	double arg[2];
	//если не хватает аргументов для операции
	if (context.size_() + context.size_arg() < 2)
		throw empty_args();
	int counter = 0;
	while (counter != 2 && context.size_()){
		//поиск define
		arg[counter] = context.find_var(context.back_());
		//если не нашел
		if (arg[counter] == DBL_MIN){
			//проверка числа
			if (!check(context.back_()))
				throw invalid_arg();
			arg[counter] = std::stod(context.back_());
		}
		context.pop_back_();
		counter++;
	}
	while (counter != 2)
	{
		arg[counter] = context.top_arg();
		context.pop_back_();
		counter++;
	}
	context.push_arg(arg[0] + arg[1]);
}


void Subtract::make_operation(Context& context) {
	double arg[2];
	if (context.size_() + context.size_arg() < 2)
		throw empty_args();
	int counter = 0;
	while (counter != 2 && context.size_()) {
		arg[counter] = context.find_var(context.back_());
		if (arg[counter] == DBL_MIN) {
			if (!check(context.back_()))
				throw invalid_arg();
			arg[counter] = std::stod(context.back_());
		}
		context.pop_back_();
		counter++;
	}
	while (counter != 2) {
		arg[counter] = context.top_arg();
		context.pop_back_();
		counter++;
	}
	context.push_arg(arg[1] - arg[0]);
}


void Multiplicate::make_operation(Context& context) {
	double arg[2];
	if (context.size_() + context.size_arg() < 2)
		throw empty_args();
	int counter = 0;
	while (counter != 2 && context.size_()) {
		arg[counter] = context.find_var(context.back_());
		if (arg[counter] == DBL_MIN) {
			if (!check(context.back_()))
				throw invalid_arg();
			arg[counter] = std::stod(context.back_());
		}
		context.pop_back_();
		counter++;
	}
	while (counter != 2) {
		arg[counter] = context.top_arg();
		context.pop_back_();
		counter++;
	}
	context.push_arg(arg[0] * arg[1]);
}


void Division::make_operation(Context& context) {
	double arg[2];
	if (context.size_() + context.size_arg() < 2)
		throw empty_args();
	int counter = 0;
	while (counter != 2 && context.size_()) {
		arg[counter] = context.find_var(context.back_());
		if (arg[counter] == DBL_MIN) {
			if (!check(context.back_()))
				throw invalid_arg();
			arg[counter] = std::stod(context.back_());
		}
		context.pop_back_();
		counter++;
	}
	while (counter != 2) {
		arg[counter] = context.top_arg();
		context.pop_back_();
		counter++;
	}
	if (!arg[0])
		throw division_by_zero();
	context.push_arg(arg[1] / arg[0]);
}

void Sqrt::make_operation(Context& context) {
	double arg;
	if (context.size_() + context.size_arg() < 1)
		throw empty_args();
	int counter = 0;
	if (context.size_()) {
		arg = context.find_var(context.back_());
		if (arg == DBL_MIN) {
			if (!check(context.back_()))
				throw invalid_arg();
			arg = std::stod(context.back_());
		}
		context.pop_back_();
	}
	else {
		arg = context.top_arg();
		context.pop_back_();
		counter++;
	}
	if (arg < 0)
		throw negative_number();
	context.push_arg(sqrt(arg));
}