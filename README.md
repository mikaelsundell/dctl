Readme for dctl
====================

[![License](https://img.shields.io/badge/license-BSD%203--Clause-blue.svg?style=flat-square)](https://github.com/mikaelsundell/icloud-snapshot/blob/master/license.md)

  
Introduction
---------

This collection consists of continuously updated DCTL (DaVinci Resolve Custom Tool) scripts, primarily aimed at enhancing workflows using ARRI LogC in DaVinci Resolve. These scripts are  designed for photographers and cinematographers seeking a gentle touch photographic approach to color correction and grading.
  
Installation and utils
---------

To use these tools into your DaVinci Resolve setup, begin by cloning the git repository, which contains the DCTL scripts and utilities.

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

Dctls
---------

## MS-LogC3-Exposure.dctl

![MS-LogC3-Exposure figure](resources/MS-LogC3-Exposure.png 'MS-LogC3-Exposure')

This script is crafted for precise exposure adjustments within LogC3 footage, incorporating a False Color feature to aid in achieving optimal exposure levels.

## MS-LogC3-Print.dctl

![MS-LogC3-Exposure figure](resources/MS-LogC3-Print.png 'S-LogC3-Exposure')

Made for print emulation, this DCTL applies DaVinci Resolve's built-in film looks to LogC3 footage with adjustable controls for contrast and color strength.

## MS-Saturation

Focusing on HSV-based adjustments, this script provides a tool for fine-tuning saturation.

## DCTLs from other projects ##

TetraInterp.dctl
* Copyright (c) 2021 calvinsilly, Ember Light, Nick Eason

TetraInterpHSV.dctl
* Copyright (c) 2021 calvinsilly, Ember Light, Nick Eason

## LogC3 EI800 reference chart

The LogC3 reference chart is created using the logctool command:

* https://github.com/mikaelsundell/logctool

ARRI LogC3 EI800 EXR:

* [logctool_ei800_3840x2160.exr](resources/logctool_ei800_3840x2160.exr)

Documentation
---------

Blend modes, used in MS-LogC3-Print.dctl
* https://skia.googlesource.com/skia/+/70e432e72745/gm/hsl.cpp

Grayscale legacy luma 
* https://en.wikipedia.org/wiki/Grayscale


 Web Resources
-------------

* GitHub page:        https://github.com/mikaelsundell/dctl
* Issues              https://github.com/mikaelsundell/dctl/issues
