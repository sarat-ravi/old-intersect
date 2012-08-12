filename=$(basename "$1")
extension=${filename##*.}
filename=${filename%.*}
bin=bin
compiledFileName=a.out
#echo $filename
gcc $1 -o $compiledFileName `pkg-config --cflags --libs opencv`
