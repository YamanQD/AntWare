project('antware', 'cpp',
    license: 'GPL-3.0-or-later',
    version: '1.0.0',
    default_options: ['warning_level=3','default_library=static'])

zlib_dep = dependency('zlib')
glm_dep = dependency('glm')
glew_dep = dependency('glew')

if host_machine.system() == 'linux'
    glu_dep = dependency('glu')
    sfml_dep = dependency('sfml-all')
    assimp_dep = dependency('assimp')
elif host_machine.system() == 'windows'
    rapidjson_dep = dependency('rapidjson')
    cmake = import('cmake')
    compiler = meson.get_compiler('cpp')
    
    glu_dep = compiler.find_library('glu32')

    if target_machine.cpu_family() == 'x86'
        sfml_dep = dependency('sfml_win32')
    elif target_machine.cpu_family() == 'x86_64'
        sfml_dep = dependency('sfml_win64')
    endif

    assimp_opt = cmake.subproject_options()
    assimp_opt.add_cmake_defines({
        'BUILD_SHARED_LIBS': false,
        'CMAKE_BUILD_TYPE': get_option('buildtype') == 'debug' ? 'Debug' : 'Release',
        'ASSIMP_BUILD_ASSIMP_TOOLS': false,
        'ASSIMP_BUILD_TESTS': false,
        'ASSIMP_BUILD_ZLIB': false,

        'ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT': false,
        'ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT': false,

        'ASSIMP_BUILD_GLB_IMPORTER': true,
        'ASSIMP_BUILD_OBJ_IMPORTER': true,
        'ASSIMP_BUILD_GLTF_IMPORTER': true,
    })
    assimp_dep = cmake.subproject('assimp', options: assimp_opt).dependency('assimp')
endif

src_assembler = run_command('src_assembler.py')
sources = src_assembler.stdout().strip().split('\n')


if host_machine.system() == 'windows'
executable('antware', sources,
    win_subsystem: 'windows',
    override_options: ['cpp_std=c++17'],
    include_directories: ['include'],
    dependencies: [sfml_dep, glew_dep, glm_dep, glu_dep, rapidjson_dep, zlib_dep, assimp_dep])
elif host_machine.system() == 'linux'
executable('antware', sources,
    override_options: ['cpp_std=c++17'],
    include_directories: ['include'],
    dependencies: [sfml_dep, glew_dep, glm_dep, glu_dep, zlib_dep, assimp_dep])
endif