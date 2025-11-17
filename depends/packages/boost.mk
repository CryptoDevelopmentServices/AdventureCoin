package=boost
$(package)_version=1_74_0
$(package)_download_path=https://archives.boost.io/release/1.74.0/source/
$(package)_file_name=boost_1_74_0.tar.bz2
$(package)_sha256_hash=83bfc1507731a0906e387fc28b7ef5417d591429e51e788417fe9ff025e116b1

define $(package)_set_vars
$(package)_config_opts_release=variant=release
$(package)_config_opts_debug=variant=debug
$(package)_config_opts=--layout=tagged --build-type=complete --user-config=user-config.jam
$(package)_config_opts+=threading=multi link=static -sNO_BZIP2=1 -sNO_ZLIB=1

# Per-platform build options
$(package)_config_opts_linux=threadapi=pthread runtime-link=shared
$(package)_config_opts_darwin=threadapi=pthread runtime-link=shared
$(package)_config_opts_mingw32=binary-format=pe target-os=windows threadapi=win32 runtime-link=static
$(package)_config_opts_x86_64_mingw32=address-model=64
$(package)_config_opts_i686_mingw32=address-model=32
$(package)_config_opts_i686_linux=address-model=32 architecture=x86

# C++ flags
$(package)_cxxflags=-std=c++11 -fvisibility=hidden
$(package)_cxxflags_linux=-fPIC

# Libraries we actually need (no Boost.Test here)
$(package)_config_libraries=chrono,filesystem,program_options,system,thread
endef

# 🔥 Critical bit: generate a VALID user-config.jam for ALL hosts
define $(package)_preprocess_cmds
  case "$(host_os)" in \
    darwin)  TOOLSET="darwin"; ARCHIVER="$($(package)_libtool)";; \
    mingw32) TOOLSET="gcc";    ARCHIVER="$($(package)_ar)";; \
    *)       TOOLSET="gcc";    ARCHIVER="$($(package)_ar)";; \
  esac; \
  echo "using $${TOOLSET} : : $($(package)_cxx) : <cxxflags>\"$($(package)_cxxflags) $($(package)_cppflags)\" <linkflags>\"$($(package)_ldflags)\" <archiver>\"$${ARCHIVER}\" <striper>\"$(host_STRIP)\" <ranlib>\"$(host_RANLIB)\" <rc>\"$(host_WINDRES)\" ;" > user-config.jam
endef

define $(package)_config_cmds
  ./bootstrap.sh --without-icu --with-libraries=$(boost_config_libraries)
endef

define $(package)_build_cmds
  ./b2 -d2 -j2 -d1 --prefix=$($(package)_staging_prefix_dir) $($(package)_config_opts) stage
endef

define $(package)_stage_cmds
  ./b2 -d0 -j4 --prefix=$($(package)_staging_prefix_dir) $($(package)_config_opts) install
endef
