// Copyright 2022-present Contributors to the dctl project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/dctl

// clang-format on

// Rec709 curve
struct Rec709Curve
{
    const float threshold = 0.018;
    const float slope = 4.5;
    const float exp = 0.45;
    const float scale = 1.099;
    const float offset = 0.099;

    // Convert linear to Rec. 709 gamma-encoded value
    __DEVICE__ float lin_rec709(float lin) {
        return (lin < threshold) ? slope * lin : scale * pow(lin, exp) - offset;
    }

    // Convert Rec. 709 gamma-encoded value to linear
    __DEVICE__ float rec709_lin(float val) {
        return (val < offset * slope) ? val / slope : pow((val + offset) / scale, 1.0 / exp);
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
    return cv;
}

__DEVICE__ Rec709Colorspace rec709_colorspace() {
    Rec709Colorspace cs;
    cs.rec709_matrix = {3.2406, -1.5372, -0.4986, -0.9689, 1.8758, 0.0415, 0.0557, -0.2040, 1.0570}; 
    cs.xyz_matrix = {0.4124, 0.3576, 0.1805, 0.2126, 0.7152, 0.0722, 0.0193, 0.1192, 0.9505}; 
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
    rec709.x = clamp(rec709.x, 0.0, 1.0);
    rec709.y = clamp(rec709.y, 0.0, 1.0);
    rec709.z = clamp(rec709.z, 0.0, 1.0);
    return rec709;
}

// Convert xyz to Rec709
__DEVICE__ float3 rec709_xyz(float3 rgb) {
    Rec709Colorspace cs = rec709_colorspace();
    return cs.rec709_xyz(rgb);
}    
