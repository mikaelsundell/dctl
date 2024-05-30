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
    float lin_logC3(float lin) {
        return ((lin > cut) ? c * log10(a * lin + b) + d : e * lin + f);
    }
    float logC3_lin(float log) {
        float lin = ((log > e * cut + f) ? (pow(10, (log - d) / c) - b) / a : (log - f) / e);
        return fmax(lin, 0.0f); // fmax for non-log negative values
    }
};

__DEVICE__ LogC3Curve logC3_curve(int ei) {
    LogC3Curve curve;
    if (ei == EI160) {
        curve = { 160,  0.005561, 5.555556, 0.080216, 0.269036, 0.381991, 5.842037, 0.092778 };
    } else if (ei == EI200) {
        curve = { 200,  0.006208, 5.555556, 0.076621, 0.266007, 0.382478, 5.776265, 0.092782 };
    } else if (ei == EI250) {
        curve = { 250,  0.006871, 5.555556, 0.072941, 0.262978, 0.382966, 5.710494, 0.092786 };
    } else if (ei == EI320) {
        curve = { 320,  0.007622, 5.555556, 0.068768, 0.259627, 0.383508, 5.637732, 0.092791 };
    } else if (ei == EI400) {
        curve = { 400,  0.008318, 5.555556, 0.064901, 0.256598, 0.383999, 5.571960, 0.092795 };
    } else if (ei == EI500) {
        curve = { 500,  0.009031, 5.555556, 0.060939, 0.253569, 0.384493, 5.506188, 0.092800 };
    } else if (ei == EI640) {
        curve = { 640,  0.009840, 5.555556, 0.056443, 0.250219, 0.385040, 5.433426, 0.092805 };
    } else if (ei == EI800) {
        curve = { 800,  0.010591, 5.555556, 0.052272, 0.247190, 0.385537, 5.367655, 0.092809 };
    } else if (ei == EI1000) {
        curve = { 1000, 0.011361, 5.555556, 0.047996, 0.244161, 0.386036, 5.301883, 0.092814 };
    } else if (ei == EI1280) {
        curve = { 1280, 0.012235, 5.555556, 0.043137, 0.240810, 0.386590, 5.229121, 0.092819 };
    } else if (ei == EI1600) {
        curve = { 1600, 0.013047, 5.555556, 0.038625, 0.237781, 0.387093, 5.163350, 0.092824 };
    }
    return curve;
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
