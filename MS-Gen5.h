// Copyright 2022-present Contributors to the dctl project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/dctl

// clang-format on

// Gen5 curve
struct Gen5Curve
{
    float a;
    float b;
    float c;
    float d;
    float e;
    float lin_cut;
    float log_cut;

    __DEVICE__ float lin_gen5(float lin) {
        return ((lin >= lin_cut) ? a * log(lin + b) + c : d * lin + e);
    }
    __DEVICE__ float gen5_lin(float log) {
        return ((log >= log_cut) ? exp((log - c) / a) - b : (log - e) / d);
    }
};

// Gen5 colorspace
struct Gen5Colorspace
{
    Matrix gen5_matrix;
    Matrix xyz_matrix;

    __DEVICE__ float3 xyz_gen5(float3 xyz) {
        return mult_matrix(xyz, gen5_matrix);
    }
    __DEVICE__ float3 gen5_xyz(float3 gen5) {
        return mult_matrix(gen5, xyz_matrix);
    }
};

__DEVICE__ Gen5Curve gen5_curve() {
    Gen5Curve cv;
    cv.a = 0.08692876065491224; cv.b = 0.005494072432257808; cv.c = 0.5300133392291939; cv.d = 8.283605932402494; cv.e = 0.09246575342465753; cv.lin_cut = 0.005; cv.log_cut = cv.d * cv.lin_cut + cv.e;
    return cv;
}

__DEVICE__ Gen5Colorspace gen5_colorspace() {
    Gen5Colorspace cs;
    cs.gen5_matrix = {1.866382, -0.518397, -0.234610, -0.600342, 1.378149, 0.176732, 0.002452, 0.086400, 0.836943}; 
    cs.xyz_matrix = {0.606530, 0.220408, 0.123479, 0.267989, 0.832731, -0.100720, -0.029442, -0.086611, 1.204861}; 
    return cs;
}

// Convert linear to Gen5
__DEVICE__ float3 lin_gen5(float3 rgb) {
    Gen5Curve cv = gen5_curve();
    return make_float3(cv.lin_gen5(rgb.x), cv.lin_gen5(rgb.y), cv.lin_gen5(rgb.z));
}

// Convert Gen5 to linear
__DEVICE__ float3 gen5_lin(float3 rgb) {
    Gen5Curve cv = gen5_curve();
    return make_float3(cv.gen5_lin(rgb.x), cv.gen5_lin(rgb.y), cv.gen5_lin(rgb.z));
}    

// Convert Gen5 to xyz
__DEVICE__ float3 xyz_gen5(float3 rgb) {
    Gen5Colorspace cs = gen5_colorspace();
    return cs.xyz_gen5(rgb);
}

// Convert XYZ to Gen5
__DEVICE__ float3 gen5_xyz(float3 rgb) {
    Gen5Colorspace cs = gen5_colorspace();
    return cs.gen5_xyz(rgb);
}    
