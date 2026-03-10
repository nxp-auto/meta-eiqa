SUMMARY = "LLM support packagegroup"
DESCRIPTION = "Packagegroup for LLM runtime and dependencies"

LICENSE = "LA_OPT_NXP_Software_License"
LIC_FILES_CHKSUM = "file://${EIQAUTO_LICENSE};md5=8b13b71da2ba9684156478a0800d536a"

inherit packagegroup

RDEPENDS:${PN} = " \
    python3-pip \
    onnxruntime \
    neutron \
"
