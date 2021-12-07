project('ant-warrior', 'cpp',
    license: 'GPL-3.0-or-later'
    version : '0.0.1',
    default_options : ['warning_level=3'])

if host_machine.system()=='linux'
    src_assembler=run_command('src_assembler.sh')
elif host_machine.system()=='windows'
    #TODO @rami write your own patch file
    #OR delete the if condition if you could run the shell script
endif

sfml_window = dependency('sfml-window')
sources = src_assembler.stdout().strip().split('\n')
executable('ant-warrior', sources,
    include_directories:['include'],
    dependencies:[sfml_window])