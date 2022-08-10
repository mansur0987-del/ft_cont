#bin/bash

make re

leaks --atExit -- ./ft_containers > ft_containers.txt
leaks --atExit -- ./std_containers > std_containers.txt

diff ft_containers.txt std_containers.txt > diff.txt
