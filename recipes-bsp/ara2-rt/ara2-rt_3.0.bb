SUMMARY = "Ara-2 NPU runtime "
DESCRIPTION = "User-space inference proxy, client library, firmware, and \
hardware initialization utilities for the Ara-2 neural processing unit"

ARA_RT_TAR_PATH ?= "ara2-rt-r3.0.tar.gz"

SRC_URI[md5sum]    = "7cb42e1ab686730c918cca3b3149683d"
SRC_URI[sha256sum] = "5bc81318d6ad08dc928b88bedbc42632c58dc90a7b948ae44e6fe66da8d8a603"

S = "${WORKDIR}/ara2-rt-r3.0"

require ara2-rt.inc
