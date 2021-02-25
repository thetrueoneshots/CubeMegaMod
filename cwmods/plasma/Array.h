#ifndef ARRAY_H
#define ARRAY_H

#include "../IDA/types.h"

namespace plasma {
    template <typename T>
    class Array {
        public:
            T *start;
            T *end;
            T *cap;

        int Length() {
            return (this->end - this->start);
        }

        T Get(int i) {
            return start[i];
        }

        void Set(int i, T x) {
            start[i] = x;
        }
    };
}

#endif // ARRAY_H
