#ifndef DISCRETEATTRIBUTE_H
#define DISCRETEATTRIBUTE_H

#include "../IDA/types.h"
#include "Attribute.h"
#include <vector>

namespace plasma {
    template <typename T>
    class DiscreteAttribute : public plasma::Attribute {
        public:
            std::vector<T> data;
        };
}

#endif // DISCRETEATTRIBUTE_H
