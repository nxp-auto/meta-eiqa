NEUTRON_SDK_ARCHIVE_PATH ??= "eiq-neutron-sdk-linux-3.0.1.zip"
NEUTRON_SDK_URL ??= ""

require neutron-src.inc

SRC_URI[md5sum] = "bee31af6b8fcf4f90b694aff301726c9"
SRC_URI[sha256sum] = "e4876e36f4c961876d6e9745c1b9d1d0aa3091ce6f26092d0b32a6cac86f8e46"

require neutron.inc
