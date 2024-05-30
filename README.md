Readme for dctl
====================

[![License](https://img.shields.io/badge/license-BSD%203--Clause-blue.svg?style=flat-square)](https://github.com/mikaelsundell/icloud-snapshot/blob/master/license.md)

Table of Contents
=================

- [Readme for dctl](#readme-for-dctl)
- [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Installation and utils](#installation-and-utils)
- [DCTLs](#dctls)
  - [Cineon color processing](#cineon-color-processing)
    - [MS-Cineon-Exposure.dctl](#ms-cineon-exposuredctl)
    - [MS-Cineon-Invert.dctl](#ms-cineon-invertdctl)
    - [MS-Cineon-Transform.dctl](#ms-cineon-transformdctl)
  - [LogC3 color processing](#logc3-color-processing)
    - [MS-LogC3-Print.dctl](#ms-logc3-printdctl)
  - [MS-LogC3-Exposure.dctl](#ms-logc3-exposuredctl)
    - [MS-LogC3-Transform.dctl](#ms-logc3-transformdctl)
  - [Utility DCTLs](#utility-dctls)
    - [MS-Stripify.dctl](#ms-stripifydctl)
    - [MS-Saturation.dctl](#ms-saturationdctl)
  - [DCTLs from other projects](#dctls-from-other-projects)
    - [Film Grain.dctl](#film-graindctl)
    - [Printer Lights.dctl](#printer-lightsdctl)
    - [TetraInterp.dctl](#tetrainterpdctl)
    - [TetraInterpHSV.dctl](#tetrainterphsvdctl)
  - [ARRI LogC3 EI800 reference chart](#arri-logc3-ei800-reference-chart)
  - [References](#references)
  - [Web Resources](#web-resources)

Introduction
---------

A collection of continuously updated DCTLs (DaVinci Color Transform Language), primarily aimed at enhancing workflows using ARRI LogC3 in DaVinci Resolve. These DCTLs are  designed for photographers and cinematographers seeking a photographic approach to color correction and grading.
  
Installation and utils
---------

To use these tools into your DaVinci Resolve setup, begin by cloning the git repository, which contains the DCTLs and headers.

Run `./build.sh` in your terminal to copy the `*.dctl` and `*.h` files to the DaVinci Resolve LUT DCTL folder, ensuring they're accessible within your Resolve environment. The files can also be manually copied to `/Library/Application Support/Blackmagic Design/DaVinci Resolve/LUT/DCTL`

For added convenience, the open.sh script is provided, enabling easy access to various resources:

**To open the DCTL readme documentation, use:**

```shell
./run.sh readme
````

**For exploring DCTL examples, execute:**

```shell
./run.sh examples
````

**To access the DaVinci Resolve log file and initiate a trace, input:**

```shell
./run.sh log
````

**To make a snapshot of hte DaVinvi Resolve DCTL folder, input:**

```shell
./run.sh snapshot
````

# DCTLs

## Cineon color processing

### MS-Cineon-Exposure.dctl

![MS-LogC3-Cineon figure](resources/MS-Cineon-Exposure.png "MS-Cineon-Exposure")

Cineon exposure from photographic stops, incorporating a false color to aid in achieving correct exposure levels.

- https://github.com/mikaelsundell/dctl/blob/master/MS-Cineon-Exposure.dctl

### MS-Cineon-Invert.dctl

![MS-LogC3-Exposure figure](resources/MS-Cineon-Invert.png "MS-LogC3-Invert")

Cineon negative inversion from dmin ratios with adjustable controls for density, bitdepth, offset and scale. Dmin values can either be specified manually or samples using sampler rectangle from border or other dmin base.

- https://github.com/mikaelsundell/dctl/blob/master/MS-Cineon-Invert.dctl



### MS-Cineon-Transform.dctl

Cineon conversion to and from linear. 

- https://github.com/mikaelsundell/dctl/blob/master/MS-Cineon-Transform.dctl


## LogC3 color processing

### MS-LogC3-Print.dctl

![MS-LogC3-Cineon figure](resources/MS-LogC3-Print.png "MS-Cineon-Exposure")

Made for print emulation, this DCTL applies DaVinci Resolve's built-in film looks to ARRI LogC3 footage with adjustable controls for contrast and color strength.

- https://github.com/mikaelsundell/dctl/blob/master/MS-LogC3-Print.dctl


## MS-LogC3-Exposure.dctl

![MS-LogC3-Exposure figure](resources/MS-LogC3-Exposure.png "MS-LogC3-Exposure")

LogC3 exposure from photographic stops, incorporating a false color to aid in achieving correct exposure levels.

- https://github.com/mikaelsundell/dctl/blob/master/MS-LogC3-Exposure.dctl

### MS-LogC3-Transform.dctl

LogC3 conversion to and from linear. 

- https://github.com/mikaelsundell/dctl/blob/master/MS-Cineon-Transform.dctl


## Utility DCTLs

### MS-Stripify.dctl

Matrix adjustments, this DCTL simplifies the color palette by push colors into a warm/ cool strip.

- https://github.com/mikaelsundell/dctl/blob/master/MS-Stripify.dctl

### MS-Saturation.dctl

HSV-based adjustments, this DCTL provides a tool for fine-tuning saturation using saturation in HSV.

- https://github.com/mikaelsundell/dctl/blob/master/MS-Saturation.dctl

## DCTLs from other projects

### Film Grain.dctl

- https://github.com/thatcherfreeman/utility-dctls

### Printer Lights.dctl

- https://github.com/thatcherfreeman/utility-dctls

### TetraInterp.dctl

- Copyright © 2021 calvinsilly, Ember Light, Nick Eason

### TetraInterpHSV.dctl

- Copyright © 2021 calvinsilly, Ember Light, Nick Eason

## ARRI LogC3 EI800 reference chart

ARRI LogC3 EI800 EXR

- [logctool_ei800_3840x2160.exr](resources/logctool_ei800_3840x2160.exr)

Logctool project:

- https://github.com/mikaelsundell/logctool


References
---------

ARRI Companion to DI
* https://dicomp.arri.de/digital/digital_systems/DIcompanion/index.html
  
Blend modes:
* https://skia.googlesource.com/skia/+/70e432e72745/gm/hsl.cpp

Cineon conversion in RV:
* https://github.com/AcademySoftwareFoundation/OpenRV/blob/main/src/plugins/rv-packages/additional_nodes/LinearToCineonLog.glsl
* https://github.com/AcademySoftwareFoundation/OpenRV/blob/main/src/plugins/rv-packages/additional_nodes/CineonLogToLinear.glsl

Grayscale legacy luma:
* https://en.wikipedia.org/wiki/Grayscale


 Web Resources
-------------

* GitHub page:        https://github.com/mikaelsundell/dctl
* Issues              https://github.com/mikaelsundell/dctl/issues
