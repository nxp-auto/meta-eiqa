SUMMARY = "Ara-2 NPU runtime packagegroup"
DESCRIPTION = "Packagegroup for the Ara-2 PCIe NPU runtime and integration components"

LICENSE = "LA_OPT_NXP_Software_License"
LIC_FILES_CHKSUM = "file://${EIQAUTO_LICENSE};md5=8b13b71da2ba9684156478a0800d536a"

inherit packagegroup

RDEPENDS:${PN} = " \
    ara2-rt \
    ara2-rt-nnapp \
    ara2-rt-utils \
    ara2-rt-python \
    optimum-ara \
    eiq-aaf-connector \
"
