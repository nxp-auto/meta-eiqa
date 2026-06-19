NEUTRON_SDK_ARCHIVE_PATH ??= "eiq-neutron-sdk-linux-3.1.3.zip"
NEUTRON_SDK_URL ??= ""

require neutron-src.inc

SRC_URI[md5sum] = "0128d5942f91bd257ede8060c4f4655d"
SRC_URI[sha256sum] = "675309772778dcb15a6dabc76df408ed1090f327bf4e201a6a666e883294f7b4"

require neutron.inc
