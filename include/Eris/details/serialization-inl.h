#pragma once



#include <Eris/serialization.h>

#include <cstring>
#include <vector>


namespace Eris {    
    template<typename T>
    void serialize(const ConstArrayAccessor1<T>& array,
               std::vector<uint8_t>* buffer){
                size_t size= sizeof(T)*array.size();

                serialize(reinterpret_cast<const uint8_t*>(array.data()),size,buffer);
               }

    inline void serialize(const uint8_t* data, size_t size,
                           std::vector<uint8_t>* buffer) {
        buffer->insert(buffer->end(), data, data + size);
    }

    inline void deserialize(const std::vector<uint8_t>& buffer,
                            std::vector<uint8_t>* data) {
        data->resize(buffer.size());
        std::copy(buffer.begin(), buffer.end(), data->begin());
    }

    template<typename T>
    void deserialize(const std::vector<uint8_t>& buffer,Array1<T>* accessor){
                std::vector<uint8_t> data;
                deserialize(buffer, &data);
                accessor->resize(data.size() / sizeof(T));
                memcpy(reinterpret_cast<uint8_t*>(accessor->data()), data.data(), data.size());
    }



}