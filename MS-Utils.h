// Copyright 2022-present Contributors to the colorpicker project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/dctl

// clang-format on

// matrix
typedef struct {
    float m00, m01, m02;
    float m03, m04, m05;
    float m06, m07, m08;
} Matrix;

// Multiply float3 by matrix
__DEVICE__ float3 multiply_matrix(float3 value, Matrix mat) {
    float3 result = make_float3(
        mat.m00 * value.x + mat.m01 * value.y + mat.m02 * value.z,
        mat.m03 * value.x + mat.m04 * value.y + mat.m05 * value.z,
        mat.m06 * value.x + mat.m07 * value.y + mat.m08 * value.z
    );
    return result;
}

// Convert HSV to RGB
__DEVICE__ float3 hsv_rgb(float3 hsv) {
    float hue = hsv.x;
    float sat = hsv.y;
    float val = hsv.z;

    hue = _fmod(hue + 360.0, 360.0);

    float c = val * sat;
    float x = c * (1.0 - _fabs(_fmod(hue / 60.0, 2.0) - 1.0));
    float m = val - c;
    float3 rgbp = make_float3(0.0, 0.0, 0.0);
    if (0.0 <= hue && hue < 60.0) {
        rgbp = make_float3(c, x, 0.0);
    } else if (60.0 <= hue && hue < 120.0) {
        rgbp = make_float3(x, c, 0.0);
    } else if (120.0 <= hue && hue < 180.0) {
        rgbp = make_float3(0.0, c, x);
    } else if (180.0 <= hue && hue < 240.0) {
        rgbp = make_float3(0.0, x, c);
    } else if (240.0 <= hue && hue < 300.0) {
        rgbp = make_float3(x, 0.0, c);
    } else if (300.0 < hue && hue < 360.0) {
        rgbp = make_float3(c, 0.0, x);
    }
    return rgbp + m;
}

// Convert RGB to HSV
__DEVICE__ float3 rgb_hsv(float3 rgb) {
    float r = rgb.x;
    float g = rgb.y;
    float b = rgb.z;
    float c_max = _fmaxf(_fmaxf(r, g), b);
    float c_min = _fminf(_fminf(r, g), b);
    float delta = c_max - c_min;

    float H;
    if (delta == 0.0f) {
        H = 0.0f;
    } else if (r >= g && r >= b) {
        H = _fmod((g - b) / delta + 6.0f, (6.0f));
    } else if (g >= r && g >= b) {
        H = (b - r) / delta + (2.0f);
    } else {
        // b >= r && b >= g
        H = (r - g) / delta + 4.0f;
    }
    H = H / 6.0f;
    float S;
    if (c_max == 0.0f) {
        S = 0.0f;
    } else {
        S = delta / c_max;
    }
    float V = c_max;
    float3 color = make_float3(H * 360.0, S, V);
    return color;
}

// Convert HSL to RGB
__DEVICE__ float3 hsl_rgb(float3 hsl) {
    float h = hsl.x / 360.0f; // Convert h to [0, 1] range
    float s = hsl.y;
    float l = hsl.z;

    float c = (1.0f - _fabs(2.0f * l - 1.0f)) * s;
    float x = c * (1.0f - _fabs(_fmod(h * 6.0f, 2.0f) - 1.0f));
    float m = l - c / 2.0f;
    float3 rgb = make_float3(0.0f, 0.0f, 0.0f);

    if (0.0f <= h && h < 1.0f/6.0f) {
        rgb = make_float3(c, x, 0.0f);
    } else if (1.0f/6.0f <= h && h < 2.0f/6.0f) {
        rgb = make_float3(x, c, 0.0f);
    } else if (2.0f/6.0f <= h && h < 3.0f/6.0f) {
        rgb = make_float3(0.0f, c, x);
    } else if (3.0f/6.0f <= h && h < 4.0f/6.0f) {
        rgb = make_float3(0.0f, x, c);
    } else if (4.0f/6.0f <= h && h < 5.0f/6.0f) {
        rgb = make_float3(x, 0.0f, c);
    } else if (5.0f/6.0f <= h && h < 1.0f) {
        rgb = make_float3(c, 0.0f, x);
    }

    rgb += m;
    return rgb;
}

// Convert RGB to HSL
__DEVICE__ float3 rgb_hsl(float3 rgb) {
    float r = rgb.x;
    float g = rgb.y;
    float b = rgb.z;
    float max = _fmaxf(_fmaxf(r, g), b);
    float min = _fminf(_fminf(r, g), b);
    float h, s, l;
    l = (max + min) / 2.0f;

    float delta = max - min;

    if (delta == 0) {
        h = s = 0; // achromatic
    } else {
        s = l > 0.5f ? delta / (2.0f - max - min) : delta / (max + min);

        if (max == r) {
            h = (g - b) / delta + (g < b ? 6.0f : 0);
        } else if (max == g) {
            h = (b - r) / delta + 2.0f;
        } else {
            h = (r - g) / delta + 4.0f;
        }
        h /= 6.0f;
    }
    return make_float3(h * 360.0f, s, l); // H in [0, 360], S and L in [0, 1]
}

// Calculate grayscale from RGB
__DEVICE__ float grayscale(float r, float g, float b)
{ 
    float grayscale = r * 0.30f + g * 0.59f + b * 0.11f;
    return grayscale;
}

// Calculate grayscale from RGB
__DEVICE__ float3 set_grayscale(float r, float g, float b, float l)
{
    float diff = l - grayscale(r, g, b);
    float3 result = make_float3(r + diff, g + diff, b + diff);
    return result;
}

// Calculate luma from RGB
__DEVICE__ float luma(float3 rgb)
{
    float luma = 0.2126 * rgb.x + 0.7152 * rgb.y + 0.0722 * rgb.z;
    return luma;
}
