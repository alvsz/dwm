# dwm-polybar

todos os patches utilizados estão em /patches/

## atalhos do teclado
- Super+d > [lançador](https://github.com/alvsz/dmenu)
- Super+Shift+Enter > [terminal](https://github.com/alvsz/st)
- Super+v > gerenciar [área de transferência](https://github.com/cdown/clipmenu)
- Super+p > habilitar barra superior
- Super+Setas 
- - direita/esquerta > mudar janela em foco
- - cima/baixo > coloca a janela em foco no master
- Super+Shift+Setas
- - esquerda/direita > altera o tamanho do master
- - cima/baixo >  altera a quantidade de janelas no master
- Super+q > fecha a janela ativa
- Super+b/n/m > muda a disposição das janelas
- Super+Tab > muda para o próximo tag
- Super+print > abre a interface do gnome-screenshot
- Print > salva o print da tela em ~/Imagens
- Control+print > salva o print da tela na área de transferência
- Shift+print > seleciona uma área para tirar print e salva em ~/Imagens
- Shift+Control+print > seleciona uma área para tirar print e salva na área de transferência
- Super+Shift+q > reinicia o dwm
- Super+Control+Shift+q > fecha o dwm

## relevante
[pywal](https://github.com/dylanaraps/pywal) para as cores do sistema
- depois de rodar `wal -b suaimagem` remova a penúltima linha de ~.cache/wal/colors-wal-dwm.h para funcionar sem o patch de cores

os controles de som são para pulseaudio e o player de música é a versão flatpak de [spot](https://github.com/xou816/spot)

[playerctl](https://github.com/altdesktop/playerctl) para usar os controles de mídia e [mpv-mpris](https://github.com/hoyon/mpv-mpris) para o mpv
