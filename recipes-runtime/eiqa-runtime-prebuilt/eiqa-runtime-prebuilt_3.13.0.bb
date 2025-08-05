EIQA_RUNTIME_PREBUILT_TAR_PATH ?= "eIQAuto_S32N7_PRM_3.13.0.tar.gz"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI = "file://${EIQA_RUNTIME_PREBUILT_TAR_PATH}"
SRC_URI[MD5SUM] = "4fbe122a06e39b520daac862ae23855d"
SRC_URI[SHA1SUM] = "d3abf9957015a1584f9a38cdfb9fbb063cf5ad5d"

require eiqa-runtime-prebuilt.inc
