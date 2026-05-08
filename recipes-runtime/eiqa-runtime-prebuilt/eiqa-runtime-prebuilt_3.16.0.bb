EIQA_RUNTIME_PREBUILT_TAR_PATH ?= "eIQAuto_S32N7_PRM_3.16.0.tar.gz"
EIQA_RUNTIME_PREBUILT_URL ??= ""

require eiqa-runtime-prebuilt-src.inc

SRC_URI[md5sum] = "1574756692d3af0086c23b674f6b0145"
SRC_URI[sha256sum] = "73af4c218286e45eef418b1dae393dee3f5c76e700c4cb6f28a0f2b7b53309d5"

require eiqa-runtime-prebuilt.inc
