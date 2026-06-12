SUMMARY = "Ara-2 NPU runtime (extracted from SDK r2.1)"
DESCRIPTION = "User-space inference proxy, client library, firmware, and \
hardware initialization utilities for the Ara-2 neural processing unit, \
extracted from the full Ara-2 SDK r2.1 archive."

ARA_RT_TAR_PATH ?= "ara2-sdk-r2.1-lic.tar"

SRC_URI[md5sum]    = "e5fb9e7dfbd0bc03a24d32568a76ac86"
SRC_URI[sha256sum] = "3857e5914b70834e7b192e1f9e5764e70fa98cc7c85b1b4f94b5a7a52336fb2b"

# SDK tarball extracts to ara2-sdk-r2.1-lic
S = "${WORKDIR}/ara2-sdk-r2.1-lic"

require ara2-rt.inc
