project('ant-warrior', 'cpp',
    license: 'GPL-3.0-or-later'
    version : '0.0.1',
    default_options : ['warning_level=3'])

if host_machine.system()=='linux'
    srcAssembler=run_command('srcAssembler.sh')
elif host_machine.system()=='windows'
    #TODO @rami write your own patch file
    #OR delete the if condition if you could run the shell script
endif
sfmlWindow=dependency('sfml-window')
sources=srcAssembler.stdout().strip().split('\n')
executable('ant-warrior',sources,include_directories:['include'],dependencies:[sfmlWindow])