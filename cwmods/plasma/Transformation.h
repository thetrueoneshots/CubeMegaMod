#ifndef PLASMA_TRANSFORMATION_H
#define PLASMA_TRANSFORMATION_H

#include "../IDA/types.h"
#include "Keyable.h"
#include "DiscreteAttribute.h"
#include "ContinuousAttribute.h"
#include "Vector.h"
#include "Matrix.h"

namespace plasma {
    class Transformation : public plasma::Keyable {
        public:
			plasma::ContinuousAttribute<plasma::Vector<2, float>> translation;
			plasma::ContinuousAttribute<plasma::Matrix<float>> deformation;
			plasma::ContinuousAttribute<plasma::Vector<3, float>> rotation;
			plasma::ContinuousAttribute<plasma::Vector<2, float>> pivot;
			__int64 field_290;
			__int64 field_298;
			plasma::Matrix<float> matrix;
			__int64 field_2E0;
			__int64 field_2E8;
			__int64 field_2F0;
			__int64 field_2F8;
			__int64 field_300;
			__int64 field_308;
			__int64 field_310;
			__int64 field_318;
			__int64 field_320;
        };
}

static_assert(sizeof(plasma::Transformation) == 0x328, "plasma::Transformation is not the correct size.");

#endif // PLASMA_TRANSFORMATION_H
