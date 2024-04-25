project(
  'hl2sdk-starter',
  'cpp',
  default_options: [
    'cpp_std=c++20',
  ],
)

cpp = meson.get_compiler('cpp')
compiler_args = []
linker_args = []

compiler = cpp.get_id()
host_system = host_machine.system()
arch = get_option('arch')
buildtype = get_option('buildtype')

if compiler == 'msvc'
elif compiler == 'gcc'
  compiler_args += [
    '-DGNUC'
  ]
else
  error('Unsupported compiler "@0@"', compiler)
endif

# Warnings
compiler_args += [
  '-Wall',
  '-Werror',
  '-Wno-overloaded-virtual',
]

# Debug/Release target
if buildtype == 'debug'
  compiler_args += [
    '-DDEBUG',
    '-D_DEBUG',
    '-g',
    '-O0',
  ]
else
  compiler_args += [
    '-DNDEBUG',
    '-O3',
  ]
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
  ]
  linker_args += [
    '-static-libgcc',
  ]
else
  error('Unsupported host system system "@0@"', host_system)
endif

# CPU architecture
if arch == 'x86'
  compiler_args += [
    '-m32',
  ]
  linker_args += [
    '-m32',
  ]
elif arch == 'x64'
  compiler_args += [
    '-m64',
    '-DX64BITS',
    '-DPLATFORM_64BITS',
  ]
  linker_args += [
    '-m64',
  ]
else
  error('Unsupported arch "@0@"', arch)
endif

# Engine defines
compiler_args += [
  '-DSE_EPISODEONE=1',
  '-DSE_DARKMESSIAH=2',
  '-DSE_ORANGEBOX=3',
  '-DSE_BLOODYGOODTIME=4',
  '-DSE_EYE=5',
  '-DSE_CSS=6',
  '-DSE_HL2DM=7',
  '-DSE_DODS=8',
  '-DSE_SDK2013=9',
  '-DSE_BMS=10',
  '-DSE_TF2=11',
  '-DSE_LEFT4DEAD=12',
  '-DSE_NUCLEARDAWN=13',
  '-DSE_CONTAGION=14',
  '-DSE_LEFT4DEAD2=15',
  '-DSE_ALIENSWARM=16',
  '-DSE_PORTAL2=17',
  '-DSE_BLADE=18',
  '-DSE_INSURGENCY=19',
  '-DSE_DOI=20',
  '-DSE_CSGO=21',
  '-DSE_DOTA=22',
]

engine = get_option('engine')

# Selected engine defines
if engine == 'episodeone'
  compiler_args += ['-DSOURCE_ENGINE=1']
elif engine == 'darkmessiah'
  compiler_args += ['-DSOURCE_ENGINE=2']
elif engine == 'orangebox'
  compiler_args += ['-DSOURCE_ENGINE=3']
elif engine == 'bloodygoodtime'
  compiler_args += ['-DSOURCE_ENGINE=4']
elif engine == 'eye'
  compiler_args += ['-DSOURCE_ENGINE=5']
elif engine == 'css'
  compiler_args += ['-DSOURCE_ENGINE=6']
elif engine == 'hl2dm'
  compiler_args += ['-DSOURCE_ENGINE=7']
elif engine == 'dods'
  compiler_args += ['-DSOURCE_ENGINE=8']
elif engine == 'sdk2013'
  compiler_args += ['-DSOURCE_ENGINE=9']
elif engine == 'bms'
  compiler_args += ['-DSOURCE_ENGINE=10']
elif engine == 'tf2'
  compiler_args += ['-DSOURCE_ENGINE=11']
elif engine == 'left4dead'
  compiler_args += ['-DSOURCE_ENGINE=12']
elif engine == 'nucleardawn'
  compiler_args += ['-DSOURCE_ENGINE=13']
elif engine == 'contagion'
  compiler_args += ['-DSOURCE_ENGINE=14']
elif engine == 'left4dead2'
  compiler_args += ['-DSOURCE_ENGINE=15']
elif engine == 'alienswarm'
  compiler_args += ['-DSOURCE_ENGINE=16']
elif engine == 'portal2'
  compiler_args += ['-DSOURCE_ENGINE=17']
elif engine == 'blade'
  compiler_args += ['-DSOURCE_ENGINE=18']
elif engine == 'insurgency'
  compiler_args += ['-DSOURCE_ENGINE=19']
elif engine == 'doi'
  compiler_args += ['-DSOURCE_ENGINE=20']
elif engine == 'csgo'
  compiler_args += ['-DSOURCE_ENGINE=21']
elif engine == 'dota'
  compiler_args += ['-DSOURCE_ENGINE=22']
else
  error('Unsupported engine "@0@"', engine)
endif

# Target specific workarounds
if host_system == 'linux' and buildtype == 'release'
  compiler_args += [
    '-Wno-strict-aliasing',
  ]
endif
if host_system == 'linux' and arch == 'x64'
  compiler_args += [
    '-fpermissive',
    # CThreadSpinRWLock() COMPILE_TIME_ASSERT wrong LockInfo_t size
    '-U_DEBUG',
  ]
endif

# Common SDK directories to include
sdk_includes = include_directories([
  'include/hl2sdk/public',
  'include/hl2sdk/public/engine',
  'include/hl2sdk/public/game/client',
  'include/hl2sdk/public/game/server',
  'include/hl2sdk/public/tier0',
  'include/hl2sdk/public/tier1',
  'include/hl2sdk/public/tier2',
  'include/hl2sdk/public/tier3',
])

# SDK libraries
sdk_deps = []
if host_system == 'windows'
  if arch == 'x86'
    dir_x86 = join_paths(meson.current_source_dir(), 'include/hl2sdk/lib/linux')
    sdk_deps += [
      cpp.find_library('mathlib', dirs: [dir_x86], required: true),
      cpp.find_library('tier0', dirs: [dir_x86], required: true),
      cpp.find_library('tier1', dirs: [dir_x86], required: true),
      cpp.find_library('tier2', dirs: [dir_x86], required: true),
      cpp.find_library('tier3', dirs: [dir_x86], required: true),
      cpp.find_library('vstdlib', dirs: [dir_x86], required: true),
    ]
  elif arch == 'x64'
    dir_x64 = join_paths(meson.current_source_dir(), 'include/hl2sdk/lib/linux64')
    sdk_deps += [
      cpp.find_library('mathlib', dirs: [dir_x64], required: true),
      cpp.find_library('tier0', dirs: [dir_x64], required: true),
      cpp.find_library('tier1', dirs: [dir_x64], required: true),
      cpp.find_library('vstdlib', dirs: [dir_x64], required: true),
    ]
  else
    error('Unsupported host system "@0@" and arch "@1@" for libraries')
  endif
elif host_system == 'linux'
  if arch == 'x86'
    dir_x86 = join_paths(meson.current_source_dir(), 'include/hl2sdk/lib/linux')
    sdk_deps += [
      cpp.find_library('libtier0_srv', dirs: [dir_x86], required: true),
      cpp.find_library('libvstdlib_srv', dirs: [dir_x86], required: true),
      cpp.find_library('mathlib_i486', dirs: [dir_x86], required: true),
      cpp.find_library('tier1_i486', dirs: [dir_x86], required: true),
      cpp.find_library('tier2_i486', dirs: [dir_x86], required: true),
      cpp.find_library('tier3_i486', dirs: [dir_x86], required: true),
    ]
  elif arch == 'x64'
    dir_x64 = join_paths(meson.current_source_dir(), 'include/hl2sdk/lib/linux64')
    sdk_deps += [
      cpp.find_library('libtier0_srv', dirs: [dir_x64], required: true),
      cpp.find_library('libvstdlib_srv', dirs: [dir_x64], required: true),
      cpp.find_library('mathlib', dirs: [dir_x64], required: true),
      cpp.find_library('tier1', dirs: [dir_x64], required: true),
    ]
  else
    error('Unsupported host system "@0@" and arch "@1@" for libraries')
  endif
else
  error('Unsupported host system "@0@" and arch "@1@" for libraries')
endif

add_project_arguments(cpp.get_supported_arguments(compiler_args), language: 'cpp')
add_project_link_arguments(cpp.get_supported_link_arguments(linker_args), language: 'cpp')
add_project_dependencies(sdk_deps, language: 'cpp')

subdir('src')

