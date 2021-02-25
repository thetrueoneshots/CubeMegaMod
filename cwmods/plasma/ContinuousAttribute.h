#ifndef CONTINUOUSATTRIBUTE_H
#define CONTINUOUSATTRIBUTE_H

#include "../IDA/types.h"
#include "Attribute.h"
#include <vector>

namespace plasma {
    template <typename T>
    class ContinuousAttribute : public plasma::Attribute {
        public:
            std::vector<T> data;
        };
}

#endif // CONTINUOUSATTRIBUTE_H
