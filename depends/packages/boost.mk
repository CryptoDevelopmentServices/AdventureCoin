package=boost
$(package)_version=1_74_0

# Primary (stable) CDN mirror
$(package)_download_path=https://archives.boost.io/release/1.74.0/source/

# Secondary fallback (JFrog)
$(package)_download_path_1=https://boostorg.jfrog.io/artifactory/main/release/1.74.0/source/

# Tertiary fallback (Bitcoin Core mirror — may not host this version but harmless)
$(package)_download_path_2=https://bitcoincore.org/depends-sources/

$(package)_file_name=boost_1_74_0.tar.bz2
$(package)_sha256_hash=83bfc1507731a0906e387fc28b7ef5417d591429e51e788417fe9ff025e116b1

###### FETCH COMMANDS — TRY ALL MIRRORS ######
define $(package)_fetch_cmds
  $(call fetch_file,$(package),$(package)_download_path,$($(package)_file_name),$($(package)_sha256_hash)) || \
  $(call fetch_file,$(package),$(package)_download_path_1,$($(package)_file_name),$($(package)_sha256_hash)) || \
  $(call fetch_file,$(package),$(package)_download_path_2,$($(package)_file_name),$($(package)_sha256_hash))
endef

###### CONFIG + BUILD SETTINGS ######

define $(package)_set_vars
$(package)_config_opts_release=variant=release
$(package)_config_opts_debug=variant=debug

$(package)_config_opts=--layout=tagged --build-type=complete --user-config=user-config.jam
$(package)_config_opts+=threading=multi link=static -sNO_BZIP2=1 -sNO_ZLIB=1

# Linux
$(package)_config_opts_linux=threadapi=pthread runtime-link=shared

# macOS cross-compile
$(package)_config_opts_darwin=threadapi=pthread runtime-link=shared

# Windows (MinGW)
$(package)_config_opts_mingw32=binary-format=pe target-os=windows threadapi=win32 runtime-link=static
$(package)_config_opts_x86_64_mingw32=address-model=64
$(package)_config_opts_i686_mingw32=address-model=32

# Linux 32-bit
$(package)_config_opts_i686_linux=address-model=32 architecture=x86

# Toolsets
$(package)_toolset_linux=gcc
boost_toolset_linux=$($(package)_toolset_linux)
$(package)_archiver_linux=$($(package)_ar)
boost_archiver_linux=$($(package)_archiver_linux)

$(package)_toolset_darwin=clang
boost_toolset_darwin=$($(package)_toolset_darwin)
$(package)_archiver_darwin=$($(package)_libtool)
boost_archiver_darwin=$($(package)_archiver_darwin)

$(package)_toolset_mingw32=gcc
boost_toolset_mingw32=$($(package)_toolset_mingw32)
$(package)_archiver_mingw32=$($(package)_ar)
boost_archiver_mingw32=$($(package)_archiver_mingw32)

# Libraries (NO Boost.Test)
$(package)_config_libraries=chrono,filesystem,program_options,system,thread

# Flags
$(package)_cxxflags=-std=c++11 -fvisibility=hidden
$(package)_cxxflags_linux=-fPIC
endef

###### PREPROCESS ######
define $(package)_preprocess_cmds
  echo "using $(boost_toolset_$(host_os)) : : $($(package)_cxx) : <cxxflags>\"$($(package)_cxxflags) $($(package)_cppflags)\" <linkflags>\"$($(package)_ldflags)\" <archiver>\"$(boost_archiver_$(host_os))\" <striper>\"$(host_STRIP)\"  <ranlib>\"$(host_RANLIB)\" <rc>\"$(host_WINDRES)\" : ;" > user-config.jam
endef

###### CONFIG ######
define $(package)_config_cmds
  ./bootstrap.sh --without-icu --with-libraries=$(boost_config_libraries)
endef

###### BUILD ######
define $(package)_build_cmds
  ./b2 -d2 -j2 -d1 --prefix=$($(package)_staging_prefix_dir) $($(package)_config_opts) stage
endef

###### INSTALL ######
define $(package)_stage_cmds
  ./b2 -d0 -j4 --prefix=$($(package)_staging_prefix_dir) $($(package)_config_opts) install
endef
