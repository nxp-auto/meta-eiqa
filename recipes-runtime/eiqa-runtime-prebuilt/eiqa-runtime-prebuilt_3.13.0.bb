EIQA_RUNTIME_PREBUILT_TAR_PATH ?= "eIQAuto_S32N7_PRM_3.13.0.tar.gz"
EIQA_RUNTIME_PREBUILT_URL ??= ""

require eiqa-runtime-prebuilt-src.inc

SRC_URI[md5sum] = "ef79b933ce7c368365c6982634153c34"
SRC_URI[sha256sum] = "36046d856d76c8a573d9d5ba40c0fc1b6693f92e45ac991d104839b2e92d2d8c"

require eiqa-runtime-prebuilt.inc
