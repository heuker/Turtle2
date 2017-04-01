grammar ShellGrammar;

start : (buildIns | startProgram);

buildIns
        : 'ls'                                                              #listWorkingDirectory
        | 'pwd'                                                             #getWorkingDirectory
        | 'cd' newDir=STRING                                                #changeWorkingDirectory
        ;

startProgram
        : (buildIns | program=STRING) (arguments=STRING | iORedirect | programPipedTo)* ('&')? #executeProgram
        ;

iORedirect
        : ('>' | '>>' | '2>' | '<') fileName=STRING
        ;

programPipedTo
        : '|' (buildIns | program=STRING)
        ;



STRING: [A-Za-z0-9.]+;
WS: [\r\n\t\f ]+ -> skip;

