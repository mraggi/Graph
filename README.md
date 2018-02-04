# Instalar los siguientes:
	git
	cmake
	Google test
	SFML
	boost
	clang o gcc
	kdevelop o codeblocks

# Para ubuntu 16.04:

`wget https://raw.githubusercontent.com/mraggi/Graph/master/install_ubuntu1604.sh && chmod +x install_ubuntu1604.sh && ./install_ubuntu1604.sh`

# Para ubuntu 17.10:

`wget https://raw.githubusercontent.com/mraggi/Graph/master/install_ubuntu1710.sh && chmod +x install_ubuntu1710.sh && ./install_ubuntu1710.sh`

# Para manjaro/arch

`wget https://raw.githubusercontent.com/mraggi/Graph/master/install_arch.sh && chmod +x install_arch.sh && ./install_arch.sh`

En manjaro/arch es fácil:
```sh
sudo pacman -S sfml git cmake boost gtest clang gcc kdevelop
git clone https://github.com/mraggi/Graph
cd Graph
mkdir build
cd build
cmake ..
make
```
