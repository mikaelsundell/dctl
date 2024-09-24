// Copyright 2022-present Contributors to the dctl project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/dctl

// clang-format on

// CineonColor
struct CineonColor
{
    float stop;
    float r;
    float g;
    float b;
};

__CONSTANT__ CineonColor cineon_colors[] = {
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
    {2,  0.90f, 0.50f, 0.25f},
    {3,  0.90f, 0.60f, 0.25f},
    {4,  0.90f, 0.30f, 0.20f},
    {5,  0.90f, 0.35f, 0.30f},
    {6,  0.90f, 0.90f, 0.90f},
    {7,  0.95f, 0.95f, 0.95f},
    {8,  0.99f, 0.99f, 0.99f}
};
#define cineon_stops 17

// Cineon curve
struct CineonCurve
{
    float density;
    float gamma;
    float bitdepth;
    int offset;
    int white;

    __DEVICE__  float steps() {
        return (density / bitdepth);
    }

    __DEVICE__ float3 invert_cineon(float3 rgb, float3 scale, float3 dmin) {
        float3 invert = make_float3(offset, offset, offset);
        invert += scale * log10f3(div3f(dmin, rgb)) / steps();
        invert /= bitdepth;
        return invert;
    }

    __DEVICE__ float3 reverse_cineon(float3 rgb, float3 scale, float3 dmin) {
        float3 reverse = rgb;
        reverse *= bitdepth;
        reverse -= make_float3(offset, offset, offset);
        float3 scaled = reverse * steps() / scale;
        rgb = dmin / pow10f3(scaled);
        return rgb;
    }

    __DEVICE__ float3 lin_cineon(float3 rgb) {
        float scale = steps() / gamma;
        float gain = 1.0 - pow(10.0f, (offset - white) * scale);
        float offset = white / bitdepth;
        rgb = make_float3(offset, offset, offset) + logf3(max((rgb - 1.0f) * gain + 1.0, 1e-7)) / (bitdepth * log(10.0f) * scale);
        return rgb;
    }

    __DEVICE__ float3 cineon_lin(float3 rgb) {
        float scale = steps() / gamma;
        rgb = minf3(rgb, 1.0f) * bitdepth;
        float black = pow(10.0f, offset * scale);
        float diff = pow(10.0f, white * scale) - black;
        float r = pow(10.0f, rgb.x * scale);
        float g = pow(10.0f, rgb.y * scale);
        float b = pow(10.0f, rgb.z * scale);
        rgb = (make_float3(r, g, b) - black) / diff;
        return rgb;
    }
};

__DEVICE__ CineonCurve cineon_curve() {
    CineonCurve cv = { 2.046f, 0.6f, 1023.0f, 95, 685 };
    return cv;
}

// Invert Negative to Cineon
__DEVICE__ float3 invert_cineon(float3 rgb, float3 scale, float3 dmin) {
    CineonCurve cv = cineon_curve();
    return cv.invert_cineon(rgb, scale, dmin);
}

// Reverse Negative to Cineon
__DEVICE__ float3 reverse_cineon(float3 rgb, float3 scale, float3 dmin) {
    CineonCurve cv = cineon_curve();
    return cv.reverse_cineon(rgb, scale, dmin);
}

// Convert Cineon to linear
__DEVICE__ float3 cineon_lin(float3 rgb) {
    CineonCurve cv = cineon_curve();
    return cv.cineon_lin(rgb);
}

// Convert linear to Cineon
__DEVICE__ float3 lin_cineon(float3 rgb) {
    CineonCurve cv = cineon_curve();
    return cv.lin_cineon(rgb);
}
