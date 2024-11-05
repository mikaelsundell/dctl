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
    // cat02 matrix
    ct.cat02_matrix.m00 = 0.7328; ct.cat02_matrix.m01 = 0.4296; ct.cat02_matrix.m02 = -0.1624;
    ct.cat02_matrix.m03 = -0.7036; ct.cat02_matrix.m04 = 1.6975; ct.cat02_matrix.m05 = 0.0061;
    ct.cat02_matrix.m06 = 0.0030; ct.cat02_matrix.m07 = 0.0136; ct.cat02_matrix.m08 = 0.9834;
    // inverse matrix
    ct.inv_matrix.m00 = 1.096124; ct.inv_matrix.m01 = -0.278869; ct.inv_matrix.m02 = 0.182745;
    ct.inv_matrix.m03 = 0.454369; ct.inv_matrix.m04 = 0.473533; ct.inv_matrix.m05 = 0.072098;
    ct.inv_matrix.m06 = -0.009628; ct.inv_matrix.m07 = -0.005698; ct.inv_matrix.m08 = 1.015326;
    return ct;
}  

// CAT02 adaptation
__DEVICE__ float3 cat02_adaptation(float3 rgb, float kelvin) {
    CAT02Transform ct = cat02_transform();
    return ct.adaptation(rgb, kelvin);
}
