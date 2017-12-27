#!/bin/bash
v4l2-ctl -d /dev/video$1 --set-ctrl white_balance_automatic=0
v4l2-ctl -d /dev/video$1 --set-ctrl auto_exposure=1
v4l2-ctl -d /dev/video$1 --set-ctrl exposure=10
v4l2-ctl -d /dev/video$1 --set-ctrl gain_automatic=0
