grammar ShellGrammar;

start : (buildIns | 'exec' startProgram);

buildIns
        : 'ls'                                                              #listWorkingDirectory
        | 'pwd'                                                             #getWorkingDirectory
        | 'cd' newDir=STRING                                                #changeWorkingDirectory
        ;

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

