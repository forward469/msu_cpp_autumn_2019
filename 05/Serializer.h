#pragma once
#include <iostream>
#include <cassert>
#include <cstdint>
#include <sstream>


enum class Error
{
	NoError,
	CorruptedArchive
};

class Serializer{
	const char delimiter = ' ';
public:
	explicit Serializer(std::ostream& out): out_(out){}
	//----------------------------------------------------------------
	template <class T>
	Error save(T& object){
		return object.serialize(*this);
	}
	//----------------------------------------------------------------
	template <class... ArgsT>
	Error operator()(ArgsT&&... args){
		return process(std::forward<ArgsT>(args)...);
	}
	//----------------------------------------------------------------

private:
	std::ostream& out_;
	//----------------------------------------------------------------
	Error process(){
		return Error::NoError;
	}
	//----------------------------------------------------------------
	Error process(bool value){
		if(value)
			out_ << "true" << delimiter;
		else
			out_ << "false" << delimiter;
		return Error::NoError;
	}
	//----------------------------------------------------------------
	Error process(uint64_t val){
		out_ << val << delimiter;
		return Error::NoError;
	}
	//----------------------------------------------------------------
	template <class T, class... Args>
	Error process(T&& value, Args&&... args){
		if(!(process(value) == Error::NoError))
            return Error::CorruptedArchive;
		else
			return process(std::forward<Args>(args)...);
	}
	//----------------------------------------------------------------
};


class Deserializer
{
public:
	explicit Deserializer(std::istream& in): in_(in) {}
	//----------------------------------------------------------------
	template <class T>
	Error load(T& object){
		return object.serialize(*this);
	}
	//----------------------------------------------------------------
	template <class... ArgsT>
	Error operator()(ArgsT&&... args){
		return process(std::forward<ArgsT>(args)...);
	}
	//----------------------------------------------------------------
	
private:
	std::istream& in_;
	//----------------------------------------------------------------
	Error process(bool& value){
		std::string text;
		in_ >> text;
		if (text == "true")
			value = true;
		else if (text == "false")
			value = false;
		else
			return Error::CorruptedArchive;

		return Error::NoError;
	}
	//----------------------------------------------------------------
	Error process(){
		return Error::NoError;
	}
	//----------------------------------------------------------------
	Error process(uint64_t& value){
		std::string text;
		in_ >> text;

	
		if(!isdigit(text[0]))
			return Error::CorruptedArchive;
		value = std::stoull(text);
        return Error::NoError;
	}
	//----------------------------------------------------------------
	template <class T, class... Args>
	Error process(T&& val, Args&&... args){
		if(process(val) == Error::NoError)
			return process(std::forward<Args>(args)...);
		else
			return Error::CorruptedArchive;
	}
	//----------------------------------------------------------------
};