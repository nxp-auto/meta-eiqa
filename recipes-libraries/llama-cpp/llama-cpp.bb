SUMMARY = "llama.cpp"
DESCRIPTION = "LLM inference in C/C++"

SRCREV = "42401c72b8d239240ed0fb37694d29ac33b3bc4f"

S = "${WORKDIR}/git"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${S}/LICENSE;md5=223b26b3c1143120c87e2b13111d3e99"

SRC_URI = "\
    git://github.com/ggml-org/llama.cpp.git;protocol=https;branch=master \
"

DEPENDS = " openssl"

CPU_ARM_ARCH = ""
CPU_ARM_ARCH:s32n79sim = "armv8.2-a+dotprod+fp16"
CPU_ARM_ARCH:s32n79rdb = "armv8.2-a+dotprod+fp16"
CPU_ARM_ARCH:append = "${@bb.utils.contains('TUNE_FEATURES', 'crypto', '+crypto', '', d)}"

inherit cmake

EXTRA_OECMAKE = "\
    -DCMAKE_BUILD_TYPE=Release \
    -DFETCHCONTENT_FULLY_DISCONNECTED=OFF \
    -DGGML_CPU_KLEIDIAI=ON \
    -DGGML_CPU_ARM_ARCH=${CPU_ARM_ARCH} \
"

FILES:${PN} += "\
    ${bindir}/* \
"

FILES:${PN}-dev += "\
    ${includedir}/* \
"

INHIBIT_PACKAGE_DEBUG_SPLIT = "1"
