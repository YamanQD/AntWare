project('ant-warrior', ['cpp','c'],
    license: 'GPL-3.0-or-later',
    version: '0.0.1',
    default_options: ['warning_level=3','default_library=static'])

if host_machine.system()!='linux'
    sfml_dep = subproject('sfml').get_variable('sfml_dep')
    rapidjson_dep = subproject('rapidjson').get_variable('rapidjson_dep')
    glew_dep = subproject('glew').get_variable('glew_dep')
else
    sfml_dep=dependency('sfml-window')
    glew_dep = dependency('glew')
endif
src_assembler = run_command('src_assembler.py')
sources = src_assembler.stdout().strip().split('\n')

if host_machine.system()=='windows'
    executable('ant-warrior', sources,
        win_subsystem: 'windows',
        include_directories: ['include'],
        dependencies: [sfml_dep, glew_dep, rapidjson_dep])
elif host_machine.system()=='linux'
    executable('ant-warrior',sources,
        include_directories:['include'],
        dependencies:[sfml_dep,glew_dep])
endif
