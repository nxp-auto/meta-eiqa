EIQA_RUNTIME_PREBUILT_TAR_PATH ?= "eIQAuto_S32N7_PRM_3.15.0.tar.gz"
EIQA_RUNTIME_PREBUILT_URL ??= ""

require eiqa-runtime-prebuilt-src.inc

SRC_URI[md5sum] = "9e3ae5aa65422de0240ae459171a8e05"
SRC_URI[sha256sum] = "aaa46cb03f5b39af5dcc4c0040af8ccf5e7b7bebaabfee92bfa004e802f22b79"

require eiqa-runtime-prebuilt.inc
