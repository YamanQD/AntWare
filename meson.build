project('ant-warrior', 'cpp',
    license: 'GPL-3.0-or-later',
    version: '0.0.1',
    default_options: ['warning_level=3','default_library=static'])

compiler = meson.get_compiler('cpp')
cmake = import('cmake')

sfml_dep = subproject('sfml').get_variable('sfml_dep')
rapidjson_dep = subproject('rapidjson').get_variable('rapidjson_dep')
glew_dep = subproject('glew').get_variable('glew_dep')

assimp_dep = cmake.subproject('assimp').dependency('assimp')

glm_dep = dependency('glm')

if host_machine.system() == 'linux'
    glu_dep = dependency('glu')
elif host_machine.system() == 'windows'
    glu_dep = compiler.find_library('glu32')
endif

src_assembler = run_command('src_assembler.py')
sources = src_assembler.stdout().strip().split('\n')

executable('antware', sources,
    win_subsystem: 'windows',
    override_options: ['cpp_std=c++17'],
    include_directories: ['include'],
    dependencies: [sfml_dep, glew_dep, glm_dep, glu_dep, rapidjson_dep, assimp_dep])