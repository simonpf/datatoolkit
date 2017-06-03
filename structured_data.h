/**
 * Structured data class representing serialized tensors.
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <numeric>
#include <vector>

#include "type_names.h"

template <typename NumberType>
class StructuredData {

public:

    StructuredData(
        std::shared_ptr<NumberType> data ,
        std::vector<size_t> dimensions,
        std::vector<size_t> order
        ) : raw_data(data), dimensions(dimensions), order(order) {};

    StructuredData(
        std::shared_ptr<NumberType> data,
        size_t length
        ) : raw_data(data), dimensions(1), order(1)
    {
        dimensions[0] = length;
        order[0] = 0;
    };

    NumberType & get_element(size_t i)       {return raw_data.get()[i];};
    NumberType   get_element(size_t i) const {return raw_data.get()[i];};

    size_t ndimensions() const {return dimensions.size();};
    size_t nelements() const
    {
        return std::accumulate(
            dimensions.begin(), dimensions.end(),
            1, std::multiplies<NumberType>()
            );
    };

    const std::vector<size_t> dimensions; // Number of elements in each dimension.
    const std::vector<size_t> order;      // Serialization order of the array.


private:

    std::shared_ptr<NumberType> raw_data;

};

template <typename NumberType>
std::ostream& operator<< (
    std::ostream& stream,
    const StructuredData<NumberType>& sd
    )
{
    stream << "Structured Data of type " << Type<NumberType>::name() << "." << std::endl;

    stream << "  Dimensions: [";
    for (size_t i = 0; i < sd.dimensions.size() - 1; i++)
    {
        stream << sd.dimensions[i] << ", ";
    }
    stream << sd.dimensions.back() << "]" << std::endl;

    stream << "  Order:      [";
    for (size_t i = 0; i < sd.order.size() - 1; i++)
    {
        stream << sd.order[i] << ", ";
    }
    stream << sd.order.back() << "]" << std::endl;

    stream << "  Data:       [";
    for (size_t i = 0; i < std::min<size_t>(sd.nelements(), 5) - 1; i++)
    {
        stream << sd.get_element(i) << ", ";
    }
    stream << sd.get_element(std::max<size_t>(sd.nelements() - 1, 5)) << " ...]" << std::endl;
}
