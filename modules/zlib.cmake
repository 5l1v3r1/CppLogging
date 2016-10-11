if(NOT TARGET zlib)

  # Module configuration
  include(CheckTypeSize)
  include(CheckFunctionExists)
  include(CheckIncludeFile)
  include(CheckCSourceCompiles)
  check_include_file(sys/types.h HAVE_SYS_TYPES_H)
  check_include_file(stdint.h HAVE_STDINT_H)
  check_include_file(stddef.h HAVE_STDDEF_H)
  set(CMAKE_REQUIRED_DEFINITIONS -D_LARGEFILE64_SOURCE=1)
  if(HAVE_SYS_TYPES_H)
    list(APPEND CMAKE_REQUIRED_DEFINITIONS -DHAVE_SYS_TYPES_H)
  endif()
  if(HAVE_STDINT_H)
    list(APPEND CMAKE_REQUIRED_DEFINITIONS -DHAVE_STDINT_H)
  endif()
  if(HAVE_STDDEF_H)
    list(APPEND CMAKE_REQUIRED_DEFINITIONS -DHAVE_STDDEF_H)
  endif()
  check_type_size(off64_t OFF64_T)
  if(HAVE_OFF64_T)
    add_definitions(-D_LARGEFILE64_SOURCE=1)
  endif()
  set(CMAKE_REQUIRED_DEFINITIONS)
  check_function_exists(fseeko HAVE_FSEEKO)
  if(NOT HAVE_FSEEKO)
    add_definitions(-DNO_FSEEKO)
  endif()
  check_include_file(unistd.h Z_HAVE_UNISTD_H)

  # Module definitions
  if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
    add_definitions(-D_CRT_NONSTDC_NO_DEPRECATE)
  endif()

  # Module assembler files
  if(CMAKE_COMPILER_IS_GNUCC)
    add_definitions(-DASMV)
    set(ASSEMBLER_FILES "zlib/contrib/amd64/amd64-match.S")
    set_source_files_properties(${ASSEMBLER_FILES} PROPERTIES LANGUAGE C COMPILE_FLAGS -DNO_UNDERLINE)
  elseif(MSVC)
    ENABLE_LANGUAGE(ASM_MASM)
    add_definitions(-DASMV -DASMINF)
    set(ASSEMBLER_FILES "zlib/contrib/masmx64/gvmat64.asm" "zlib/contrib/masmx64/inffasx64.asm")
  endif()

  # Module library
  file(GLOB SOURCE_FILES "zlib/*.c")
  if(CMAKE_MAKE_PROGRAM MATCHES "(MSBuild|devenv|msdev|nmake)")
    # C4127: conditional expression is constant
    # C4131: 'function' : uses old-style declarator
    # C4210: nonstandard extension used : function given file scope
    # C4244: 'conversion' conversion from 'type1' to 'type2', possible loss of data
    set(${SOURCE_FILES} "zlib/contrib/masmx64/inffas8664.c" "zlib/contrib/masmx64/inffas8664.c")
    set_source_files_properties(${SOURCE_FILES} PROPERTIES COMPILE_FLAGS "${COMMON_COMPILE_FLAGS} /wd4127 /wd4131 /wd4210 /wd4244")
  else()
    set_source_files_properties(${SOURCE_FILES} PROPERTIES COMPILE_FLAGS "${COMMON_COMPILE_FLAGS}")
  endif()
  add_library(zlib ${SOURCE_FILES} ${ASSEMBLER_FILES})
  target_link_libraries(zlib)

  # Module folder
  set_target_properties(zlib PROPERTIES FOLDER modules/zlib)

endif()
