grammar ShellGrammar;

start : (buildIns | 'exec' startProgram) derp;

buildIns
        : 'ls'                                                              #listWorkingDirectory
        | 'pwd'                                                             #getWorkingDirectory
        | 'cd' newDir=STRING                                                #changeWorkingDirectory
        ;

derp : kabouter='a'* kabouter='b'*;

startProgram
        : (buildIns | program=STRING) (arguments=STRING | iORedirect | programPipedTo)* ('&')? #executeProgram
        ;

iORedirect
        : op=('>' | '>>' | '2>' | '<') fileName=STRING
        ;

programPipedTo
        : '|' (buildIns | program=STRING)
        ;



STRING: [A-Za-z0-9./~]+;
WS: [\r\t\f ]+ -> skip;

