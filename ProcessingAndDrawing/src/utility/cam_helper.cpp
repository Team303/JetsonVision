#include "cam_helper.hpp"

void flash_settings (int device, const CameraSettings &settings) {
    char setting_script[1000];

    //create system call to use v4l2 to change camera settings according
    //to data in CameraSettings struct
    sprintf (setting_script, 
        "v4l2-ctl -d /dev/video%d  "
            "--set-ctrl white_balance_automatic=%d "
            "--set-ctrl auto_exposure=%d "
            "--set-ctrl exposure=%d "
            "--set-ctrl gain_automatic=%d ",
        device, 
        settings.white_balance_automatic,
        settings.auto_exposure,
        settings.exposure,
        settings.gain_automatic);

    //run the system call created in the above step
    system (setting_script);
}
