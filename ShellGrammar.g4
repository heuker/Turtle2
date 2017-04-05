grammar ShellGrammar;

start : (buildIns | startProgram);

buildIns
        : 'pwd'                                                             #getWorkingDirectory
        | 'cd' newDir=STRING                                                #changeWorkingDirectory
        ;

startProgram
        : program=STRING (argument| iORedirect | programPipedTo)* ('&')? #executeProgram
        ;

argument
        : STRING;

iORedirect
        : op=('>' | '>>' | '2>' | '<') fileName=STRING
        ;

programPipedTo
        : '|' program=STRING
        ;


STRING: [A-Za-z0-9./~-]+;
WS: [\r\t\f ]+ -> skip;

