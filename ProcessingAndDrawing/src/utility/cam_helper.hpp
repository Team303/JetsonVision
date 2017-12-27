/*
Helper utilities for interacting with camera settings
*/

#ifndef CAM_HELPER_HPP
#define CAM_HELPER_HPP

#include <stdlib.h>
#include <stdio.h>
using namespace std;

/**
 * struct to hold camera setting information
 * can be passed to flash_settings function to flash usb cam settings with
 * video4linux. Comparator operators implement to easily check if stored camera
 * settings match those requested over networktables. Use v4l2-ctl -L command
 * to see which settings are available on your particular camera and what the
 * ranges are, you may need to modify this struct to match your camera.
 */
struct CameraSettings {

    int white_balance_automatic=0;
    int auto_exposure=1;
    int exposure=30;
    int gain_automatic=0;

};

inline bool operator== (const CameraSettings &s1,const CameraSettings &s2) {
    return
	s1.white_balance_automatic == s2.white_balance_automatic &&
	s1.auto_exposure == s2.auto_exposure &&
	s1.exposure == s2.exposure &&
	s1.gain_automatic == s2.gain_automatic;
}

inline bool operator!= (const CameraSettings &s1,const CameraSettings &s2) {
    return !(s1 == s2);
}

/**
 * flashes camera settings stored in struct to specified device
 * @param device video input to flash settings, usually 0 or 1. Check which 
 *  device your camera is on with ls /dev/video*
 * @param settings camera settings to be flashed
 */
void flash_settings (int device, const CameraSettings &settings);

#endif
