#!/bin/bash
v4l2-ctl -d /dev/video$1 --set-ctrl white_balance_automatic=1 
v4l2-ctl -d /dev/video$1 --set-ctrl auto_exposure=0
v4l2-ctl -d /dev/video$1 --set-ctrl exposure=60 
v4l2-ctl -d /dev/video$1 --set-ctrl gain_automatic=1
