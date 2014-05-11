BRIDGE_ROOT=libraries/bridge
BRIDGE_DIR=libraries/bridge/steam_api_bridge.dll

.PHONY : all clean rebuild winemaker install uninstall

all :
	cd $(BRIDGE_DIR) && $(MAKE)

clean :
	cd $(BRIDGE_DIR) && $(MAKE) clean

rebuild : clean
	cd $(BRIDGE_DIR) && $(MAKE)

winemaker :
	cd $(BRIDGE_ROOT) && ./winemaker.sh

install :
	./buildhelper/install.py

uninstall:
	./buildhelper/uninstall.py

