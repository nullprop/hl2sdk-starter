project(
  'hl2sdk-starter',
  'cpp',
  default_options: [
    'cpp_std=c++17',
  ],
)

cpp = meson.get_compiler('cpp')
compiler_args = []
linker_args = []

compiler = cpp.get_id()
host_system = host_machine.system()
arch = get_option('arch')
buildtype = get_option('buildtype')

# Sanity checks
if compiler != 'gcc' and compiler != 'clang' 
  error('Unsupported compiler "@0@"', compiler)
endif
if host_system != 'linux' and host_system != 'windows'
  error('Unsupported host system system "@0@"', host_system)
endif
if arch != 'x86' and arch != 'x64'
  error('Unsupported arch "@0@"', arch)
endif

# Compiler specific defines
if compiler == 'gcc' or compiler == 'clang'
  compiler_args += [
    '-DGNUC'
  ]
endif

# Warnings
compiler_args += [
  '-Wall',
]
if compiler == 'msvc'
  compiler_args += [
    # '/WX',
  ]
elif compiler == 'gcc'
  compiler_args += [
    # '-Werror',
    '-Wno-overloaded-virtual',
  ]
elif compiler == 'clang'
  compiler_args += [
    # '-Werror',
    '-Wno-overloaded-virtual',
    '-fms-extensions', # narrowing casts
  ]
endif

# Debug/Release target
if buildtype == 'debug'
  compiler_args += [
    '-DDEBUG',
    '-D_DEBUG',
  ]
  if compiler == 'msvc'
    compiler_args += [
      '/Od',
    ]
  elif compiler == 'gcc' or compiler == 'clang'
    compiler_args += [
      '-g',
      '-O0',
    ]
  endif
else
  compiler_args += [
    '-DNDEBUG',
  ]
  if compiler == 'msvc'
    compiler_args += [
      '/O2',
    ]
  elif compiler == 'gcc' or compiler == 'clang'
    compiler_args += [
      '-O3',
    ]
  endif
endif

# OS
if host_system == 'windows'
  compiler_args += [
    '-D_WINDOWS',
  ]
  if arch == 'x86'
    compiler_args += [
      '-DWIN32',
      '-D_WIN32',
    ]
  else
    compiler_args += [
      '-DWIN64',
      '-D_WIN64',
    ]
  endif
elif host_system == 'linux'
  compiler_args += [
    '-DLINUX',
    '-D_LINUX',
    '-DPOSIX',
    '-D_finite=finite',
	'-Dstricmp=strcasecmp',
	'-D_stricmp=strcasecmp',
	'-D_strnicmp=strncasecmp',
	'-Dstrnicmp=strncasecmp',
	'-D_vsnprintf=vsnprintf',
	'-D_alloca=alloca',
	'-Dstrcmpi=strcasecmp',
    '-DNO_MALLOC_OVERRIDE',
    '-msse',
    '-fPIC',
    '-fpermissive',
  ]
  linker_args += [
    '-static-libgcc',
  ]
endif

# CPU architecture
if arch == 'x86'
  if compiler == 'gcc' or compiler == 'clang'
    compiler_args += [
      '-m32',
    ]
    linker_args += [
      '-m32',
    ]
  endif
elif arch == 'x64'
  compiler_args += [
    '-DX64BITS',
    '-DPLATFORM_64BITS',
  ]
  if compiler == 'gcc' or compiler == 'clang'
    compiler_args += [
      '-m64',
    ]
    linker_args += [
      '-m64',
    ]
  endif
endif

# Target specific workarounds
if host_system == 'linux' and buildtype == 'release'
  compiler_args += [
    '-Wno-strict-aliasing',
  ]
endif
if host_system == 'linux' and arch == 'x64'
  compiler_args += [
    # CThreadSpinRWLock() COMPILE_TIME_ASSERT wrong LockInfo_t size
    '-U_DEBUG',
  ]
endif

# Common SDK directories to include
sdk_includes = include_directories([
  'include/hl2sdk/public',
  'include/hl2sdk/public/engine',
  'include/hl2sdk/public/game/server',
  'include/hl2sdk/public/mathlib',
  'include/hl2sdk/public/tier0',
  'include/hl2sdk/public/tier1',
  'include/hl2sdk/public/vstdlib',
])

# SDK libraries
sdk_deps = []
if host_system == 'windows'
  if arch == 'x86'
    dir_x86 = join_paths(meson.current_source_dir(), 'include/hl2sdk/lib/public')
    sdk_deps += [
      cpp.find_library('mathlib', dirs: [dir_x86], required: true),
      cpp.find_library('tier0', dirs: [dir_x86], required: true),
      cpp.find_library('tier1', dirs: [dir_x86], required: true),
      cpp.find_library('vstdlib', dirs: [dir_x86], required: true),
    ]
  elif arch == 'x64'
    dir_x64 = join_paths(meson.current_source_dir(), 'include/hl2sdk/lib/public/win64')
    sdk_deps += [
      cpp.find_library('mathlib', dirs: [dir_x64], required: true),
      cpp.find_library('tier0', dirs: [dir_x64], required: true),
      cpp.find_library('tier1', dirs: [dir_x64], required: true),
      cpp.find_library('vstdlib', dirs: [dir_x64], required: true),
    ]
  endif
elif host_system == 'linux'
  if arch == 'x86'
    dirs_x86 = [
      join_paths(meson.current_source_dir(), 'include/hl2sdk/lib/linux'),
      join_paths(meson.current_source_dir(), 'include/hl2sdk/lib/public/linux32'),
    ]
    sdk_deps += [
      cpp.find_library('mathlib', dirs: [dirs_x86], required: false),
      cpp.find_library('mathlib_i486', dirs: [dirs_x86], required: false),

      cpp.find_library('tier0', dirs: [dirs_x86], required: false),
      cpp.find_library('tier0_i486', dirs: [dirs_x86], required: false),
      cpp.find_library('tier0_srv', dirs: [dirs_x86], required: false),

      cpp.find_library('tier1', dirs: [dirs_x86], required: false),
      cpp.find_library('tier1_i486', dirs: [dirs_x86], required: false),

      cpp.find_library('vstdlib', dirs: [dirs_x86], required: false),
      cpp.find_library('vstdlib_i486', dirs: [dirs_x86], required: false),
      cpp.find_library('vstdlib_srv', dirs: [dirs_x86], required: false),
    ]
  elif arch == 'x64'
    dir_x64 = join_paths(meson.current_source_dir(), 'include/hl2sdk/lib/linux64')
    sdk_deps += [
      cpp.find_library('mathlib', dirs: [dir_x64], required: true),
      cpp.find_library('tier0_srv', dirs: [dir_x64], required: true),
      cpp.find_library('tier1', dirs: [dir_x64], required: true),
      cpp.find_library('vstdlib_srv', dirs: [dir_x64], required: true),
    ]
  endif
endif

add_project_arguments(cpp.get_supported_arguments(compiler_args), language: 'cpp')
add_project_link_arguments(cpp.get_supported_link_arguments(linker_args), language: 'cpp')
add_project_dependencies(sdk_deps, language: 'cpp')

subdir('src')

