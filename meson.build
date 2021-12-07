project('ant-warrior', ['cpp','c'],
    license: 'GPL-3.0-or-later',
    version: '0.0.1',
    default_options: ['warning_level=3','default_library=static'])

sfml_dep = subproject('sfml').get_variable('sfml_dep')
rapidjson_dep = subproject('rapidjson').get_variable('rapidjson_dep')
glew_dep = dependency('glew')

src_assembler = run_command('src_assembler.py')
sources = src_assembler.stdout().strip().split('\n')

executable('ant-warrior', sources,
    win_subsystem: 'windows',
    include_directories: ['include'],
    dependencies: [sfml_dep, glew_dep, rapidjson_dep])
