ls *.c | while read archivo; do
    nuevo_nombre=$(echo "$archivo" | sed 's/..$//')
    gcc "$archivo" -o ../programas/"$nuevo_nombre"
done

