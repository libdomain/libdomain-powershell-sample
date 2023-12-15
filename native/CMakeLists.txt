cmake_minimum_required(VERSION 3.5)

project(domain_wrapper LANGUAGES C)

if(UNIX)
  include(GNUInstallDirs)
else()
    message(FATAL_ERROR "System not UNIX - not implemented yet")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(FindLdap)
include(FindLibdomain)

find_package(Ldap REQUIRED)
find_package(Libdomain REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(Talloc REQUIRED IMPORTED_TARGET talloc)
pkg_check_modules(Libverto REQUIRED IMPORTED_TARGET libverto)
pkg_check_modules(Libconfig REQUIRED IMPORTED_TARGET libconfig)

add_library(domain_wrapper SHARED main.c)

target_link_libraries(domain_wrapper domain)

target_link_libraries(domain_wrapper Ldap::Ldap)
target_link_libraries(domain_wrapper Libdomain::Libdomain)
target_link_libraries(domain_wrapper PkgConfig::Libverto)
target_link_libraries(domain_wrapper PkgConfig::Libconfig)
target_link_libraries(domain_wrapper PkgConfig::Talloc)

install(TARGETS domain_wrapper DESTINATION ${CMAKE_INSTALL_BINDIR})

add_subdirectory(test)
