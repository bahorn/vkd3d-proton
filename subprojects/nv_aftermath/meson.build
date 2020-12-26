project('nv-aftermath', ['c'], version: '0.0', meson_version : '>= 0.49')

nv_aftermath_compiler       = meson.get_compiler('c')
nv_aftermath_c_std          = 'c99'
nv_aftermath_warning_level  = '2'
nv_aftermath_platform       = target_machine.system()

# So we include the correct files.
if target_machine.cpu_family() == 'x86'
  arch = 'x86'
elif target_machine.cpu_family() == 'x86_64'
  arch = 'x64'
else
  error('Unsupported Architecture')
endif

add_project_arguments(nv_aftermath_compiler.get_supported_arguments([
    '-fvisibility=hidden',
    '-Wno-format',
    '-Wno-missing-field-initializers',
    '-Wno-unused-parameter',
    '-Wdeclaration-after-statement',
    '/wd4244', # Narrowing conversion
    '/wd4101', # Unreferenced local variable
    '/wd4267', # Another narrowing conversion
    '/wd4996', # Secure no warnings
    '/wd4334', # Result of 32-bit shift cast to 64-bit
    '/wd4146', # Unary minus on unsigned
    '/wd4305', # Truncation from double to float
    ]),
  language : 'c')


if nv_aftermath_platform == 'linux'
  nv_aftermath_include_dirs = include_directories([
    './external/linux/include'
  ])
elif nv_aftermath_platform == 'windows'
  nv_aftermath_include_dirs = include_directories([
    './external/windows/include'
  ])
else
  error('Unknown platform')
endif

nv_aftermath_src = [
  'src/nv_aftermath.c',
]


prebuilt_deps = []

if nv_aftermath_platform == 'windows'
  llvm_version = '7_0_1'

  aftermath_prebuilt = declare_dependency(
      dependencies : [
        nv_aftermath_compiler.find_library('GFSDK_Aftermath_Lib.'
          + arch,
          dirs :[
            meson.current_source_dir() + '/external/windows/lib/' + arch
          ]
        ),
        nv_aftermath_compiler.find_library('llvm_' + llvm_version,
          dirs : [
            meson.current_source_dir() + '/external/windows/lib/' + arch
          ])
      ],
      include_directories: 'external/windows/include'
    )

elif nv_aftermath_platform == 'linux'
  aftermath_prebuilt = declare_dependency(
      dependencies : nv_aftermath_compiler.find_library('GFSDK_Aftermath_Lib.'
        + arch,
        dirs :[
          meson.current_source_dir() + '/external/linux/lib/' + arch
        ]
      ),
      include_directories: 'external/linux/include'
    )
endif


prebuilt_deps = [aftermath_prebuilt]

nv_aftermath_lib = static_library(
  'nv-aftermath',
  nv_aftermath_src,
  include_directories : nv_aftermath_include_dirs,
  dependencies        : [ prebuilt_deps ]
)

nv_aftermath_dep = declare_dependency(
  include_directories : include_directories('./include'),
  link_with           : [ nv_aftermath_lib ],
  dependencies        : [ prebuilt_deps ])
