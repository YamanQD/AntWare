project('antware', 'cpp',
    license: 'GPL-3.0-or-later',
    version: '1.0.0',
    default_options: ['warning_level=3','default_library=static'])

cmake = import('cmake')
compiler = meson.get_compiler('cpp')

assimp_opt = cmake.subproject_options()
assimp_opt.add_cmake_defines({
    'BUILD_SHARED_LIBS': false,
    'ASSIMP_BUILD_ASSIMP_TOOLS': false,
    'ASSIMP_BUILD_TESTS': false,
})
assimp_proj = cmake.subproject('assimp', options: assimp_opt)

assimp_dep = assimp_proj.dependency('assimp')
zlib_dep = assimp_proj.dependency('zlibstatic')

glm_dep = dependency('glm')
glew_dep = dependency('glew')
rapidjson_dep = dependency('rapidjson')

if host_machine.system() == 'linux'
    glu_dep = dependency('glu')
    sfml_dep = dependency('sfml')
elif host_machine.system() == 'windows'
    glu_dep = compiler.find_library('glu32')

    if target_machine.cpu_family() == 'x86'
        sfml_dep = dependency('sfml_win32')
    elif target_machine.cpu_family() == 'x86_64'
        sfml_dep = dependency('sfml_win64')
    endif
endif

src_assembler = run_command('src_assembler.py')
sources = src_assembler.stdout().strip().split('\n')

executable('antware', sources,
    win_subsystem: 'windows',
    override_options: ['cpp_std=c++17'],
    include_directories: ['include'],
    dependencies: [sfml_dep, glew_dep, glm_dep, glu_dep, rapidjson_dep, zlib_dep, assimp_dep])