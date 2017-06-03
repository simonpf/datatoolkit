/**
 * Simple reader for \c .mat files.
 */

#include <mex.h>
#include <mat.h>
#include <matrix.h>
#include <assert.h>

#include "structured_data.h"


void close_matlab_file(MATFile * file)
{
    matClose(file);
};

template<typename NumberType>
StructuredData<NumberType> read_matlab_data(std::string filename,
                                            size_t directory_index = 0)
{
    mxArray* array_pointer = nullptr;
    const char* array_name = nullptr;

    // Open the file.
    std::shared_ptr<MATFile> file(matOpen(filename.c_str(), "r"), close_matlab_file);
    if (!file.get())
    {
        std::cout << matOpen(filename.c_str(), "r") << std::endl;
        throw std::logic_error("Could not open file.");
    }

    // Read the directory.
    for (size_t i = 0; i < std::max<int>(directory_index - 1, 0); i++)
    {
        array_pointer = matGetNextVariable(file.get(), &array_name);
    }
    array_pointer = matGetNextVariable(file.get(), &array_name);

    if (!array_pointer)
    {
        throw std::logic_error(
            "Could not read the directory index from file."
            );
    }

    // Check the number type.
    mxClassID array_class = mxGetClassID(array_pointer);
    if ((typeid(NumberType) == typeid(char)) && (array_class != mxINT8_CLASS))
    {
        throw std::logic_error(
            "Matlab array is of type int8 but the expected C type is not char."
            );
    }
    if ((typeid(NumberType) == typeid(unsigned char)) && (array_class != mxINT8_CLASS))
    {
        throw std::logic_error(
            "Matlab array is of type uint8 but the expected C type is not unsigned char."
            );
    }
    if ((typeid(NumberType) == typeid(short)) && (array_class != mxINT16_CLASS))
    {
        throw std::logic_error(
            "Matlab array is of type int16 but the expected C type is not short."
            );
    }
    if ((typeid(NumberType) == typeid(unsigned short)) && (array_class != mxUINT16_CLASS))
    {
        throw std::logic_error(
            "Matlab array is of type uint16 but the expected C type is not unsigned short."
            );
    }
    if ((typeid(NumberType) == typeid(int)) && (array_class != mxINT32_CLASS))
    {
        throw std::logic_error(
            "Matlab array is of type int32 but the expected C type is not int."
            );
    }
    if ((typeid(NumberType) == typeid(unsigned int)) && (array_class != mxUINT32_CLASS))
    {
        throw std::logic_error(
            "Matlab array is of type uint32 but the expected C type is not unsigned int."
            );
    }
    if ((typeid(NumberType) == typeid(long long)) && (array_class != mxINT64_CLASS))
    {
        throw std::logic_error(
            "Matlab array is of type int64 but the expected C type is not long long."
            );
    }
    if ((typeid(NumberType) == typeid(unsigned long long)) && (array_class != mxUINT64_CLASS))
    {
        throw std::logic_error(
            "Matlab array is of type uint64 but the expected C type is not unsigned long long."
            );
    }
    if ((typeid(NumberType) == typeid(float)) && (array_class != mxSINGLE_CLASS))
    {
        throw std::logic_error(
            "Matlab array is of type single but the expected C type is not float."
            );
    }
    if ((typeid(NumberType) == typeid(float)) && (array_class != mxDOUBLE_CLASS))
    {
        throw std::logic_error(
            "Matlab array is of type double but the expected C type is not double."
            );
    }

    size_t nelements = mxGetNumberOfElements(array_pointer);

    // Copy the dimensions.
    std::vector<size_t> dimensions(mxGetNumberOfDimensions(array_pointer));
    const size_t* dimension_pointer = mxGetDimensions(array_pointer);
    for (size_t& i : dimensions)
    {
        i = *dimension_pointer;
        dimension_pointer++;
    }

    // Order of dimension is N-major, i.e. first columns, then rows, then higher dimensions.
    std::vector<size_t> order(dimensions.size());
    for (size_t i = 0; i < dimensions.size(); i++)
    {
        order[i] = i;
    }

    // Create shared pointer to data.
    double * ptr = (NumberType *) mxGetData(array_pointer);
    std::shared_ptr<NumberType> data(file, ptr);
    return StructuredData<NumberType>(data, dimensions, order);
}
