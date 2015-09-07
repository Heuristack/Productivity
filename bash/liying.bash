
export ACE_HOME=$HOME/sources/ace
if [ $HN == 'liying' ]; then export ACE_HOME=$HOME/orc/ace; fi
export ACE_ROOT=$ACE_HOME/wrappers
export ACE_LIB=$ACE_ROOT/lib
export LOCAL_DYLD_LIBRARY_PATH=$ACE_LIB:$LOCAL_DYLD_LIBRARY_PATH

export BOOST_HOME=$HOME/sources/boost
if [ $HN == 'liying' ]; then export BOOST_HOME=$HOME/Programming/boost; fi
export BOOST_INCLUDE=$BOOST_HOME/include
export BOOST_LIBRARY=$BOOST_HOME/lib
export LOCAL_DYLD_LIBRARY_PATH=$BOOST_LIBRARY:$LOCAL_DYLD_LIBRARY_PATH

export QUANTLIB_HOME=$HOME/sourses/quantlib
if [ $HN == 'liying' ]; then export QUANTLIB_HOME=$HOME/Courses/HKU/COMP7406_FIN3/quantlib; fi
export QUANTLIB_INCLUDE=$QUANTLIB_HOME/include
export QUANTLIB_LIBRARY=$QUANTLIB_HOME/lib
export LOCAL_DYLD_LIBRARY_PATH=$QUANTLIB_LIBRARY:$LOCAL_DYLD_LIBRARY_PATH

alias cdace='cd $ACE_ROOT'
alias cdboost='cd $BOOST_HOME'
alias cdquant='cd $QUANTLIB_HOME'


export JAVA_HOME=$(/usr/libexec/java_home -v 1.8)
export JAVA_LIB=$JAVA_HOME/lib
export JAVA=$JAVA_HOME/bin
export CLASSPATH=$JAVA_LIB:$CLASSPATH
export LOCALPATH=$LOCALPATH:$JAVA

export JRE_HOME=$JAVA_HOME/jre
export JRE_LIB=$JRE_HOME/lib
export JRE=$JRE_HOME/bin
export CLASSPATH=$JRE_LIB:$CLASSPATH
export LOCALPATH=$LOCALPATH:$JRE

export M2_HOME=/opt/apache-maven-3.2.1
export M2=$M2_HOME/bin
export LOCALPATH=$LOCALPATH:$M2


export MASTER_HOME=$HOME/MasterProject
export NESOX_HOME=$MASTER_HOME/Nesox
export NESOX_BIN=$NESOX_HOME/bin
export LOCALPATH=$LOCALPATH:$NESOX_BIN
export CLUSTERSCRIPT=$MASTER_HOME/ClusterScripts
export LOCALPATH=$LOCALPATH:$CLUSTERSCRIPT

alias cdmaster='cd $MASTER_HOME'
alias cdnesox='cd $NESOX_HOME'


export ALGO_HOME=$HOME/Programming/algo
export ALGO_INCLUDE=$ALGO_HOME/incl
export ALGO_LIBRARY=$ALGO_HOME/libs

export TBRICKS=$HOME/tbricks
alias cdt='cd $TBRICKS'

export TB_HOME=$TBRICKS/tbricks.tb
alias cdtb='cd $TB_HOME'

