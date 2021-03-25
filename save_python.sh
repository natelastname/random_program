name=$(mktemp -d ./python_progs/XXXXXXX)
cp ./src/dynamic.c $name
mv ./cap.bmp $name

echo "Saved in ($name)"
