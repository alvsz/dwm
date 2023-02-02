# dwm

```
git clone https://github.com/alvsz/dwm.git
cd dwm
sed s,/home/mamba,$HOME,g -i config.def.h
mkdir -p $HOME/.config/dwm
touch $HOME/.config/dwm/autostart.sh
touch $HOME/.config/dwm/autostart_blocking.sh
sudo make clean install
