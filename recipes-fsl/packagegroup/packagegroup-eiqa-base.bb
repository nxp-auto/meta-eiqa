SUMMARY = "eIQAuto support packagegroup"
DESCRIPTION = "Base packagegroup for eIQAuto runtime components"

LICENSE = "LA_OPT_NXP_Software_License"
LIC_FILES_CHKSUM = "file://${EIQAUTO_LICENSE};md5=8b13b71da2ba9684156478a0800d536a"

inherit packagegroup

RDEPENDS:${PN} = " \
    eiqa-runtime-prebuilt \
    neutron-firmware \
"
