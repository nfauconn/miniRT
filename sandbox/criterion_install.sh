#Criterion Installer for ubuntu dump 42

#installation of meson and ninja to build criterion
pip3 install --user meson

python3 -m pip install ninja

#creation of new PATH variable to find meson and ninja
#(could probably be done another way, because this method need to re-export that variable
#each time you launch a new shell)
export "PATH=/mnt/nfs/homes/nfauconn/.local/bin:$PATH"

#dowloading criterion on a usable folder
cd ~

git clone --recursive git@github.com:Snaipe/Criterion.git

cd Criterion

meson build

ninja -C build

export "LD_LIBRARY_PATH=$PWD/build/src"

#now you should be able to use criterion library by compiling like this:
#gcc -o "binary" "files" -I/$HOME/Criterion/include
#-L/$HOME/Criterion/build/src -W -Wall -Wextra -Werror -lcriterion