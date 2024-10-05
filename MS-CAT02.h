// Copyright 2022-present Contributors to the dctl project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/dctl

// clang-format on

// CAT02 transform
struct CAT02Transform
{
    Matrix cat02_matrix;
    Matrix inv_matrix;
    
    __DEVICE__ float3 adaptation(float3 xyz, float kelvin) {
        float norm = kelvin / 10000.0; 
        float sx = 1.0 + norm * 1.0;
        float sy = 1.0;
        float sz = 1.0 + norm * -1.0;
        float3 lms = mult_matrix(xyz, cat02_matrix);
        lms.x *= sx;
        lms.y *= sy;
        lms.z *= sz;
        float3 color = mult_matrix(lms, inv_matrix);
        return color;
    }
};

__DEVICE__ CAT02Transform cat02_transform() {
    CAT02Transform ct;
    ct.cat02_matrix = {0.7328, 0.4296, -0.1624, -0.7036, 1.6975, 0.0061, 0.0030, 0.0136, 0.9834}; 
    ct.inv_matrix = {1.096124, -0.278869, 0.182745, 0.454369, 0.473533, 0.072098, -0.009628, -0.005698, 1.015326};
    return ct;
}  

// CAT02 adaptation
__DEVICE__ float3 cat02_adaptation(float3 rgb, float kelvin) {
    CAT02Transform ct = cat02_transform();
    return ct.adaptation(rgb, kelvin);
}
