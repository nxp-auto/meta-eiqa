EIQA_RUNTIME_PREBUILT_TAR_PATH ?= "eIQAuto_S32N7_PRM_3.14.0.tar.gz"
EIQA_RUNTIME_PREBUILT_URL ??= ""

require eiqa-runtime-prebuilt-src.inc

SRC_URI[md5sum] = "949787814c897d2c72287d61d4a2dff4"
SRC_URI[sha256sum] = "9e60591dc2931e2bd0f497004d861af053586a6552ec44dbd3b5a8c186a02801"

require eiqa-runtime-prebuilt.inc
