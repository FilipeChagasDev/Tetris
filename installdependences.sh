apt install g++
apt install mesa-common-dev
apt install libmesa-dev
apt install libglfw3
apt install libglfw3-dev

git clone https://github.com/jtsiomb/libdrawtext.git
cd libdrawtext
./configure
make
make install

cp libdrawtext/libdrawtext.so.0 /usr/lib

