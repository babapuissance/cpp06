#include <iostream>
#include "Serializer.hpp"

int main() {
    Data data;
    data.number = 42;
    data.text = "Hello";

    std::cout << "Original pointer: " << &data << "\n";

    uintptr_t raw = Serializer::serialize(&data);
    std::cout << "Serialized (integer): " << raw << "\n";

    Data* back = Serializer::deserialize(raw);
    std::cout << "Deserialized pointer: " << back << "\n";

    if (back == &data)
        std::cout << "OK: pointers match!\n";
    else
        std::cout << "ERROR: pointers don't match\n";

    return 0;
}
