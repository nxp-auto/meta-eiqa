====================================
OpenEmbedded/Yocto layer for eIQAuto
====================================

This layer provides support for eIQAuto for use with OpenEmbedded and/or Yocto Project.

Note: The layer uses the eIQAuto release package, which can be provided either by setting
EIQA_RUNTIME_PREBUILT_URL in local.conf to a download link, copying the archive to
recipes-runtime/eiqa-runtime-prebuilt/files/eIQAuto_S32N7_PRM_3.13.0.tar.gz, or defining
EIQA_RUNTIME_PREBUILT_TAR_PATH in local.conf with the absolute path to the archive.

To manually add meta-eiqa layer to your build run the following command from
within the build directory::

  bitbake-layers add-layer meta-eiqa
