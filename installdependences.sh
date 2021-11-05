apt install g++
apt install libgl-dev
apt install mesa-common-dev
apt install libmesa-dev
apt install libglfw3
apt install libglfw3-dev
apt install libglu1-mesa-dev 
apt install freeglut3-dev
apt install libfreetype-dev 
apt install libfreetype6 
apt install libfreetype6-dev

git clone https://github.com/jtsiomb/libdrawtext.git
cd libdrawtext
./configure
make
make install

cp libdrawtext/libdrawtext.so.0 /usr/lib

