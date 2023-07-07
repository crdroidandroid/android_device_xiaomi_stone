#
# FPC1020 Touch sensor driver
#
# Copyright (c) 2013,2014 Fingerprint Cards AB <tech@fingerprints.com>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License Version 2
# as published by the Free Software Foundation.
#

device.internal = 1

keyboard.layout = uinput-fpc
keyboard.builtIn = 1
keyboard.orientationAware = 1

touch.deviceType = touchScreen
touch.orientationAware = 1
touch.filter.level = 0
touch.size.calibration = diameter
touch.size.scale = 1
touch.size.bias = 0
touch.size.isSummed = 0
touch.gestureMode = pointer
touch.pressure.calibration = physical
touch.pressure.scale = 0.00000125
touch.distance.calibration = none
