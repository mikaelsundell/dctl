// Copyright 2022-present Contributors to the dctl project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/dctl

// clang-format on

// rec709 curve
struct Rec709Curve
{
    float threshold;
    float slope;
    float exp;
    float scale;
    float offset;
};

__DEVICE__ float Rec709Curve_lin_rec709(struct Rec709Curve cv, float lin) {
    return (lin < cv.threshold) ? cv.slope * lin : cv.scale * pow_f(lin, cv.exp) - cv.offset;
}

__DEVICE__ float Rec709Curve_rec709_lin(struct Rec709Curve cv, float val) {
    return (val < cv.offset * cv.slope) ? val / cv.slope : pow_f((val + cv.offset) / cv.scale, 1.0 / cv.exp);
}

// rec709 colorspace
struct Rec709Colorspace
{
    struct Matrix rec709_matrix;
    struct Matrix xyz_matrix;
};

__DEVICE__ float3 Rec709Colorspace_xyz_rec709(struct Rec709Colorspace cs, float3 xyz) {
    return mult_matrix(xyz, cs.rec709_matrix);
}
__DEVICE__ float3 Rec709Colorspace_rec709_xyz(struct Rec709Colorspace cs, float3 rec709) {
    return mult_matrix(rec709, cs.xyz_matrix);
}

__DEVICE__ struct Rec709Curve rec709_curve(int ei) {
    struct Rec709Curve cv;
    cv.threshold = 0.018;
    cv.slope = 4.5;
    cv.exp = 0.45;
    cv.scale = 1.099;
    cv.offset = 0.099;
    return cv;
}

__DEVICE__ struct Rec709Colorspace rec709_colorspace() {
    struct Rec709Colorspace cs;
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

// convert linear to Rec709
__DEVICE__ float3 lin_rec709(float3 rgb, int ei) {
    struct Rec709Curve cv = rec709_curve(ei);
    return make_float3(Rec709Curve_lin_rec709(cv, rgb.x), Rec709Curve_lin_rec709(cv, rgb.y), Rec709Curve_lin_rec709(cv, rgb.z));
}

// convert Rec709 to linear
__DEVICE__ float3 rec709_lin(float3 rgb, int ei) {
    struct Rec709Curve cv = rec709_curve(ei);
    return make_float3(Rec709Curve_rec709_lin(cv, rgb.x), Rec709Curve_rec709_lin(cv, rgb.y), Rec709Curve_rec709_lin(cv, rgb.z));
}    

// convert Rec709 to xyz
__DEVICE__ float3 xyz_rec709(float3 rgb) {
    struct Rec709Colorspace cs = rec709_colorspace();
    float3 rec709 = Rec709Colorspace_xyz_rec709(cs, rgb);
    return rec709;
}

// convert xyz to Rec709
__DEVICE__ float3 rec709_xyz(float3 rgb) {
    struct Rec709Colorspace cs = rec709_colorspace();
    return Rec709Colorspace_rec709_xyz(cs, rgb);
}    