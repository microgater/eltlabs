После make прописать:

LD_LIBRARY_PATH=${PWD}:${LD_LIBRARY_PATH}
export LD_LIBRARY_PATH


После использования можно затереть запись LD_LIBRARY_PATH:

LD_LIBRARY_PATH=""
export LD_LIBRARY_PATH
