project('ant-warrior','cpp')
if host_machine.system()=='linux'
    srcAssembler=run_command('srcAssembler.sh')
elif host_machine.system()=='windows'
    #TODO @rami write your own patch file
    #OR delete the if condition if you could run the shell script
endif
sfmlWindow=dependency('sfml-window')
sources=srcAssembler.stdout().strip().split('\n')
executable('ant-warrior',sources,include_directories:['include'],dependencies:[sfmlWindow])