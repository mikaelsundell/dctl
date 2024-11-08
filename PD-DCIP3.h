// Copyright 2022-present Contributors to the dctl project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/dctl

// clang-format on

// DCI-P3 curve
struct DCIP3Curve
{
    float threshold;
    float slope;
    float exp;
    float scale;
    float offset;
};

__DEVICE__ float DCIP3Curve_lin_dcip3(struct DCIP3Curve cv, float lin) {
    return pow_f(lin, cv.exp);
}

__DEVICE__ float DCIP3Curve_dcip3_lin(struct DCIP3Curve cv, float val) {
    return pow_f(val, 1 / cv.exp);
}

// DCI-P3 colorspace
struct DCIP3Colorspace
{
    struct Matrix dcip3_matrix;
    struct Matrix xyz_matrix;
};

__DEVICE__ float3 DCIP3Colorspace_xyz_dcip3(struct DCIP3Colorspace cs, float3 xyz) {
    return mult_matrix(xyz, cs.dcip3_matrix);
}
__DEVICE__ float3 DCIP3Colorspace_dcip3_xyz(struct DCIP3Colorspace cs, float3 dcip3) {
    return mult_matrix(dcip3, cs.xyz_matrix);
}

__DEVICE__ struct DCIP3Curve dcip3_curve() {
    struct DCIP3Curve cv;
    cv.exp = 1 / 2.6;
    return cv;
}

__DEVICE__ struct DCIP3Colorspace dcip3_colorspace() {
    struct DCIP3Colorspace cs;
    // xu
    cs.dcip3_matrix.m00 = 2.4934969; cs.dcip3_matrix.m01 = -0.9313836; cs.dcip3_matrix.m02 = -0.4027108;
    cs.dcip3_matrix.m03 = -0.8294890; cs.dcip3_matrix.m04 = 1.7626641; cs.dcip3_matrix.m05 = 0.0236247;
    cs.dcip3_matrix.m06 = 0.0358458; cs.dcip3_matrix.m07 = -0.0761724; cs.dcip3_matrix.m08 = 0.9568845;
    // XYZ to DCI-P3 matrix


    cs.xyz_matrix.m00 =  0.4865709; cs.xyz_matrix.m01 = 0.2656677; cs.xyz_matrix.m02 = 0.1982173;
    cs.xyz_matrix.m03 =  0.2289746; cs.xyz_matrix.m04 = 0.6917385; cs.xyz_matrix.m05 = 0.0792869;
    cs.xyz_matrix.m06 =  0.0000000; cs.xyz_matrix.m07 = 0.0451134; cs.xyz_matrix.m08 = 1.0439444;



    return cs;
}

// convert linear to DCI-P3
__DEVICE__ float3 lin_dcip3(float3 rgb) {
    struct DCIP3Curve cv = dcip3_curve();
    return make_float3(DCIP3Curve_lin_dcip3(cv, rgb.x), DCIP3Curve_lin_dcip3(cv, rgb.y), DCIP3Curve_lin_dcip3(cv, rgb.z));
}

// convert DCI-P3 to linear
__DEVICE__ float3 dcip3_lin(float3 rgb) {
    struct DCIP3Curve cv = dcip3_curve();
    return make_float3(DCIP3Curve_dcip3_lin(cv, rgb.x), DCIP3Curve_dcip3_lin(cv, rgb.y), DCIP3Curve_dcip3_lin(cv, rgb.z));
}    

// convert DCI-P3 to xyz
__DEVICE__ float3 xyz_dcip3(float3 rgb) {
    struct DCIP3Colorspace cs = dcip3_colorspace();
    return DCIP3Colorspace_xyz_dcip3(cs, rgb);
}

// convert xyz to DCI-P3
__DEVICE__ float3 dcip3_xyz(float3 rgb) {
    struct DCIP3Colorspace cs = dcip3_colorspace();
    return DCIP3Colorspace_dcip3_xyz(cs, rgb);
}
