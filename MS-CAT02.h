// Copyright 2022-present Contributors to the dctl project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/dctl

// clang-format on

// CAT5 transform
struct CAT5Transform
{
    Matrix cat5_matrix;
    Matrix inv_matrix;
    float3 d65;
    __DEVICE__ float3 adaptation(float3 rgb, float kelvin) {
        float norm = kelvin / 10000.0; 
        float sx = 1.0 + norm * 0.1;
        float sy = 1.0;
        float sz = 1.0 + norm * -0.1;
        float3 lms = mult_matrix(rgb, cat5_matrix);
        lms.x *= sx;
        lms.y *= sy;
        lms.z *= sz;
        float3 adaptedColor = mult_matrix(lms, inv_matrix);
        return adaptedColor;
    }
};

__DEVICE__ CAT5Transform cat5_transform() {
    CAT5Transform ct;
    ct.cat5_matrix = {0.7328, 0.4296, -0.1624, -0.7036, 1.6975, 0.0061, 0.0030, 0.0136, 0.9834}; 
    ct.inv_matrix = {1.096124, -0.278869, 0.182745, 0.454369, 0.473533, 0.072098, -0.009628, -0.005698, 1.015326};
    ct.d65 = make_float3(0.95047, 1.00000, 1.08883);
    return ct;
}  

// CAT5 adaptation
__DEVICE__ float3 cat5_adaptation(float3 rgb, float kelvin) {
    CAT5Transform ct = cat5_transform();
    return ct.adaptation(rgb, kelvin);
}
