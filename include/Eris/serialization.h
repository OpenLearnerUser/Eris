#pragma once
#include<Eris/array1.h>



#include<vector>



namespace Eris {    

class Serializable{
    public:
        Serializable() = default;
        virtual ~Serializable() = default;


        virtual void serialize(std::vector<uint8_t>* butter)const=0;

        virtual void deserialize(const std::vector<uint8_t>& butter)=0;

};

void serialize(Serializable& serializable, std::vector<uint8_t>* butter);

void serialize(const uint8_t* data, size_t size,std::vector<uint8_t>* butter);


template<typename T>
void serialize(ConstArrayAccessor1<T>& accessor, std::vector<uint8_t>* butter);


template<typename T>
void deserialize(const std::vector<uint8_t>& buffer,Serializable* serializable);


void deserialize(const std::vector<uint8_t>& buffer,std::vector<uint8_t>* data);


template<typename T>
void deserialize(const std::vector<uint8_t>& buffer,Array1<T>* accessor);





}


#include "Eris/details/serialization-inl.h"

