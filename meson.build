project('ant-warrior', 'cpp',
    license: 'GPL-3.0-or-later',
    version: '0.0.1',
    default_options: ['warning_level=3','default_library=static'])

sfml_dep = subproject('sfml').get_variable('sfml_dep')
rapidjson_dep = subproject('rapidjson').get_variable('rapidjson_dep')
glew_dep = subproject('glew').get_variable('glew_dep')
if host_machine.system()=='linux'
    assimp_dep=dependency('assimp') #TODO your magic, @rami
endif

src_assembler = run_command('src_assembler.py')
sources = src_assembler.stdout().strip().split('\n')

executable('ant-warrior', sources,
    win_subsystem: 'windows',
    override_options: ['cpp_std=c++17'],
    include_directories: ['include'],
    dependencies: [sfml_dep, glew_dep, rapidjson_dep, assimp_dep]) #FIXME Windows builds are not working 
                                                                   #since Assimp is missing. 
