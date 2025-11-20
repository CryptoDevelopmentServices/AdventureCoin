package=libevent
$(package)_version=2.1.12-stable
$(package)_download_path=https://github.com/libevent/libevent/releases/download/release-$($(package)_version)/
$(package)_file_name=libevent-$($(package)_version).tar.gz
$(package)_sha256_hash=92e6de1be9ec176428fd2367677e61ceffc2ee1cb119035037a27d346b0403bb

define $(package)_preprocess_cmds
  ./autogen.sh
endef

define $(package)_set_vars
  $(package)_config_opts= \
    --disable-shared \
    --disable-openssl \
    --disable-libevent-regress \
    --disable-samples \
    --enable-static

  $(package)_config_opts_release=--disable-debug-mode
  $(package)_config_opts_linux=--with-pic

  # macOS cross-compile requires manual override of configure tests
  $(package)_config_opts_darwin= \
    ac_cv_prog_cc_c_works=yes \
    ac_cv_c_compiler_gnu=yes \
    ac_cv_func_malloc_0_nonnull=yes \
    ac_cv_func_realloc_0_nonnull=yes \
    CC="$(host_CC)" \
    CXX="$(host_CXX)" \
    AR="$(host_AR)" \
    RANLIB="$(host_RANLIB)" \
    STRIP="$(host_STRIP)"
endef

define $(package)_config_cmds
  ./configure \
    --host=$(host) \
    --build=$(build) \
    --prefix=$($(package)_staging_prefix_dir) \
    $($(package)_config_opts) \
    $($(package)_config_opts_$(host_os))
endef

define $(package)_build_cmds
  $(MAKE)
endef

define $(package)_stage_cmds
  $(MAKE) DESTDIR=$($(package)_staging_dir) install
endef
