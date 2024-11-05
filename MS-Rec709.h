// Copyright 2022-present Contributors to the dctl project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/dctl

// clang-format on

// Rec709 curve
struct Rec709Curve
{
    float threshold;
    float slope;
    float exp;
    float scale;
    float offset;

    __DEVICE__ float lin_rec709(float lin) {
        return (lin < threshold) ? slope * lin : scale * pow(lin, exp) - offset;
    }

    __DEVICE__ float rec709_lin(float val) {
        return (val < offset * slope) ? val / slope : _powf((val + offset) / scale, 1.0 / exp);
    }
};

// Rec709 colorspace
struct Rec709Colorspace
{
    Matrix rec709_matrix;
    Matrix xyz_matrix;

    __DEVICE__ float3 xyz_rec709(float3 xyz) {
        return mult_matrix(xyz, rec709_matrix);
    }
    __DEVICE__ float3 rec709_xyz(float3 rec709) {
        return mult_matrix(rec709, xyz_matrix);
    }
};

__DEVICE__ Rec709Curve rec709_curve(int ei) {
    Rec709Curve cv;
    cv.threshold = 0.018;
    cv.slope = 4.5;
    cv.exp = 0.45;
    cv.scale = 1.099;
    cv.offset = 0.099;
    return cv;
}

__DEVICE__ Rec709Colorspace rec709_colorspace() {
    Rec709Colorspace cs;
     // rec709 matrix
    cs.rec709_matrix.m00 = 3.2406; cs.rec709_matrix.m01 = -1.5372; cs.rec709_matrix.m02 = -0.4986;
    cs.rec709_matrix.m03 = -0.9689; cs.rec709_matrix.m04 = 1.8758; cs.rec709_matrix.m05 = 0.0415;
    cs.rec709_matrix.m06 = 0.0557; cs.rec709_matrix.m07 = -0.2040; cs.rec709_matrix.m08 = 1.0570;
    // xyz matrix
    cs.xyz_matrix.m00 = 0.4124; cs.xyz_matrix.m01 = 0.3576; cs.xyz_matrix.m02 = 0.1805;
    cs.xyz_matrix.m03 = 0.2126; cs.xyz_matrix.m04 = 0.7152; cs.xyz_matrix.m05 = 0.0722;
    cs.xyz_matrix.m06 = 0.0193; cs.xyz_matrix.m07 = 0.1192; cs.xyz_matrix.m08 = 0.9505;
    return cs;
}

// Convert linear to Rec709
__DEVICE__ float3 lin_rec709(float3 rgb, int ei) {
    Rec709Curve cv = rec709_curve(ei);
    return make_float3(cv.lin_rec709(rgb.x), cv.lin_rec709(rgb.y), cv.lin_rec709(rgb.z));
}

// Convert Rec709 to linear
__DEVICE__ float3 rec709_lin(float3 rgb, int ei) {
    Rec709Curve cv = rec709_curve(ei);
    return make_float3(cv.rec709_lin(rgb.x), cv.rec709_lin(rgb.y), cv.rec709_lin(rgb.z));
}    

// Convert Rec709 to xyz
__DEVICE__ float3 xyz_rec709(float3 rgb) {
    Rec709Colorspace cs = rec709_colorspace();
    float3 rec709 = cs.xyz_rec709(rgb);
    return rec709;
}

// Convert xyz to Rec709
__DEVICE__ float3 rec709_xyz(float3 rgb) {
    Rec709Colorspace cs = rec709_colorspace();
    return cs.rec709_xyz(rgb);
}    
