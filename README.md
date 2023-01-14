# dwm

```
sed s,/home/mamba,$HOME,g -i config.def.h
mkdir -p $HOME/.config/dwm
cp keys.h $HOME/.config/dwm
cp rules.h $HOME/.config/dwm
sudo make clean install
