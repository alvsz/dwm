# dwm

```
git clone https://github.com/alvsz/dwm.git
cd dwm
sed s,/home/mamba,$HOME,g -i config.def.h
mkdir -p $HOME/.config/dwm
ln -s keys.h $HOME/.config/dwm
ln -s rules.h $HOME/.config/dwm
sudo make clean install
