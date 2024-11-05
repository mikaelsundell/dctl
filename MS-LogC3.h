// Copyright 2022-present Contributors to the dctl project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/dctl

// clang-format on

// LogC3Color
struct LogC3Color
{
    float stop;
    float r;
    float g;
    float b;
};

__CONSTANT__ LogC3Color logC3_colors[] = {
    {-8, 0.01f, 0.01f, 0.01f},
    {-7, 0.05f, 0.05f, 0.05f},
    {-6, 0.10f, 0.10f, 0.10f},
    {-5, 0.40f, 0.25f, 0.60f},
    {-4, 0.20f, 0.45f, 0.70f},
    {-3, 0.40f, 0.60f, 0.95f},
    {-2, 0.40f, 0.60f, 0.25f},
    {-1, 0.60f, 0.90f, 0.55f},
    {0,  0.50f, 0.50f, 0.50f},
    {1,  1.00f, 0.95f, 0.25f},
    {2,  0.90f, 0.60f, 0.25f},
    {3,  0.90f, 0.50f, 0.25f},
    {4,  0.90f, 0.35f, 0.30f},
    {5,  0.90f, 0.30f, 0.20f},
    {6,  0.90f, 0.90f, 0.90f},
    {7,  0.95f, 0.95f, 0.95f},
    {8,  0.99f, 0.99f, 0.99f}
};
#define logC3_stops 17

// LogC3 curve
struct LogC3Curve
{
    int ei;
    float cut;
    float a;
    float b;
    float c;
    float d;
    float e;
    float f;

    __DEVICE__ float lin_logC3(float lin) {
        return ((lin > cut) ? c * log10(a * lin + b) + d : e * lin + f);
    }
    __DEVICE__ float logC3_lin(float log) {
        float lin = ((log > e * cut + f) ? (pow(10, (log - d) / c) - b) / a : (log - f) / e);
        return lin;
    }
};

// LogC3 colorspace
struct LogC3Colorspace
{
    Matrix logC3_matrix;
    Matrix xyz_matrix;

    __DEVICE__ float3 xyz_logC3(float3 xyz) {
        return mult_matrix(xyz, logC3_matrix);
    }
    __DEVICE__ float3 logC3_xyz(float3 logC3) {
        return mult_matrix(logC3, xyz_matrix);
    }
};

__DEVICE__ LogC3Curve logC3_curve(int ei) {
    LogC3Curve cv;
    if (ei == EI160) {
        cv.ei = 160; cv.cut = 0.005561; cv.a = 5.555556; cv.b = 0.080216; cv.c = 0.269036; cv.d = 0.381991; cv.e = 5.842037; cv.f = 0.092778;
    } else if (ei == EI200) {
        cv.ei = 200; cv.cut = 0.006208; cv.a = 5.555556; cv.b = 0.076621; cv.c = 0.266007; cv.d = 0.382478; cv.e = 5.776265; cv.f = 0.092782;
    } else if (ei == EI250) {
        cv.ei = 250; cv.cut = 0.006871; cv.a = 5.555556; cv.b = 0.072941; cv.c = 0.262978; cv.d = 0.382966; cv.e = 5.710494; cv.f = 0.092786;
    } else if (ei == EI320) {
        cv.ei = 320; cv.cut = 0.007622; cv.a = 5.555556; cv.b = 0.068768; cv.c = 0.259627; cv.d = 0.383508; cv.e = 5.637732; cv.f = 0.092791;
    } else if (ei == EI400) {
        cv.ei = 400; cv.cut = 0.008318; cv.a = 5.555556; cv.b = 0.064901; cv.c = 0.256598; cv.d = 0.383999; cv.e = 5.571960; cv.f = 0.092795;
    } else if (ei == EI500) {
        cv.ei = 500; cv.cut = 0.009031; cv.a = 5.555556; cv.b = 0.060939; cv.c = 0.253569; cv.d = 0.384493; cv.e = 5.506188; cv.f = 0.092800;
    } else if (ei == EI640) {
        cv.ei = 640; cv.cut = 0.009840; cv.a = 5.555556; cv.b = 0.056443; cv.c = 0.250219; cv.d = 0.385040; cv.e = 5.433426; cv.f = 0.092805;
    } else if (ei == EI800) {
        cv.ei = 800; cv.cut = 0.010591; cv.a = 5.555556; cv.b = 0.052272; cv.c = 0.247190; cv.d = 0.385537; cv.e = 5.367655; cv.f = 0.092809;
    } else if (ei == EI1000) {
        cv.ei = 1000; cv.cut = 0.011361; cv.a = 5.555556; cv.b = 0.047996; cv.c = 0.244161; cv.d = 0.386036; cv.e = 5.301883; cv.f = 0.092814;
    } else if (ei == EI1280) {
        cv.ei = 1280; cv.cut = 0.012235; cv.a = 5.555556; cv.b = 0.043137; cv.c = 0.240810; cv.d = 0.386590; cv.e = 5.229121; cv.f = 0.092819;
    } else if (ei == EI1600) {
        cv.ei = 1600; cv.cut = 0.013047; cv.a = 5.555556; cv.b = 0.038625; cv.c = 0.237781; cv.d = 0.387093; cv.e = 5.163350; cv.f = 0.092824;
    }
    return cv;
}

__DEVICE__ LogC3Colorspace logC3_colorspace() {
    LogC3Colorspace cs;
    // logC3 matrix
    cs.logC3_matrix.m00 = 1.789066; cs.logC3_matrix.m01 = -0.482534; cs.logC3_matrix.m02 = -0.200076;
    cs.logC3_matrix.m03 = -0.639849; cs.logC3_matrix.m04 = 1.396400; cs.logC3_matrix.m05 = 0.194432;
    cs.logC3_matrix.m06 = -0.041532; cs.logC3_matrix.m07 = 0.082335; cs.logC3_matrix.m08 = 0.878868;
    // xyz matrix
    cs.xyz_matrix.m00 = 0.638008; cs.xyz_matrix.m01 = 0.214704; cs.xyz_matrix.m02 = 0.097744;
    cs.xyz_matrix.m03 = 0.291954; cs.xyz_matrix.m04 = 0.823841; cs.xyz_matrix.m05 = -0.115795;
    cs.xyz_matrix.m06 = 0.002798; cs.xyz_matrix.m07 = -0.067034; cs.xyz_matrix.m08 = 1.153294;
    return cs;
}

// Convert linear to LogC3
__DEVICE__ float3 lin_logC3(float3 rgb, int ei) {
    LogC3Curve cv = logC3_curve(ei);
    return make_float3(cv.lin_logC3(rgb.x), cv.lin_logC3(rgb.y), cv.lin_logC3(rgb.z));
}

// Convert LogC3 to linear
__DEVICE__ float3 logC3_lin(float3 rgb, int ei) {
    LogC3Curve cv = logC3_curve(ei);
    return make_float3(cv.logC3_lin(rgb.x), cv.logC3_lin(rgb.y), cv.logC3_lin(rgb.z));
}    

// Convert LogC3 to xyz
__DEVICE__ float3 xyz_logC3(float3 rgb) {
    LogC3Colorspace cs = logC3_colorspace();
    return cs.xyz_logC3(rgb);
}

// Convert XYZ to LogC3
__DEVICE__ float3 logC3_xyz(float3 rgb) {
    LogC3Colorspace cs = logC3_colorspace();
    return cs.logC3_xyz(rgb);
}    
