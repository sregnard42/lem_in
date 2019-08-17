maps/generator --big-superposition > tmp.map
./lem-in < tmp.map
tail -1 tmp.map
