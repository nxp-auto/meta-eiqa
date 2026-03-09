FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

EIQA_PROVIDER ?= ""
NEUTRON_SRC ?= ""

python __anonymous() {
    import os

    url = d.getVar("NEUTRON_SDK_URL")
    archive = d.getVar("NEUTRON_SDK_ARCHIVE_PATH")

    def is_empty(v):
        return (v is None) or (v.strip() == "")

    # Resolve SRC_URI (URL, abs path, relative path, or "")
    src_uri = ""
    if not is_empty(url):
        src_uri = url
    elif os.path.isabs(archive) and os.path.exists(archive):
        src_uri = "file://" + archive
    else:
        # Relative path inside FILESEXTRAPATHS
        paths = (d.getVar("FILESEXTRAPATHS") or "").split(":")
        for p in paths:
            candidate = os.path.join(p, archive)
            if os.path.exists(candidate):
                src_uri = "file://" + candidate
                break

    if src_uri:
        d.appendVar("SRC_URI", " " + src_uri)

    # Determine if eiqa provider is required
    need_provider = is_empty(src_uri)
    d.setVar("EIQA_PROVIDER", "1" if need_provider else "0")

    if need_provider:
        neutron_src = d.expand("${RECIPE_SYSROOT}${datadir}/neutron")
    else:
        neutron_src = d.expand("${WORKDIR}")

    d.setVar("NEUTRON_SRC", neutron_src)
}
