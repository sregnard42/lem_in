#maps/generator --flow-one > tmp.map
#maps/generator --flow-ten > tmp.map
#maps/generator --flow-thousand > tmp.map
#maps/generator --big > tmp.map
maps/generator --big-superposition > tmp.map
./lem-in < tmp.map
tail -1 tmp.map
