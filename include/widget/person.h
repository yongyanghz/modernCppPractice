#pragma once

#include<string>
#include<map>
#include<iostream>

static const std::map<int, std::string> s_personNameTable = {
    {1000, "Lyra"},
    {1001, "Lana"},
    {1002, "Jack"},
    {1003, "Jasmin"},
    {1004, "Nancy"},
};

class Person{
public:
    template<
        typename T,
        typename = std::enable_if_t<
            !std::is_base_of<Person, std::decay_t<T>>::value
            && !std::is_integral<std::remove_reference_t<T>>::value
        >
    >
    explicit Person(T&& n):
        _name(std::forward<T>(n)){
            static_assert(
                std::is_constructible<std::string, T>::value, 
                "Paramter n can't be used to construct a std::string"
            );
            std::cout<<"Called Person Universal Reference/Template ctor!"<<std::endl;
        }

     explicit Person(int idx):
        _name(nameFromIdx(idx)){}

     // Person(const Person& rhs) // copy ctor, compiler generated, if not define
     // Person(Person&& rhs) // move ctor, compiler generated, if not define
       Person(const Person& rhs){
            std::cout<<"Called Person copy constructor!"<<std::endl;
      }

      Person(Person&& rhs){
            std::cout<<"Called Person move constructor!"<<std::endl;
      }
     
    std::string nameFromIdx(int idx)
    {
        if(s_personNameTable.find(idx) != s_personNameTable.end()){
            return s_personNameTable.at(idx);
        }else{
            return "Na";
        }
    }

private:
    std::string _name;
};

class SpecialPerson: public Person {
public:
    template<
        typename T,
        typename = std::enable_if_t<
            !std::is_same<SpecialPerson, std::decay_t<T>>::value
            && !std::is_integral<std::remove_reference_t<T>>::value
        >
    >
    explicit SpecialPerson(T&& n):
    Person(std::forward<T>(n)){
        std::cout<<"Called SpecialPerson Universal Reference/Template ctor!"<<std::endl;
    }


    SpecialPerson(const SpecialPerson& rhs): // copy ctor;  
        Person(rhs){                        // calls base class forwarding ctor!
        std::cout<<"Called SpecialPerson copy ctor!"<<std::endl;    
    }
    SpecialPerson(SpecialPerson&& rhs):     // move ctor;
        Person(std::move(rhs)){            // calles base class forwarding ctor!
        std::cout<<"Called SpecialPerson move ctor!"<<std::endl;    
    }
};