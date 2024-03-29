# Copyright 2022-present Contributors to the colorpalette project.
# SPDX-License-Identifier: BSD-3-Clause
# https://github.com/mikaelsundell/colorpalette

cmake_minimum_required(VERSION 3.27)
set( project_name "dctl" )

project( "${project_name} project" )

file(GLOB dctl "*.dctl")
install(FILES ${dctl} DESTINATION dctl)
