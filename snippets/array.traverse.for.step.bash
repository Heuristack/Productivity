array+=(a b)
array+=(c)

size=${#array[@]}
step=1

for (( index=0; index<size; index=index+step )); 
do
    echo ${array[index]}
done

