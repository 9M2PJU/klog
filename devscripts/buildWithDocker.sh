#!/bin/bashcd /root/klog
qmake KLog.pro -spec linux-g++ CONFIG+=release && make -j$(nproc)
