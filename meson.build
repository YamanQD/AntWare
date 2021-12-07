project('ant-warrior', ['cpp','c'],
    license: 'GPL-3.0-or-later',
    version: '0.0.1',
    default_options: ['warning_level=3'])

sfml_dep = subproject('sfml').get_variable('sfml_dep')
rapidjson_dep = subproject('rapidjson').get_variable('rapidjson_dep')

src_assembler=run_command('src_assembler.py')

# sfml_window = dependency('sfml-window')
sources = src_assembler.stdout().strip().split('\n')
executable('ant-warrior', sources,
    include_directories: ['include'],
    dependencies: [sfml_dep, rapidjson_dep])