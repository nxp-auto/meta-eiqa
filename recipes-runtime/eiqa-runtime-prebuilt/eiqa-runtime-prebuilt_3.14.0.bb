EIQA_RUNTIME_PREBUILT_TAR_PATH ?= "eIQAuto_S32N7_PRM_3.14.0_CD.tar.gz"
EIQA_RUNTIME_PREBUILT_URL ??= ""

require eiqa-runtime-prebuilt-src.inc

SRC_URI[md5sum] = "767d6bc5825f876bded401eae2f0c1e7"
SRC_URI[sha256sum] = "b697ede7ed5dbb1768e49e756bd6aecc056ec54b473fdf46f6ee21df6f56e8bd"

require eiqa-runtime-prebuilt.inc
