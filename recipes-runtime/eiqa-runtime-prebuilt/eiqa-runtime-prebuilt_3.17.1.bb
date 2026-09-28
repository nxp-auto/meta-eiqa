EIQA_RUNTIME_PREBUILT_TAR_PATH ?= "eIQAuto_S32N7_PRM_3.17.1.tar.gz"
EIQA_RUNTIME_PREBUILT_URL ??= ""

require eiqa-runtime-prebuilt-src.inc

SRC_URI[md5sum] = "52838d665e9920e3e9b15ddbe3d19abe"
SRC_URI[sha256sum] = "7d5ab1b012e5f2ac341640f785e1d0d0da2f877baecee35c2ef6f5150020371f"

require eiqa-runtime-prebuilt.inc
