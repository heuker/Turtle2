grammar ShellGrammar;

start : (buildIns | startProgram)?;

buildIns
        : 'pwd'                                                             #getWorkingDirectory
        | 'cd' newDir=STRING                                                #changeWorkingDirectory
        ;

startProgram
        : program=STRING (argument| iORedirect | '|' startProgram (background='&')? )*  #executeProgram
        ;

argument
        : STRING;

iORedirect
        : op=('>' | '>>' | '2>' | '<') fileName=STRING
        ;


STRING: ~[\r\t\f ]+;
WS: [\r\t\f ]+ -> skip;

