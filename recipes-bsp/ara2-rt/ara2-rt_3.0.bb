SUMMARY = "Ara-2 NPU runtime "
DESCRIPTION = "User-space inference proxy, client library, firmware, and \
hardware initialization utilities for the Ara-2 neural processing unit"

ARA_RT_TAR_PATH ?= "arart-r3.0.tar.gz"

SRC_URI[md5sum]    = "b89ffeec4c72bcdd7e19b0cc24940500"
SRC_URI[sha256sum] = "4bf2f1849e7bccdecffa845e25e637941942c24183895ae340e30f93c3f3dca4"

S = "${WORKDIR}/arart-r3.0/arart-r3.0-aarch64"

require ara2-rt.inc
