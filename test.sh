#bin/bash

make re

./ft_containers > ft_containers.txt
./std_containers > std_containers.txt

diff ft_containers.txt std_containers.txt > dif.txt
