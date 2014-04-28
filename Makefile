BRIDGE_ROOT=bridge
BRIDGE_DIR=bridge/steam_api_bridge.dll

.PHONY : all clean rebuild winemaker config install uninstall

all :
	cd $(BRIDGE_DIR) && $(MAKE)

clean :
	cd $(BRIDGE_DIR) && $(MAKE) clean

rebuild : clean
	cd $(BRIDGE_DIR) && $(MAKE)

winemaker :
	cd $(BRIDGE_ROOT) && ./winemaker.sh

config :
	./installation/config.py

install :
	./installation/install.py

uninstall:
	./installation/uninstall.py

