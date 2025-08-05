====================================
OpenEmbedded/Yocto layer for eIQAuto
====================================

This layer provides support for eIQAuto for use with OpenEmbedded and/or Yocto Project.

Note: The layer uses the eIQAuto release package. For that, the release package archive
must be copied to recipes-runtime/eiqa-runtime-prebuilt/files/eIQAuto_S32N7_PRM_3.13.0.tar.gz
or define EIQA_RUNTIME_PREBUILT_TAR_PATH to be the absolute path to the archive into local.conf.

To manually add meta-eiqa layer to your build run the following command from
within the build directory::

  bitbake-layers add-layer meta-eiqa
