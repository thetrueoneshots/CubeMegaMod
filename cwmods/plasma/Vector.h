#ifndef PLASMA_VECTOR_H
#define PLASMA_VECTOR_H


namespace plasma {
    template <int N, typename T>
    class Vector {
        public:
            T elements[N];

            T Get(int i) {
                return elements[i];
            }

            void Set(int i, T x) {
                elements[i] = x;
            }
    };
}

#endif // PLASMA_VECTOR_H
